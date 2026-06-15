#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "btstack.h"
#include <cstring>

#include "config.hpp"
#include "mpu6050.hpp"
#include "ble_peripheral.hpp"

// ------------------------------------------------------------------
// Formato del paquete binario (big-endian, 16 bytes por muestra):
//   [0..3]  timestamp uint32 (µs desde boot)
//   [4..5]  ax int16   → ÷ 16384.0 = g
//   [6..7]  ay int16
//   [8..9]  az int16
//  [10..11] gx int16   → ÷ 131.0 = °/s
//  [12..13] gy int16
//  [14..15] gz int16
// ------------------------------------------------------------------
static constexpr uint32_t SAMPLE_BYTES = 16;
static constexpr uint32_t PACKET_BYTES = SAMPLES_PER_PACKET * SAMPLE_BYTES;

static MPU6050* s_imu = nullptr;
static uint8_t  s_packet[PACKET_BYTES];
static uint32_t s_count = 0;

static btstack_timer_source_t s_sample_timer;
static btstack_timer_source_t s_led_timer;
static bool s_led_state = false;

// LED: parpadeo lento = advertising, luz fija = conectado
static void led_callback(btstack_timer_source_t* ts) {
    if (BLEPeripheral::connected()) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    } else {
        s_led_state = !s_led_state;
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, s_led_state ? 1 : 0);
    }
    btstack_run_loop_set_timer(ts, 500);
    btstack_run_loop_add_timer(ts);
}

static void append_sample(uint32_t ts_us, const IMUSample& s) {
    uint8_t* p = s_packet + s_count * SAMPLE_BYTES;
    p[0] = ts_us >> 24; p[1] = ts_us >> 16; p[2] = ts_us >> 8; p[3] = ts_us;
    auto put16 = [&](int off, int16_t v) {
        p[off]   = static_cast<uint8_t>(v >> 8);
        p[off+1] = static_cast<uint8_t>(v & 0xFF);
    };
    put16(4, s.ax); put16(6, s.ay); put16(8,  s.az);
    put16(10,s.gx); put16(12,s.gy); put16(14, s.gz);
    ++s_count;
}

static void sample_callback(btstack_timer_source_t* ts) {
    IMUSample sample;
    if (s_imu && s_imu->read(sample)) {
        uint32_t now_us = static_cast<uint32_t>(time_us_64());
        append_sample(now_us, sample);

        if (s_count >= SAMPLES_PER_PACKET) {
            if (BLEPeripheral::connected()) {
                BLEPeripheral::send(s_packet, PACKET_BYTES);
            }
            s_count = 0;
        }
    }

    // Re-arma el timer para la siguiente muestra
    btstack_run_loop_set_timer(ts, SAMPLE_INTERVAL_US / 1000);  // BTstack usa ms
    btstack_run_loop_add_timer(ts);
}

int main() {
    stdio_init_all();

    if (cyw43_arch_init() != 0) {
        while (true) tight_loop_contents();
    }

    // I2C
    i2c_init(I2C_PORT, I2C_FREQ);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    MPU6050 imu(I2C_PORT);
    imu.init();
    s_imu = &imu;

    BLEPeripheral::init(BLE_DEVICE_NAME);

    // Timer de muestreo
    btstack_run_loop_set_timer_handler(&s_sample_timer, sample_callback);
    btstack_run_loop_set_timer(&s_sample_timer, SAMPLE_INTERVAL_US / 1000);
    btstack_run_loop_add_timer(&s_sample_timer);

    // Timer de LED
    btstack_run_loop_set_timer_handler(&s_led_timer, led_callback);
    btstack_run_loop_set_timer(&s_led_timer, 500);
    btstack_run_loop_add_timer(&s_led_timer);

    btstack_run_loop_execute();
}
