# Esp32 - Messing around with bluetooth and neopixels


This example demonstrates usage of bluetooth and neopixels on esp

By default, C++ exceptions support is disabled in ESP-IDF. It can be enabled using `CONFIG_CXX_EXCEPTIONS` configuration option.

In this example, `sdkconfig.defaults` file sets `CONFIG_CXX_EXCEPTIONS` option. This enables both compile time support (`-fexceptions` compiler flag) and run-time support for C++ exception handling.

Example source code declares a class which can start a bluetooth server and turn neopixels on and off 

## How to use example

### Configure the project

Run `make menuconfig` and set serial port under Serial Flasher Options.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
make -j4 flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

```
app_main starting
In constructor, arg=42
In constructor, arg=0
In destructor, m_arg=42
Exception caught: Exception in constructor
app_main done
```

