#pragma once
#include <cstdint>
#include <cstddef>

class BLEPeripheral {
public:
    static void init(const char* device_name);

    // Envía un bloque binario por notify. No bloquea.
    // Retorna false si no hay conexión activa o la cola BLE está llena.
    static bool send(const uint8_t* data, size_t len);

    static bool connected();
};
