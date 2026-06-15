#ifndef BTSTACK_CONFIG_H
#define BTSTACK_CONFIG_H

// Pico W tiene malloc
#define HAVE_MALLOC

// Solo BLE, sin Bluetooth Classic
#define ENABLE_BLE
#define ENABLE_LE_PERIPHERAL

// Seguridad (necesario para el SM aunque no usemos pairing)
#define ENABLE_SOFTWARE_AES128
#define ENABLE_MICRO_ECC_FOR_LE_SECURE_CONNECTIONS

// Log por USB-UART (stdio)
#define ENABLE_LOG_ERROR
#define ENABLE_LOG_INFO
#define ENABLE_PRINTF_HEXDUMP

// Buffers HCI — requeridos por el transporte CYW43
#define HCI_ACL_PAYLOAD_SIZE          (255 + 4)
#define HCI_OUTGOING_PRE_BUFFER_SIZE  4     // CYW43_PACKET_HEADER_SIZE
#define HCI_ACL_CHUNK_SIZE_ALIGNMENT  4     // debe ser múltiplo de 4

// Límites de recursos — 1 conexión simultánea
#define MAX_NR_HCI_CONNECTIONS         1
#define MAX_NR_L2CAP_SERVICES          2
#define MAX_NR_L2CAP_CHANNELS          3
#define MAX_NR_SM_LOOKUP_ENTRIES       3
#define MAX_NR_WHITELIST_ENTRIES       1
#define MAX_NR_LE_DEVICE_DB_ENTRIES    1
#define NVM_NUM_DEVICE_DB_ENTRIES      1

#endif
