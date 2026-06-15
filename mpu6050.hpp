#pragma once
#include "hardware/i2c.h"
#include <cstdint>

struct IMUSample {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
};

class MPU6050 {
public:
    explicit MPU6050(i2c_inst_t* i2c);
    bool init();
    bool read(IMUSample& out);

private:
    i2c_inst_t* _i2c;
    void write_reg(uint8_t reg, uint8_t val);
};
