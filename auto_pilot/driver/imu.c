#include "Ifx_Types.h"
#include "IfxI2c_I2c.h"
#include "asclin.h"
#include <math.h>
#include <stdbool.h>
#include "IfxStm.h"
#include "imu.h"

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

float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};
float beta = 0.05f;
float deltat = 0.05f;
float pitch, yaw, roll;

bool attitude_offset_initialized = false;
float offset_pitch = 0.0f, offset_roll = 0.0f, offset_yaw = 0.0f;
int runtime_ms = 0;

int attitude_sample_count = 0;

float mag_sensitivity[3] = {1.0f, 1.0f, 1.0f};

static float sum_yaw = 0.0f, sum_pitch = 0.0f, sum_roll = 0.0f;
static int sample_count = 0;
bool offset_calibrated = false;


void init_I2C_module(void);
void resetMPU9250(void);
void calibrate_mpu9250(void);


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
    print("I2C init complete\n\r");
}

void resetMPU9250(void) {
    uint8 reset_cmd[2] = {0x6B, 0x80};  // PWR_MGMT_1, bit7=1
    IfxI2c_I2c_write(&g_i2cDevImu, reset_cmd, 2);
    delay_ms(100);
    print("MPU9250 reset complete\n\r");
}


float calculate_pitch_from_accel(float ax, float ay, float az)
{
    float pitch_rad = atan2(-ax, sqrt(ay * ay + az * az));
    return pitch_rad * 180.0f / M_PI;  // degree로 변환
}


void calibrate_mpu9250(void)
{
    uint8 data[12];
    uint16 fifo_count = 0, packet_count = 0;
    sint32 accel_bias[3] = {0}, gyro_bias[3] = {0};
    const float accel_scale = 16384.0f; // ±2g
    const float gyro_scale = 131.0f;    // ±250 dps

    // 1. FIFO 리셋 및 설정
    uint8 setup_cmds[][2] = {
        { 0x6A, 0x00 }, // USER_CTRL: FIFO, I2C Master 비활성화
        { 0x6A, 0x0C }, // USER_CTRL: FIFO & DMP reset
        { 0x1A, 0x01 }, // CONFIG: DLPF 188Hz
        { 0x19, 0x00 }, // SMPLRT_DIV: 1kHz
        { 0x1B, 0x00 }, // GYRO_CONFIG: ±250 dps
        { 0x1C, 0x00 }, // ACCEL_CONFIG: ±2g
        { 0x6A, 0x40 }, // USER_CTRL: FIFO enable
        { 0x23, 0x78 }  // FIFO_EN: gyro + accel
    };

    for (int i = 0; i < sizeof(setup_cmds)/sizeof(setup_cmds[0]); i++) {
        IfxI2c_I2c_write(&g_i2cDevImu, setup_cmds[i], 2);
        delay_ms(10);
    }

    delay_ms(150);

    // 2. FIFO 중지 및 데이터 획득
    uint8 fifo_stop[2] = {0x23, 0x00};
    IfxI2c_I2c_write(&g_i2cDevImu, fifo_stop, 2);

    uint8 fifo_reg = 0x72;
    IfxI2c_I2c_write(&g_i2cDevImu, &fifo_reg, 1);
    IfxI2c_I2c_read(&g_i2cDevImu, data, 2);
    fifo_count = (data[0] << 8) | data[1];
    packet_count = fifo_count / 12;

    for (uint16 i = 0; i < packet_count; i++) {
        uint8 fifo_read_reg = 0x74;
        IfxI2c_I2c_write(&g_i2cDevImu, &fifo_read_reg, 1);
        IfxI2c_I2c_read(&g_i2cDevImu, data, 12);

        sint16 ax = (sint16)(data[0] << 8 | data[1]);
        sint16 ay = (sint16)(data[2] << 8 | data[3]);
        sint16 az = (sint16)(data[4] << 8 | data[5]);
        sint16 gx = (sint16)(data[6] << 8 | data[7]);
        sint16 gy = (sint16)(data[8] << 8 | data[9]);
        sint16 gz = (sint16)(data[10] << 8 | data[11]);

        accel_bias[0] += ax;
        accel_bias[1] += ay;
        accel_bias[2] += az;
        gyro_bias[0]  += gx;
        gyro_bias[1]  += gy;
        gyro_bias[2]  += gz;
    }

    // 3. 평균 및 보정값 계산
    for (int i = 0; i < 3; i++) {
        accel_bias[i] /= packet_count;
        gyro_bias[i]  /= packet_count;
    }

    // 중력 제거
    if (accel_bias[2] > 0L) accel_bias[2] -= (sint32)accel_scale;
    else accel_bias[2] += (sint32)accel_scale;

    float calibrateAccel[3], calibrateGyro[3];
    for (int i = 0; i < 3; i++) {
        calibrateAccel[i] = (float)accel_bias[i] / accel_scale;
        calibrateGyro[i]  = (float)gyro_bias[i] / gyro_scale;
    }

    // 4. 출력
    print("Accel bias (g): %.4f %.4f %.4f\n\r", calibrateAccel[0], calibrateAccel[1], calibrateAccel[2]);
    print("Gyro  bias (deg/s): %.4f %.4f %.4f\n\r", calibrateGyro[0], calibrateGyro[1], calibrateGyro[2]);
    print("Calibrate complete\n\r");
}


void init_mpu9250_registers(void)
{
    uint8 cmds[][2] = {
//        { 0x6B, 0x00 }, // PWR_MGMT_1: Wake up
        { 0x6B, 0x01 }, // PWR_MGMT_1: Use X gyro as clock
//        { 0x19, 0x07 }, // SMPLRT_DIV: Sample rate = Gyro output rate / (1 + 7) = 1kHz / 8 = 125Hz
        { 0x19, 0x31 }, // SMPLRT_DIV: Sample rate = Gyro output rate / (1 + 7) = 1kHz / 8 = 125Hz
//        { 0x1A, 0x06 }, // CONFIG: DLPF set
        { 0x1A, 0x03 }, // CONFIG: DLPF set
        { 0x1B, 0x00 }, // GYRO_CONFIG: ±250°/s
        { 0x1C, 0x00 },  // ACCEL_CONFIG: ±2g
        { 0x1D, 0x03 }, // ACCEL_CONFIG2: Accel DLPF (Bandwidth ~41Hz)
        { 0x37, 0x22 }, // INT_PIN_CFG: Active High, Push Pull
    };

    for (int i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++) {
        sint8 status = IfxI2c_I2c_write(&g_i2cDevImu, cmds[i], 2);
        print("WRITE to 0x%02X status: %d\n\r", cmds[i][0], status);
        delay_ms(100);
    }
    print("mpu9250 registers init complete\n\r");
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
    mag_sensitivity[0] = ((float)(asa[0] - 128) * 0.5f / 128.0f) + 1.0f;
    mag_sensitivity[1] = ((float)(asa[1] - 128) * 0.5f / 128.0f) + 1.0f;
    mag_sensitivity[2] = ((float)(asa[2] - 128) * 0.5f / 128.0f) + 1.0f;
    print("AK8963 ASA = %02X %02X %02X\n\r", asa[0], asa[1], asa[2]);

    pd[1] = 0x00;
    IfxI2c_I2c_write(&ak8963, pd, 2);
    delay_ms(100);

    uint8 cont[2] = {AK8963_CNTL1, 0x16}; // 0x16 = 16-bit, 100Hz, continuous mode 2
    IfxI2c_I2c_write(&ak8963, cont, 2);
    delay_ms(100);
    print("AK8963 registers init complete\n\r");
}


//void read_mpu9250_sensor_data(void)
//{
//    uint8 reg = MPU9250_REG_ACCEL_XOUT_H;
//    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
//    while (IfxI2c_I2c_read(&g_i2cDevImu, g_sensorRaw, SENSOR_PACKET_SIZE) == IfxI2c_I2c_Status_nak);
//}


//void read_accel_raw(sint16* ax, sint16* ay, sint16* az)
//{
//    uint8 reg = 0x3B;  // ACCEL_XOUT_H
//    uint8 buffer[6];
//
//    // 레지스터 주소 설정 후 읽기
//    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
//    while (IfxI2c_I2c_read(&g_i2cDevImu, buffer, 6) == IfxI2c_I2c_Status_nak);
//
//    *ax = (sint16)((buffer[0] << 8) | buffer[1]);
//    *ay = (sint16)((buffer[2] << 8) | buffer[3]);
//    *az = (sint16)((buffer[4] << 8) | buffer[5]);
//}
void read_accel_g(float* ax, float* ay, float* az)
{
    uint8 reg = 0x3B;
    uint8 buffer[6];
    sint16 raw_x, raw_y, raw_z;

    // Read 6 bytes from ACCEL_XOUT_H
    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
    while (IfxI2c_I2c_read(&g_i2cDevImu, buffer, 6) == IfxI2c_I2c_Status_nak);

    raw_x = (sint16)((buffer[0] << 8) | buffer[1]);
    raw_y = (sint16)((buffer[2] << 8) | buffer[3]);
    raw_z = (sint16)((buffer[4] << 8) | buffer[5]);

    *ax = raw_x / 16384.0f;
    *ay = raw_y / 16384.0f;
    *az = raw_z / 16384.0f;
}



//void read_gyro_raw(sint16* gx, sint16* gy, sint16* gz)
//{
//    uint8 reg = 0x43;  // GYRO_XOUT_H
//    uint8 buffer[6];
//
//    // 레지스터 주소 설정 후 읽기
//    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
//    while (IfxI2c_I2c_read(&g_i2cDevImu, buffer, 6) == IfxI2c_I2c_Status_nak);
//
//    *gx = (sint16)((buffer[0] << 8) | buffer[1]);
//    *gy = (sint16)((buffer[2] << 8) | buffer[3]);
//    *gz = (sint16)((buffer[4] << 8) | buffer[5]);
//}
void read_gyro_dps(float* gx, float* gy, float* gz)
{
    uint8 reg = 0x43;
    uint8 buffer[6];
    sint16 raw_x, raw_y, raw_z;

    while (IfxI2c_I2c_write(&g_i2cDevImu, &reg, 1) == IfxI2c_I2c_Status_nak);
    while (IfxI2c_I2c_read(&g_i2cDevImu, buffer, 6) == IfxI2c_I2c_Status_nak);

    raw_x = (sint16)((buffer[0] << 8) | buffer[1]);
    raw_y = (sint16)((buffer[2] << 8) | buffer[3]);
    raw_z = (sint16)((buffer[4] << 8) | buffer[5]);

    *gx = raw_x / 131.0f;
    *gy = raw_y / 131.0f;
    *gz = raw_z / 131.0f;
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

    sint16 raw_mx = (buffer[1] << 8) | buffer[0];
    sint16 raw_my = (buffer[3] << 8) | buffer[2];
    sint16 raw_mz = (buffer[5] << 8) | buffer[4];

    *mx = (sint16)(raw_mx * mag_sensitivity[0]);
    *my = (sint16)(raw_my * mag_sensitivity[1]);
    *mz = (sint16)(raw_mz * mag_sensitivity[2]);
}


void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
{
    gx = gx* M_PI / 180.0f;
    gy = gy* M_PI / 180.0f;
    gz = gz* M_PI / 180.0f;

    float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];
    float norm;
    float hx, hy, _2bx, _2bz;
    float s1, s2, s3, s4;
    float qDot1, qDot2, qDot3, qDot4;

    // Auxiliary variables to avoid repeated arithmetic
    float _2q1mx;
    float _2q1my;
    float _2q1mz;
    float _2q2mx;
    float _4bx;
    float _4bz;
    float _2q1 = 2.0f * q1;
    float _2q2 = 2.0f * q2;
    float _2q3 = 2.0f * q3;
    float _2q4 = 2.0f * q4;
    float _2q1q3 = 2.0f * q1 * q3;
    float _2q3q4 = 2.0f * q3 * q4;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q1q4 = q1 * q4;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q2q4 = q2 * q4;
    float q3q3 = q3 * q3;
    float q3q4 = q3 * q4;
    float q4q4 = q4 * q4;


    if (runtime_ms < 3000)
        beta = 0.5f;
    else
        beta = 0.05f;

    norm = sqrt(ax * ax + ay * ay + az * az);
    if (norm == 0.0f) return;
    norm = 1.0f/norm;
    ax *= norm;
    ay *= norm;
    az *= norm;

    // Normalise magnetometer measurement
    norm = sqrt(mx * mx + my * my + mz * mz);
    if (norm == 0.0f) { return; } // handle NaN
    norm = 1.0f/norm;
    mx *= norm;
    my *= norm;
    mz *= norm;

    // Reference direction of Earth's magnetic field
    _2q1mx = 2.0f * q1 * mx;
    _2q1my = 2.0f * q1 * my;
    _2q1mz = 2.0f * q1 * mz;
    _2q2mx = 2.0f * q2 * mx;
    hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
    hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
    _2bx = sqrt(hx * hx + hy * hy);
    _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
    _4bx = 2.0f * _2bx;
    _4bz = 2.0f * _2bz;

    // Gradient decent algorithm corrective step
    s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
    norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
    norm = 1.0f/norm;
    s1 *= norm;
    s2 *= norm;
    s3 *= norm;
    s4 *= norm;

    // Compute rate of change of quaternion
    qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
    qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
    qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
    qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

    // Integrate to yield quaternion
    q1 += qDot1 * deltat;
    q2 += qDot2 * deltat;
    q3 += qDot3 * deltat;
    q4 += qDot4 * deltat;
    norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
    norm = 1.0f / norm;
    q[0] = q1 * norm;
    q[1] = q2 * norm;
    q[2] = q3 * norm;
    q[3] = q4 * norm;
}


void quaternionToEuler()
{
    yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]),
                  q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
    pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
    roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]),
                  q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);

    roll  *= 180.0f / M_PI;
    pitch *= 180.0f / M_PI;
    yaw   *= 180.0f / M_PI;
    yaw   -= 7.5f; // 지역 자기편차 보정 (Declination)



    if (!offset_calibrated && runtime_ms < 100)
    {
        sum_yaw = yaw;
        sum_pitch = pitch;
        sum_roll = roll;
        sample_count++;
        runtime_ms++;

        if (runtime_ms == 100 && sample_count > 0)
        {
            offset_yaw = sum_yaw;
            offset_pitch = sum_pitch;
            offset_roll = sum_roll;
            offset_calibrated = true;

            print("Attitude Offset Calibrated: Yaw=%.2f, Pitch=%.2f, Roll=%.2f\n\r",
                  offset_yaw, offset_pitch, offset_roll);
        }
    }
    else if (offset_calibrated)
    {
        yaw   -= offset_yaw;
        pitch -= offset_pitch;
        roll  -= offset_roll;
    }
}
