#ifndef MAIN_HTTP_SERVER_INITIALIZER_INCLUDED_H
#define MAIN_HTTP_SERVER_INITIALIZER_INCLUDED_H
#include "esp_gap_bt_api.h"
#include "NeoPixelDriver.hpp"
#include "HttpServer.h"


class HttpServerInitializer {
public:
    HttpServerInitializer();
    virtual ~HttpServerInitializer();
	static void startUp();

private:
    static NeoPixelDriver *neoPixelDriver;
    static bool areLightsOn;
    static constexpr const char * HTTP_SERVER_INTIALIZER_TAG = "HTTP_SERVER_INITIALIZER";
    static void lightOnHandler(HttpRequest* pRequest, HttpResponse* pResponse);
    static void lightOffHandler(HttpRequest* pRequest, HttpResponse* pResponse);

};

#endif /* MAIN_HTTP_SERVER_INITIALIZER_INCLUDED_H */