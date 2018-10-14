
#include "NeoPixelDriver.hpp"

#include <cstring>

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



using std::cout;
using std::endl;

NeoPixelDriver::NeoPixelDriver()
{
    neoPixelStrand = new WS2812(NEOPIXEL_PIN, PIXEL_COUNT);
    startUp();
}

NeoPixelDriver::~NeoPixelDriver()
{
    delete neoPixelStrand;
}

void NeoPixelDriver::startUp()
{
    uint8_t redChannel = 0;
    uint8_t greenChannel = 0;
    uint8_t blueChannel = 0;
    setAllPixels(redChannel, greenChannel, blueChannel);
}

void NeoPixelDriver::setAllPixels(uint8_t redValue, uint8_t greenValue, uint8_t blueValue)
{
    for (int i = 0; i < PIXEL_COUNT; i++)
    { // do something to all the neopixels
        neoPixelStrand->setPixel(i, redValue, greenValue, blueValue);
    }
    neoPixelStrand->show();
}





