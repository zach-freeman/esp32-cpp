set(CMAKE_C_FLAGS "-D LOG_LOCAL_LEVEL=ESP_LOG_DEBUG")

set(COMPONENT_SRCS Main.cpp HttpServerInitializer.cpp HttpServerHandler.cpp NeoPixelDriver.cpp NtpClient.cpp)
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()
