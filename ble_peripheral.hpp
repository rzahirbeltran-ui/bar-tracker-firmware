#pragma once
#include <cstdint>
#include <cstddef>

class BLEPeripheral {
public:
    static void init(const char* device_name);
    static bool send(const uint8_t* data, size_t len);
    static bool connected();
    static void set_battery(uint8_t pct);  // 0–100
};
