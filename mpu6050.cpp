#include "mpu6050.hpp"
#include "hardware/i2c.h"

static constexpr uint8_t ADDR         = 0x68;
static constexpr uint8_t WHO_AM_I     = 0x75;
static constexpr uint8_t PWR_MGMT_1   = 0x6B;
static constexpr uint8_t SMPLRT_DIV   = 0x19;
static constexpr uint8_t CONFIG_REG   = 0x1A;
static constexpr uint8_t GYRO_CONFIG  = 0x1B;
static constexpr uint8_t ACCEL_CONFIG = 0x1C;
static constexpr uint8_t ACCEL_XOUT_H = 0x3B;

MPU6050::MPU6050(i2c_inst_t* i2c) : _i2c(i2c) {}

void MPU6050::write_reg(uint8_t reg, uint8_t val) {
    uint8_t buf[2] = {reg, val};
    i2c_write_blocking(_i2c, ADDR, buf, 2, false);
}

bool MPU6050::init() {
    // Verificar que el sensor responde con WHO_AM_I = 0x68
    uint8_t reg = WHO_AM_I;
    uint8_t who = 0;
    if (i2c_write_blocking(_i2c, ADDR, &reg, 1, true)  < 0) return false;
    if (i2c_read_blocking (_i2c, ADDR, &who, 1, false) < 0) return false;
    if (who != 0x68) return false;

    write_reg(PWR_MGMT_1,   0x01);
    write_reg(CONFIG_REG,   0x02);
    write_reg(SMPLRT_DIV,   0x04);
    write_reg(GYRO_CONFIG,  0x00);
    write_reg(ACCEL_CONFIG, 0x00);
    return true;
}

bool MPU6050::read(IMUSample& out) {
    uint8_t raw[14];
    uint8_t reg = ACCEL_XOUT_H;

    if (i2c_write_blocking(_i2c, ADDR, &reg, 1, true)  < 0) return false;
    if (i2c_read_blocking (_i2c, ADDR, raw, 14, false) < 0) return false;

    // Los registros son big-endian: ax(2) ay(2) az(2) temp(2) gx(2) gy(2) gz(2)
    auto be16 = [&](int i) -> int16_t {
        return static_cast<int16_t>((raw[i] << 8) | raw[i + 1]);
    };
    out.ax = be16(0);  out.ay = be16(2);  out.az = be16(4);
    // raw[6..7] = temperatura, se descarta
    out.gx = be16(8);  out.gy = be16(10); out.gz = be16(12);
    return true;
}
