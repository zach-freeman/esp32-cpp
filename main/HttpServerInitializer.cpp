#include "HttpServerInitializer.hpp"
#include "HttpServerHandler.hpp"

/**
 * Create a new Http server.
 */

#include <string>
#include <WiFi.h>
#include "esp_log.h"



#include <sys/time.h>
#include <sstream>


#include "sdkconfig.h"

static WiFi *wifi;

bool HttpServerInitializer::areLightsOn;
NeoPixelDriver *HttpServerInitializer::neoPixelDriver;


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
    HttpServerHandler httpServerHandler;

	wifi->connectAP("nope", "nope");

    HttpServer *httpServer = new HttpServer();
    httpServer->addPathHandler(
            HttpRequest::HTTP_METHOD_GET,
            HttpServerHandler::LIGHT_ON_PATH,
            httpServerHandler.lightOn);
    httpServer->addPathHandler(
            HttpRequest::HTTP_METHOD_GET,
            HttpServerHandler::LIGHT_OFF_PATH,
            httpServerHandler.lightOff);
    httpServer->addPathHandler(
            HttpRequest::HTTP_METHOD_GET,
            HttpServerHandler::LIGHT_STATUS_PATH,
            httpServerHandler.lightStatus);
    httpServer->start(80);
 
}



