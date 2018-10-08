/*
 * 1. Open up the project properties
 * 2. Visit C/C++ General > Preprocessor Include Paths, Macros, etc
 * 3. Select the Providers tab
 * 4. Check the box for "CDT GCC Built-in Compiler Settings"
 * 5. Set the compiler spec command to "xtensa-esp32-elf-gcc ${FLAGS} -E -P -v -dD "${INPUTS}""
 * 6. Rebuild the index
*/

#include <string>

#include <iostream>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "BluetoothDriver.hpp"


using std::cout;
using std::endl;


static char tag[]="cpp_helloworld";

extern "C" {
	void app_main(void);
}


void app_main(void)
{
	esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK( ret );

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK)
    {
         ESP_LOGE(tag, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));
         return;
    }
    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_BLE)) != ESP_OK)
    {
         ESP_LOGE(tag, "%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));
         return;
    }
    BluetoothDriver bluetooth;
    bluetooth.startUp();
}
