#include "HttpServerInitializer.hpp"
#include "HttpServerHandler.hpp"
#include "PrivateConstants.hpp"

/**
 * Create a new Http server.
 */

#include "esp_log.h"
#include <WiFi.h>
#include <string>

#include <sstream>
#include <sys/time.h>

#include "sdkconfig.h"

static WiFi * wifi;
HttpServerHandler * HttpServerInitializer::httpServerHandler;

HttpServerInitializer::HttpServerInitializer()
{
}

HttpServerInitializer::~HttpServerInitializer()
{
    free(wifi);
}

void HttpServerInitializer::startUp()
{

    esp_log_level_set("*", ESP_LOG_DEBUG);

    wifi = new WiFi();
    httpServerHandler = new HttpServerHandler();

    wifi->connectAP(PrivateConstants::WIFI_SSID, PrivateConstants::WIFI_PASSWORD);

    HttpServer * httpServer = new HttpServer();
    httpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, HttpServerHandler::LIGHT_ON_PATH, httpServerHandler->lightOn);
    httpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, HttpServerHandler::LIGHT_OFF_PATH, httpServerHandler->lightOff);
    httpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, HttpServerHandler::LIGHT_STATUS_PATH, httpServerHandler->lightStatus);
    httpServer->addPathHandler(HttpRequest::HTTP_METHOD_GET, HttpServerHandler::CHRISTMAS_PATH, httpServerHandler->christmas);

    httpServer->start(80);
}
