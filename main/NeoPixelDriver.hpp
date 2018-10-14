#ifndef MAIN_NEOPIXELDRIVER_H_
#define MAIN_NEOPIXELDRIVER_H_
#include "esp_gap_bt_api.h"
#include "WS2812.h"
#include "driver/gpio.h"



class NeoPixelDriver {
public:
    NeoPixelDriver();
    virtual ~NeoPixelDriver();
    static constexpr const char * NEOPIXEL_DRIVER_TAG = "NEOPIXEL_DRIVER";
    static constexpr const gpio_num_t NEOPIXEL_PIN = GPIO_NUM_21;
    static constexpr const uint16_t PIXEL_COUNT = 30;
    void setAllPixels(uint8_t redValue, uint8_t greenValue, uint8_t blueValue);
private:
    WS2812 *neoPixelStrand;
    void startUp();

};

#endif /* MAIN_NEOPIXELDRIVER_H_ */