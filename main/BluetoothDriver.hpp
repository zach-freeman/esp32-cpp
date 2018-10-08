#include "esp_gap_bt_api.h"


typedef enum {
    APP_GAP_STATE_IDLE = 0,
    APP_GAP_STATE_DEVICE_DISCOVERING,
    APP_GAP_STATE_DEVICE_DISCOVER_COMPLETE,
    APP_GAP_STATE_SERVICE_DISCOVERING,
    APP_GAP_STATE_SERVICE_DISCOVER_COMPLETE,
} app_gap_state_t;

typedef struct {
    bool dev_found;
    uint8_t bdname_len;
    uint8_t eir_len;
    uint8_t rssi;
    uint32_t cod;
    uint8_t eir[ESP_BT_GAP_EIR_DATA_LEN];
    uint8_t bdname[ESP_BT_GAP_MAX_BDNAME_LEN + 1];
    esp_bd_addr_t bda;
    app_gap_state_t state;
} app_gap_cb_t;

class BluetoothDriver {
public:
    BluetoothDriver();
    virtual ~BluetoothDriver() {};
	static void startUp();
    static void bluetoothAppGapCallback(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);
    static void updateDeviceInfo(esp_bt_gap_cb_param_t *param);
    static char *bda2str(esp_bd_addr_t bda, char *str, size_t size);
    static char *uuid2str(esp_bt_uuid_t *uuid, char *str, size_t size);
    static bool getNameFromEir(uint8_t *eir, uint8_t *bdname, uint8_t *bdname_len);
    static app_gap_cb_t m_dev_info;
    static constexpr const char * GAP_TAG = "hello";
};