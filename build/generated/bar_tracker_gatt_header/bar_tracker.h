
// clang-format off
// C:/Users/rzahi/OneDrive/Desktop/Tracker/firmware/build/generated/bar_tracker_gatt_header/bar_tracker.h generated from C:/Users/rzahi/OneDrive/Desktop/Tracker/firmware/bar_tracker.gatt for BTstack
// it needs to be regenerated when the .gatt file is updated. 

// To generate C:/Users/rzahi/OneDrive/Desktop/Tracker/firmware/build/generated/bar_tracker_gatt_header/bar_tracker.h:
// C:/pico-sdk/lib/btstack/tool/compile_gatt.py C:/Users/rzahi/OneDrive/Desktop/Tracker/firmware/bar_tracker.gatt C:/Users/rzahi/OneDrive/Desktop/Tracker/firmware/build/generated/bar_tracker_gatt_header/bar_tracker.h

// att db format version 1

// binary attribute representation:
// - size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#include <stdint.h>

// Reference: https://en.cppreference.com/w/cpp/feature_test
#if __cplusplus >= 200704L
constexpr
#endif
const uint8_t profile_data[] =
{
    // ATT DB Version
    1,

    // GATT database — BarTracker
    // compile_gatt.py genera bar_tracker.h con los handles de los atributos
    // 0x0001 PRIMARY_SERVICE-GAP_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18, 
    // 0x0002 CHARACTERISTIC-GAP_DEVICE_NAME - READ
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a, 
    // 0x0003 VALUE CHARACTERISTIC-GAP_DEVICE_NAME - READ -'BarTracker'
    // READ_ANYBODY
    0x12, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x2a, 0x42, 0x61, 0x72, 0x54, 0x72, 0x61, 0x63, 0x6b, 0x65, 0x72, 
    // 0x0004 PRIMARY_SERVICE-GATT_SERVICE
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x01, 0x18, 
    // 0x0005 CHARACTERISTIC-GATT_SERVICE_CHANGED - INDICATE
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x20, 0x06, 0x00, 0x05, 0x2a, 
    // 0x0006 VALUE CHARACTERISTIC-GATT_SERVICE_CHANGED - INDICATE -''
    // 
    0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x05, 0x2a, 
    // 0x0007 CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x07, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // Nordic UART Service (NUS) — ampliamente soportado en iOS
    // 0x0008 PRIMARY_SERVICE-6E400001-B5A3-F393-E0A9-E50E24DCCA9E
    0x18, 0x00, 0x02, 0x00, 0x08, 0x00, 0x00, 0x28, 0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e, 
    // 0x0009 CHARACTERISTIC-6E400003-B5A3-F393-E0A9-E50E24DCCA9E - NOTIFY
    0x1b, 0x00, 0x02, 0x00, 0x09, 0x00, 0x03, 0x28, 0x10, 0x0a, 0x00, 0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x03, 0x00, 0x40, 0x6e, 
    // 0x000a VALUE CHARACTERISTIC-6E400003-B5A3-F393-E0A9-E50E24DCCA9E - NOTIFY -''
    // 
    0x16, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x03, 0x00, 0x40, 0x6e, 
    // 0x000b CLIENT_CHARACTERISTIC_CONFIGURATION
    // READ_ANYBODY, WRITE_ANYBODY
    0x0a, 0x00, 0x0e, 0x01, 0x0b, 0x00, 0x02, 0x29, 0x00, 0x00, 
    // END
    0x00, 0x00, 
}; // total size 99 bytes 


//
// list service handle ranges
//
#define ATT_SERVICE_GAP_SERVICE_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_END_HANDLE 0x0003
#define ATT_SERVICE_GAP_SERVICE_01_START_HANDLE 0x0001
#define ATT_SERVICE_GAP_SERVICE_01_END_HANDLE 0x0003
#define ATT_SERVICE_GATT_SERVICE_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_END_HANDLE 0x0007
#define ATT_SERVICE_GATT_SERVICE_01_START_HANDLE 0x0004
#define ATT_SERVICE_GATT_SERVICE_01_END_HANDLE 0x0007
#define ATT_SERVICE_6E400001_B5A3_F393_E0A9_E50E24DCCA9E_START_HANDLE 0x0008
#define ATT_SERVICE_6E400001_B5A3_F393_E0A9_E50E24DCCA9E_END_HANDLE 0x000b
#define ATT_SERVICE_6E400001_B5A3_F393_E0A9_E50E24DCCA9E_01_START_HANDLE 0x0008
#define ATT_SERVICE_6E400001_B5A3_F393_E0A9_E50E24DCCA9E_01_END_HANDLE 0x000b

//
// list mapping between characteristics and handles
//
#define ATT_CHARACTERISTIC_GAP_DEVICE_NAME_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_GATT_SERVICE_CHANGED_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_GATT_SERVICE_CHANGED_01_CLIENT_CONFIGURATION_HANDLE 0x0007
#define ATT_CHARACTERISTIC_6E400003_B5A3_F393_E0A9_E50E24DCCA9E_01_VALUE_HANDLE 0x000a
#define ATT_CHARACTERISTIC_6E400003_B5A3_F393_E0A9_E50E24DCCA9E_01_CLIENT_CONFIGURATION_HANDLE 0x000b
