#include "HttpServerInitializer.hpp"

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
}

void HttpServerInitializer::lightOnHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Light On");
    neoPixelDriver->setAllPixels(128, 128, 128);
    areLightsOn = true;
    pResponse->close();
}

void HttpServerInitializer::lightOffHandler(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Light Off");
    neoPixelDriver->setAllPixels(0, 0, 0);
    areLightsOn = false;
    pResponse->close();
}

void HttpServerInitializer::startUp()
{

	esp_log_level_set("*", ESP_LOG_DEBUG);
    
	wifi = new WiFi();
    neoPixelDriver = new NeoPixelDriver();
    areLightsOn = false;

	wifi->connectAP("nope", "nope");

    HttpServer *httpServer = new HttpServer();
    httpServer->addPathHandler(
            HttpRequest::HTTP_METHOD_GET,
            "/lightOn",
            lightOnHandler);
    httpServer->addPathHandler(
            HttpRequest::HTTP_METHOD_GET,
            "/lightOff",
            lightOffHandler);
    httpServer->start(80);
 
}



