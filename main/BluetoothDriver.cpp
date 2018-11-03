#include "BluetoothDriver.hpp"

/**
 * Create a new BLE server.
 */
#include "BLE2902.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include <Task.h>
#include <esp_log.h>
#include <string>

#include <sstream>
#include <sys/time.h>

#include "sdkconfig.h"

static char LOG_TAG[] = "SampleServer";

class MyCallbackHandler : public BLECharacteristicCallbacks
{
public:
    NeoPixelDriver * myNeoPixelDriver;
    bool areLightsOn;

    MyCallbackHandler()
    {
        myNeoPixelDriver = new NeoPixelDriver();
        areLightsOn = false;
    }

    virtual ~MyCallbackHandler()
    {
        delete myNeoPixelDriver;
    }

    void onRead(BLECharacteristic * pCharacteristic)
    {
        if (!areLightsOn)
        {
            areLightsOn = true;
            myNeoPixelDriver->setAllPixels(128, 128, 128);
            pCharacteristic->setValue("Light On");
        }
        else
        {
            areLightsOn = false;
            myNeoPixelDriver->setAllPixels(0, 0, 0);
            pCharacteristic->setValue("Light Off");
        }
    }

    void onWrite(BLECharacteristic * pCharacteristic)
    {
        areLightsOn = true;
        pCharacteristic->setValue("Party");
        myNeoPixelDriver->testStrand();
    }
};

class MainBLEServer : public Task
{
    void run(void * data)
    {
        ESP_LOGD(LOG_TAG, "Starting BLE work!");

        BLEDevice::init("ESP32");
        BLEServer * pServer = BLEDevice::createServer();

        BLEService * pService = pServer->createService(BluetoothDriver::SERVER_UUID);

        BLECharacteristic * pCharacteristic =
            pService->createCharacteristic(BLEUUID("0d563a58-196a-48ce-ace2-dfec78acc814"),
                                           BLECharacteristic::PROPERTY_BROADCAST | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY |
                                               BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_INDICATE);

        pCharacteristic->setValue("Hello World!");
        pCharacteristic->setCallbacks(new MyCallbackHandler());

        BLE2902 * p2902Descriptor = new BLE2902();
        p2902Descriptor->setNotifications(true);
        pCharacteristic->addDescriptor(p2902Descriptor);

        pService->start();

        BLEAdvertising * pAdvertising = pServer->getAdvertising();
        pAdvertising->addServiceUUID(BLEUUID(pService->getUUID()));
        pAdvertising->start();

        ESP_LOGD(LOG_TAG, "Advertising started!");
        delay(1000000);
    }
};

BluetoothDriver::BluetoothDriver()
{
}

BluetoothDriver::~BluetoothDriver()
{
}

void BluetoothDriver::startUp()
{

    // esp_log_level_set("*", ESP_LOG_DEBUG);
    MainBLEServer * pMainBleServer = new MainBLEServer();
    pMainBleServer->setStackSize(20000);
    pMainBleServer->start();
}
