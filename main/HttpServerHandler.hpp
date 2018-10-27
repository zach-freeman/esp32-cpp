#ifndef MAIN_HTTP_SERVER_HANDLER_H
#define MAIN_HTTP_SERVER_HANDLER_H
#include "esp_gap_bt_api.h"
#include "NeoPixelDriver.hpp"
#include "HttpServer.h"


class HttpServerHandler {
public:
    HttpServerHandler();
    virtual ~HttpServerHandler();
    static void lightOn(HttpRequest* pRequest, HttpResponse* pResponse);
    static void lightOff(HttpRequest* pRequest, HttpResponse* pResponse);
    static void lightStatus(HttpRequest *pRequest, HttpResponse* pResponse);

private:
    static NeoPixelDriver *neoPixelDriver;
    static bool areLightsOn;
    static constexpr const char * HTTP_SERVER_INTIALIZER_TAG = "HTTP_SERVER_HANDLER";
};

#endif /* MAIN_HTTP_SERVER_HANDLER_H */