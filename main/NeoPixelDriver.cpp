
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

void NeoPixelDriver::testStrand()
{
    for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < PIXEL_COUNT; i=i+3) {
                uint32_t pixelColor = Wheel( (i+j) % 255);
                neoPixelStrand->setPixel(i+q, pixelColor, pixelColor, pixelColor);    //turn every third pixel on
            }
        neoPixelStrand->show();

        vTaskDelay(50/portTICK_PERIOD_MS);

      for (uint16_t i=0; i < PIXEL_COUNT; i=i+3) {
        neoPixelStrand->setPixel(i+q, 0, 0, 0);        //turn every third pixel off
      }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t NeoPixelDriver::Wheel(uint8_t wheelPosition) 
{
  wheelPosition = 255 - wheelPosition;
  if(wheelPosition < 85) {
    return Color(255 - wheelPosition * 3, 0, wheelPosition * 3);
  }
  if(wheelPosition < 170) {
    wheelPosition -= 85;
    return Color(0, wheelPosition * 3, 255 - wheelPosition * 3);
  }
  wheelPosition -= 170;
  return Color(wheelPosition * 3, 255 - wheelPosition * 3, 0);
}

uint32_t NeoPixelDriver::Color(uint8_t r, uint8_t g, uint8_t b) 
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}





