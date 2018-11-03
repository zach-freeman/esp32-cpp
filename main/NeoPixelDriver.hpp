#ifndef MAIN_NEOPIXELDRIVER_H_
#define MAIN_NEOPIXELDRIVER_H_
#include "WS2812.h"
#include "driver/gpio.h"
#include "esp_gap_bt_api.h"

class NeoPixelDriver
{
public:
    NeoPixelDriver();
    virtual ~NeoPixelDriver();
    static constexpr const char * NEOPIXEL_DRIVER_TAG = "NEOPIXEL_DRIVER";
    static constexpr const gpio_num_t NEOPIXEL_PIN = GPIO_NUM_21;
    static constexpr const uint16_t PIXEL_COUNT = 30;
    void setAllPixels(uint8_t redValue, uint8_t greenValue, uint8_t blueValue);
    void setChristmas();
    void testStrand();

private:
    WS2812 * neoPixelStrand;
    void startUp();
    uint32_t Wheel(uint8_t WheelPos);
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
};

#endif /* MAIN_NEOPIXELDRIVER_H_ */