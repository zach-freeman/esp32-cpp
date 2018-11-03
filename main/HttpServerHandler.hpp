#ifndef MAIN_HTTP_SERVER_HANDLER_H
#define MAIN_HTTP_SERVER_HANDLER_H
#include "HttpServer.h"
#include "NeoPixelDriver.hpp"
#include "esp_gap_bt_api.h"

class HttpServerHandler
{
public:
    HttpServerHandler();
    virtual ~HttpServerHandler();
    static void lightOn(HttpRequest * pRequest, HttpResponse * pResponse);
    static void lightOff(HttpRequest * pRequest, HttpResponse * pResponse);
    static void lightStatus(HttpRequest * pRequest, HttpResponse * pResponse);
    static void christmas(HttpRequest * pRequest, HttpResponse * pResponse);

    static constexpr char LIGHT_ON_PATH[]{"/lightOn"};
    static constexpr char LIGHT_OFF_PATH[]{"/lightOff"};
    static constexpr char LIGHT_STATUS_PATH[]{"/lightStatus"};
    static constexpr char CHRISTMAS_PATH[]{"/christmas"};

private:
    static NeoPixelDriver * neoPixelDriver;
    static bool areLightsOn;
    static constexpr const char * HTTP_SERVER_INTIALIZER_TAG = "HTTP_SERVER_HANDLER";
};

#endif /* MAIN_HTTP_SERVER_HANDLER_H */