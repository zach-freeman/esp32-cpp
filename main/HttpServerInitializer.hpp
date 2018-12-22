#ifndef MAIN_HTTP_SERVER_INITIALIZER_INCLUDED_H
#define MAIN_HTTP_SERVER_INITIALIZER_INCLUDED_H
#include "HttpServer.h"
#include "HttpServerHandler.hpp"
#include "esp_gap_bt_api.h"

class HttpServerInitializer
{
public:
    HttpServerInitializer();
    virtual ~HttpServerInitializer();
    static void startUp();

private:
    static constexpr const char * HTTP_SERVER_INTIALIZER_TAG = "HTTP_SERVER_INITIALIZER";
    static HttpServerHandler  * httpServerHandler;
};

#endif /* MAIN_HTTP_SERVER_INITIALIZER_INCLUDED_H */