#include "Ifx_Types.h"
#include "IfxI2c_I2c.h"
#include "asclin.h"
#include <math.h>
#include <stdbool.h>
#include "IfxStm.h"


#define IMU_SCL_PIN                 IfxI2c0_SCL_P13_1_INOUT
#define IMU_SDA_PIN                 IfxI2c0_SDA_P13_2_INOUT
#define I2C_BAUDRATE                400000

#define MPU9250_I2C_ADDRESS         0x68
#define MPU9250_REG_ACCEL_XOUT_H    0x3B
#define MPU9250_USER_CTRL         0x6A
#define MPU9250_I2C_MST_CTRL      0x24
#define MPU9250_INT_PIN_CFG       0x37
#define SENSOR_PACKET_SIZE          14

#define AK8963_I2C_ADDR           0x0C
#define AK8963_CNTL1              0x0A
#define AK8963_ASAX               0x10
#define AK8963_WHO_AM_I           0x00
#define AK8963_ST1                0x02
#define AK8963_MAGNET_OUT         0x03


#define M_PI 3.14159f

IfxI2c_I2c g_i2cHandle;
IfxI2c_I2c_Device g_i2cDevImu;
uint8 g_sensorRaw[SENSOR_PACKET_SIZE] = {0};



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
    uint8 cmds[][2] = {
        { 0x6B, 0x00 }, // PWR_MGMT_1: Wake up
//        { 0x19, 0x07 }, // SMPLRT_DIV: Sample rate = Gyro output rate / (1 + 7) = 1kHz / 8 = 125Hz
        { 0x19, 0x31 }, // SMPLRT_DIV: Sample rate = Gyro output rate / (1 + 7) = 1kHz / 8 = 125Hz
        { 0x1A, 0x06 }, // CONFIG: DLPF set
//        { 0x1A, 0x03 }, // CONFIG: DLPF set
        { 0x1B, 0x00 }, // GYRO_CONFIG: ±250°/s
        { 0x1C, 0x00 }  // ACCEL_CONFIG: ±2g
    };

    for (int i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++) {
        sint8 status = IfxI2c_I2c_write(&g_i2cDevImu, cmds[i], 2);
        print("WRITE to 0x%02X status: %d\n\r", cmds[i][0], status);
        delay_ms(100);
    }
    print("OK");
}

void read_mpu9250_sensor_data(void)
{
    uint8 reg = MPU9250_REG_ACCEL_XOUT_H;
    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
    while (IfxI2c_I2c_read(&g_i2cDevImu, g_sensorRaw, SENSOR_PACKET_SIZE) == IfxI2c_I2c_Status_nak);
}

void init_ak8963_registers(void)
{
    uint8 val;
    // 1. MPU9250의 BYPASS 모드 활성화 (AK8963 직접 접근 가능하게)
    uint8 cfg[] = {MPU9250_USER_CTRL, 0x00}; // Disable master mode
    IfxI2c_I2c_write(&g_i2cDevImu, cfg, 2);
    delay_ms(10);

    uint8 bypass[] = {MPU9250_INT_PIN_CFG, 0x02}; // BYPASS_EN
    IfxI2c_I2c_write(&g_i2cDevImu, bypass, 2);
    delay_ms(10);

    // 2. AK8963 WHO_AM_I 확인 (0x48 expected)
    uint8 reg = AK8963_WHO_AM_I;
    uint8 whoami = 0x00;
    IfxI2c_I2c_deviceConfig akConf;
    IfxI2c_I2c_initDeviceConfig(&akConf, &g_i2cHandle);
    akConf.deviceAddress = AK8963_I2C_ADDR << 1;
    IfxI2c_I2c_Device ak8963;
    IfxI2c_I2c_initDevice(&ak8963, &akConf);

    IfxI2c_I2c_write(&ak8963, &reg, 1);
    IfxI2c_I2c_read(&ak8963, &whoami, 1);
    print("AK8963 WHO_AM_I = 0x%02X\n\r", whoami);

    // 3. Power down → Fuse ROM access → Read sensitivity adj.
    uint8 pd[2] = {AK8963_CNTL1, 0x00};
    IfxI2c_I2c_write(&ak8963, pd, 2);
    delay_ms(100);

    uint8 fuse[2] = {AK8963_CNTL1, 0x0F};  // Fuse ROM access mode
    IfxI2c_I2c_write(&ak8963, fuse, 2);
    delay_ms(100);

    uint8 asa[3];
    reg = AK8963_ASAX;
    IfxI2c_I2c_write(&ak8963, &reg, 1);
    IfxI2c_I2c_read(&ak8963, asa, 3);
    print("AK8963 ASA = %02X %02X %02X\n\r", asa[0], asa[1], asa[2]);

    pd[1] = 0x00;
    IfxI2c_I2c_write(&ak8963, pd, 2);
    delay_ms(100);

    uint8 cont[2] = {AK8963_CNTL1, 0x16}; // 0x16 = 16-bit, 100Hz, continuous mode 2
    IfxI2c_I2c_write(&ak8963, cont, 2);
    delay_ms(100);
}

void read_accel_raw(sint16* ax, sint16* ay, sint16* az)
{
    uint8 reg = 0x3B;  // ACCEL_XOUT_H
    uint8 buffer[6];

    // 레지스터 주소 설정 후 읽기
    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
    while (IfxI2c_I2c_read(&g_i2cDevImu, buffer, 6) == IfxI2c_I2c_Status_nak);

    *ax = (sint16)((buffer[0] << 8) | buffer[1]);
    *ay = (sint16)((buffer[2] << 8) | buffer[3]);
    *az = (sint16)((buffer[4] << 8) | buffer[5]);
}


void read_gyro_raw(sint16* gx, sint16* gy, sint16* gz)
{
    uint8 reg = 0x43;  // GYRO_XOUT_H
    uint8 buffer[6];

    // 레지스터 주소 설정 후 읽기
    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
    while (IfxI2c_I2c_read(&g_i2cDevImu, buffer, 6) == IfxI2c_I2c_Status_nak);

    *gx = (sint16)((buffer[0] << 8) | buffer[1]);
    *gy = (sint16)((buffer[2] << 8) | buffer[3]);
    *gz = (sint16)((buffer[4] << 8) | buffer[5]);
}


void read_magnetometer_raw(sint16* mx, sint16* my, sint16* mz)
{
    uint8 reg = AK8963_ST1;
    uint8 st1;
    IfxI2c_I2c_Device ak8963;
    IfxI2c_I2c_deviceConfig akConf;
    IfxI2c_I2c_initDeviceConfig(&akConf, &g_i2cHandle);
    akConf.deviceAddress = AK8963_I2C_ADDR << 1;
    IfxI2c_I2c_initDevice(&ak8963, &akConf);

    // 1. Data ready 확인
    IfxI2c_I2c_write(&ak8963, &reg, 1);
    IfxI2c_I2c_read(&ak8963, &st1, 1);
    if (!(st1 & 0x01)) return; // Data not ready

    // 2. Read 7 bytes: X, Y, Z, ST2
    reg = AK8963_MAGNET_OUT;
    uint8 buffer[7];
    IfxI2c_I2c_write(&ak8963, &reg, 1);
    IfxI2c_I2c_read(&ak8963, buffer, 7);

    *mx = (buffer[1] << 8) | buffer[0];
    *my = (buffer[3] << 8) | buffer[2];
    *mz = (buffer[5] << 8) | buffer[4];
}
