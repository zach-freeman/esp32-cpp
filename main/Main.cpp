/*
 * 1. Open up the project properties
 * 2. Visit C/C++ General > Preprocessor Include Paths, Macros, etc
 * 3. Select the Providers tab
 * 4. Check the box for "CDT GCC Built-in Compiler Settings"
 * 5. Set the compiler spec command to "xtensa-esp32-elf-gcc ${FLAGS} -E -P -v -dD "${INPUTS}""
 * 6. Rebuild the index
 */

#include <string>

#include "HttpServerInitializer.hpp"
#include "esp_bt.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <iostream>
#include "NtpClient.hpp"

extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_VERBOSE);  
    HttpServerInitializer httpServerInitializer;
    httpServerInitializer.startUp();
    //NtpClient ntpClient;
}
