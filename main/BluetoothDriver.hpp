#ifndef MAIN_BLUETOOTHDRIVER_H_
#define MAIN_BLUETOOTHDRIVER_H_
#include "esp_gap_bt_api.h"


class BluetoothDriver {
public:
    BluetoothDriver();
    virtual ~BluetoothDriver() {};
	static void startUp();
    static constexpr const char *SERVER_UUID = "b751e956-2864-4e0e-939e-263831e56354";

private:
    static constexpr const char * BLUETOOTH_DRIVER_TAG = "BLUETOOTH_DRIVER";

};

#endif /* MAIN_BLUETOOTHDRIVER_H_ */