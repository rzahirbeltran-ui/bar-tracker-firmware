#pragma once
#include "hardware/i2c.h"

// I2C — MPU6050
inline constexpr uint  I2C_SDA    = 4;
inline constexpr uint  I2C_SCL    = 5;
inline constexpr uint  I2C_FREQ   = 400'000;
#define I2C_PORT i2c0

// Muestreo
inline constexpr uint32_t SAMPLE_RATE_HZ     = 200;
inline constexpr uint32_t SAMPLE_INTERVAL_US = 1'000'000 / SAMPLE_RATE_HZ;  // 5 000 µs
inline constexpr uint32_t SAMPLES_PER_PACKET = 1;

// BLE
inline constexpr char BLE_DEVICE_NAME[] = "BarTracker";

// Factores de escala (para que la app convierta raw → unidades físicas)
inline constexpr float ACCEL_SCALE = 1.0f / 16384.0f;  // g por LSB  (rango ±2g)
inline constexpr float GYRO_SCALE  = 1.0f / 131.0f;    // °/s por LSB (rango ±250°/s)
