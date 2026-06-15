#include "ble_peripheral.hpp"
#include "bar_tracker.h"   // Generado por compile_gatt.py (CMake lo produce en build/)

#include "pico/cyw43_arch.h"
#include "pico/btstack_cyw43.h"
#include "btstack.h"

static constexpr uint16_t NUS_TX_VALUE_HANDLE =
    ATT_CHARACTERISTIC_6E400003_B5A3_F393_E0A9_E50E24DCCA9E_01_VALUE_HANDLE;

static hci_con_handle_t s_conn = HCI_CON_HANDLE_INVALID;
static btstack_packet_callback_registration_t s_hci_cb;

static const uint8_t ADV_DATA[] = {
    0x02, 0x01, 0x06,                                          // Flags: LE General Discoverable
    0x0B, 0x09, 'B','a','r','T','r','a','c','k','e','r'       // Complete Local Name
};

static void packet_handler(uint8_t pkt_type, uint16_t /*channel*/,
                            uint8_t* pkt, uint16_t /*size*/) {
    if (pkt_type != HCI_EVENT_PACKET) return;

    switch (hci_event_packet_get_type(pkt)) {
        case HCI_EVENT_LE_META:
            if (hci_event_le_meta_get_subevent_code(pkt) ==
                HCI_SUBEVENT_LE_CONNECTION_COMPLETE) {
                s_conn = hci_subevent_le_connection_complete_get_connection_handle(pkt);
            }
            break;
        case HCI_EVENT_DISCONNECTION_COMPLETE:
            s_conn = HCI_CON_HANDLE_INVALID;
            gap_advertisements_enable(1);
            break;
        default:
            break;
    }
}

void BLEPeripheral::init(const char* /*device_name*/) {
    l2cap_init();
    sm_init();
    att_server_init(profile_data, nullptr, nullptr);

    s_hci_cb.callback = packet_handler;
    hci_add_event_handler(&s_hci_cb);

    gap_advertisements_set_params(0x0030, 0x0030, 0, 0, nullptr, 0x07, 0x00);
    gap_advertisements_set_data(sizeof(ADV_DATA), const_cast<uint8_t*>(ADV_DATA));
    gap_advertisements_enable(1);

    hci_power_control(HCI_POWER_ON);
}

bool BLEPeripheral::connected() {
    return s_conn != HCI_CON_HANDLE_INVALID;
}

bool BLEPeripheral::send(const uint8_t* data, size_t len) {
    if (s_conn == HCI_CON_HANDLE_INVALID) return false;
    int rc = att_server_notify(s_conn, NUS_TX_VALUE_HANDLE, data, static_cast<uint16_t>(len));
    return rc == ERROR_CODE_SUCCESS;
}
