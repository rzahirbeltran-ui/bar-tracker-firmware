cmake_minimum_required(VERSION 3.13)

# ── Setup en Windows ──────────────────────────────────────────────────
# Opción A (recomendada): extensión "Raspberry Pi Pico" en VS Code.
#   Import Project → selecciona esta carpeta → Build.
#
# Opción B (terminal con Ninja):
#   cd firmware
#   mkdir build && cd build
#   cmake .. -G Ninja -DPICO_BOARD=pico_w -DPICO_SDK_PATH="C:/ruta/pico-sdk"
#   ninja                     ← en vez de make
#   # Arrastra build/bar_tracker.uf2 al Pico W en modo BOOTSEL
#
# pico_sdk_import.cmake debe estar en este directorio.
# Cópialo desde: %PICO_SDK_PATH%\external\pico_sdk_import.cmake
# ─────────────────────────────────────────────────────────────────────
include(pico_sdk_import.cmake)

project(bar_tracker C CXX ASM)
set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(bar_tracker
    main.cpp
    mpu6050.cpp
    ble_peripheral.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bar_tracker.gatt   # hace que CMake dependa del archivo
)

target_include_directories(bar_tracker PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}   # aquí va el bar_tracker.h generado
)

target_link_libraries(bar_tracker
    pico_stdlib
    hardware_i2c
    hardware_adc
    pico_cyw43_arch_none   # BLE-only: sin lwIP, BTstack maneja su propio run loop
    pico_btstack_ble
    pico_btstack_cyw43
)

# Genera bar_tracker.h con los handles GATT a partir de bar_tracker.gatt
pico_btstack_make_gatt_header(bar_tracker PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/bar_tracker.gatt")

# Salidas: .uf2 (flasheable por drag-and-drop), .hex, .bin, .map
pico_add_extra_outputs(bar_tracker)

# Debug por USB; deshabilita UART para no usar pines extra
pico_enable_stdio_usb (bar_tracker 1)
pico_enable_stdio_uart(bar_tracker 0)
