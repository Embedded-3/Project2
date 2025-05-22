#include "Ifx_Types.h"
//#include "IfxI2c_I2c.h"
#include "Libraries\iLLD\TC27D\Tricore\I2c\I2c\IfxI2c_I2c.h"
#include "asclin.h"
#include <math.h>
#include <stdbool.h>
#include "IfxStm.h"
#include "mp.h"


#define IMU_SCL_PIN                 IfxI2c0_SCL_P13_1_INOUT
#define IMU_SDA_PIN                 IfxI2c0_SDA_P13_2_INOUT
#define I2C_BAUDRATE                400000

#define MPU9250_I2C_ADDRESS         0x68
#define MPU9250_REG_ACCEL_XOUT_H    0x3B
#define SENSOR_PACKET_SIZE          14

#define M_PI 3.14159f

IfxI2c_I2c g_i2cHandle;
IfxI2c_I2c_Device g_i2cDevImu;
uint8 g_sensorRaw[SENSOR_PACKET_SIZE] = {0};


static float gx_offset = 0.0f, gy_offset = 0.0f, gz_offset = 0.0f;
static bool calibrated = false;
static float offset_roll = 0.0f, offset_pitch = 0.0f;
static bool offset_ready = false;
static float angle_x = 0.0f, angle_y = 0.0f;

void compute_initial_offset(void);


void check_who_am_i(void)
{
    uint8 reg = 0x75;
    uint8 val = 0;

    print("WHO_AM_I 체크 시작\n\r");

    sint8 w = IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1);
    print("WRITE 상태: %d\n\r", w);

    sint8 r = IfxI2c_I2c_read(&g_i2cDevImu, &val, 1);
    print("READ  상태: %d\n\r", r);
    print("WHO_AM_I: 0x%02X\n\r", val);
}



void init_I2C_module(void)
{
    IfxI2c_I2c_Config i2cConfig;
    IfxI2c_I2c_initConfig(&i2cConfig, &MODULE_I2C0);
    const IfxI2c_Pins MPU_PINS = {
        &IMU_SCL_PIN,
        &IMU_SDA_PIN,
        IfxPort_PadDriver_ttlSpeed1
    };
    i2cConfig.pins = &MPU_PINS;
    i2cConfig.baudrate = I2C_BAUDRATE;
    IfxI2c_I2c_initModule(&g_i2cHandle, &i2cConfig);

    IfxI2c_I2c_deviceConfig i2cDeviceConfig;
    IfxI2c_I2c_initDeviceConfig(&i2cDeviceConfig, &g_i2cHandle);
    i2cDeviceConfig.deviceAddress = MPU9250_I2C_ADDRESS << 1;
    IfxI2c_I2c_initDevice(&g_i2cDevImu, &i2cDeviceConfig);

}


void init_mpu9250_registers(void)
{
    // uint8 cmds[][2] = {
    //     { 0x6B, 0x01 }, // PWR_MGMT_1: Wake up
    //     //{ 0x19, 0x07 }, // SMPLRT_DIV: Sample rate = Gyro output rate / (1 + 7) = 1kHz / 8 = 125Hz
    //     { 0x19, 0x31 }, // SMPLRT_DIV: Sample rate = Gyro output rate / (1 + 7) = 1kHz / 8 = 125Hz
    //     //{ 0x1A, 0x06 }, // CONFIG: DLPF set
    //     { 0x1A, 0x03 }, // CONFIG: DLPF set
    //     { 0x1B, 0x00 }, // GYRO_CONFIG: ±250°/s
    //     { 0x1C, 0x00 }  // ACCEL_CONFIG: ±2g
    // };

    uint8 cmds[][2] = {
        { 0x6B, 0x00 }, // PWR_MGMT_1: Wake up (0x00이면 클럭 자동 선택)
        { 0x19, 0x07 }, // SMPLRT_DIV: 1kHz / (1 + 7) = 125Hz
        { 0x1A, 0x03 }, // CONFIG: DLPF 설정
        { 0x1B, 0x00 }, // GYRO_CONFIG: ±250dps
        { 0x1C, 0x00 }  // ACCEL_CONFIG: ±2g
    };

    for (int i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++) {
        while (IfxI2c_I2c_write(&g_i2cDevImu, cmds[i], 2) == IfxI2c_I2c_Status_nak);

    }
}

void scan_I2C_bus(void)
{
    uint8 reg = 0x75;
    uint8 val = 0;

    print("I2C 버스 스캔 시작\n\r");

    for (uint8 addr = 0x03; addr < 0x77; addr++) {
        IfxI2c_I2c_deviceConfig devConfig;
        IfxI2c_I2c_initDeviceConfig(&devConfig, &g_i2cHandle);
        devConfig.deviceAddress = addr << 1;

        IfxI2c_I2c_Device tempDev;
        IfxI2c_I2c_initDevice(&tempDev, &devConfig);

        if (IfxI2c_I2c_write(&tempDev, &reg, 1) == 0 &&
            IfxI2c_I2c_read(&tempDev, &val, 1) == 0) {
            print("Found device at 0x%02X (WHO_AM_I=0x%02X)\n\r", addr, val);
        }

        //delay_ms(20);
    }

    print("I2C 스캔 완료\n\r");
}





void read_mpu9250_sensor_data(void)
{
    uint8 reg = MPU9250_REG_ACCEL_XOUT_H;
    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
    while (IfxI2c_I2c_read(&g_i2cDevImu, g_sensorRaw, SENSOR_PACKET_SIZE) == IfxI2c_I2c_Status_nak);
    print("read");
}


void calibrate_gyro()
{
    int sum_gx = 0, sum_gy = 0, sum_gz = 0;
    for (int i = 0; i < 100; i++) {
        read_mpu9250_sensor_data();
        sint16 gx = (g_sensorRaw[8] << 8) | g_sensorRaw[9];
        sint16 gy = (g_sensorRaw[10] << 8) | g_sensorRaw[11];
        sint16 gz = (g_sensorRaw[12] << 8) | g_sensorRaw[13];
        sum_gx += gx;
        sum_gy += gy;
        sum_gz += gz;
        //delay_ms(10);
    }
    gx_offset = sum_gx / 100.0f / 131.0f;
    gy_offset = sum_gy / 100.0f / 131.0f;
    gz_offset = sum_gz / 100.0f / 131.0f;
    calibrated = true;
    compute_initial_offset();
}


void print_mpu9250_raw_data(void)
{
    sint16 ax = (g_sensorRaw[0] << 8) | g_sensorRaw[1];
    sint16 ay = (g_sensorRaw[2] << 8) | g_sensorRaw[3];
    sint16 az = (g_sensorRaw[4] << 8) | g_sensorRaw[5];

    sint16 tempRaw = (g_sensorRaw[6] << 8) | g_sensorRaw[7];

    sint16 gx = (g_sensorRaw[8] << 8) | g_sensorRaw[9];
    sint16 gy = (g_sensorRaw[10] << 8) | g_sensorRaw[11];
    sint16 gz = (g_sensorRaw[12] << 8) | g_sensorRaw[13];

    print("ACCEL RAW  X:%d  Y:%d  Z:%d\n\r", ax, ay, az);
    print("GYRO  RAW  X:%d  Y:%d  Z:%d\n\r", gx, gy, gz);
    print("TEMP  RAW : %d\n\r", tempRaw);
}



void print_mpu9250_sensor_data(void)
{

    if (!calibrated) return;

    sint16 ax = (g_sensorRaw[0] << 8) | g_sensorRaw[1];
    sint16 ay = (g_sensorRaw[2] << 8) | g_sensorRaw[3];
    sint16 az = (g_sensorRaw[4] << 8) | g_sensorRaw[5];

    sint16 tempRaw = (g_sensorRaw[6] << 8) | g_sensorRaw[7];
    float tempC = (tempRaw / 333.87f) + 21.0f;

    sint16 gx = (g_sensorRaw[8] << 8) | g_sensorRaw[9];
    sint16 gy = (g_sensorRaw[10] << 8) | g_sensorRaw[11];
    sint16 gz = (g_sensorRaw[12] << 8) | g_sensorRaw[13];

    float ax_g = ax / 16384.0f;
    float ay_g = ay / 16384.0f;
    float az_g = az / 16384.0f;

    float gx_dps = gx / 131.0f - gx_offset;
    float gy_dps = gy / 131.0f - gy_offset;
    float gz_dps = gz / 131.0f;

    // 가속도 기반 각도 계산
    float accel_x = atan2f(ay_g, sqrtf(ax_g * ax_g + az_g * az_g)) * 180.0f / M_PI;
    float accel_y = atan2f(-ax_g, sqrtf(ay_g * ay_g + az_g * az_g)) * 180.0f / M_PI;

    float dt = 0.05f;
    if (dt <= 0 || dt > 0.1f) dt = 0.05f;

    float gyro_angle_x = angle_x + gx_dps * dt;
    float gyro_angle_y = angle_y + gy_dps * dt;

    // 상보필터 적용
    angle_x = 0.95f * gyro_angle_x + 0.05f * accel_x;
    angle_y = 0.95f * gyro_angle_y + 0.05f * accel_y;

//    print("ACC  X:%.2fg  Y:%.2fg  Z:%.2fg\n\r", ax_g, ay_g, az_g);
//    print("GYRO X:%.2f°/s  Y:%.2f°/s  Z:%.2f°/s\n\r", gx_dps, gy_dps, gz_dps);
//    print("TEMP: %.2f °C\n\r", tempC);
//    if (offset_ready) {
//        float corrected_roll  = angle_y - offset_roll;
//        float corrected_pitch = angle_x - offset_pitch;
//        print("ROLL: %.2f°  PITCH: %.2f° (보정)\n\r", corrected_roll, corrected_pitch);
//    }
//    else {
//        print("ROLL: %.2f°  PITCH: %.2f° (상보필터)\n\r", angle_y, angle_x);
//    }
    if (offset_ready) {
        float corrected_roll  = angle_y - offset_roll;
        float corrected_pitch = angle_x - offset_pitch;
        if(corrected_pitch>=-1.5f && corrected_pitch <=1.5f){
            print("평지: %.2f° \n\r", corrected_pitch);
        }
        else if(corrected_pitch>1.5f){
            print("오르막길: %.2f° \n\r", corrected_pitch);
        }
        else{
            print("내르막길: %.2f° \n\r", corrected_pitch);
        }
    }
}

void compute_initial_offset(void)
{
    float sum_roll = 0.0f, sum_pitch = 0.0f;
    const int sample_count = 60;

    for (int i = 0; i < sample_count; i++) {
        read_mpu9250_sensor_data();
        print_mpu9250_sensor_data();  // angle_x, angle_y 업데이트
        sum_pitch += angle_x;
        sum_roll  += angle_y;
        //delay_ms(50);
    }

    offset_pitch = sum_pitch / sample_count;
    offset_roll  = sum_roll  / sample_count;
    offset_ready = true;
}
