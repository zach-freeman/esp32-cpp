#include "HttpServerHandler.hpp"

/**
 * Create a new Http server.
 */

#include "esp_log.h"
#include <WiFi.h>
#include <string>

#include <sstream>
#include <sys/time.h>

#include "sdkconfig.h"

bool HttpServerHandler::areLightsOn;
NeoPixelDriver * HttpServerHandler::neoPixelDriver;
constexpr char HttpServerHandler::LIGHT_ON_PATH[];
constexpr char HttpServerHandler::LIGHT_OFF_PATH[];
constexpr char HttpServerHandler::LIGHT_STATUS_PATH[];
constexpr char HttpServerHandler::CHRISTMAS_PATH[];

HttpServerHandler::HttpServerHandler()
{
    neoPixelDriver = new NeoPixelDriver();
    areLightsOn = false;
}

HttpServerHandler::~HttpServerHandler()
{
    free(neoPixelDriver);
}

void HttpServerHandler::lightOn(HttpRequest * pRequest, HttpResponse * pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Light On");
    neoPixelDriver->setAllPixels(128, 128, 128);
    areLightsOn = true;
    pResponse->close();
}

void HttpServerHandler::lightOff(HttpRequest * pRequest, HttpResponse * pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Light Off");
    neoPixelDriver->setAllPixels(0, 0, 0);
    areLightsOn = false;
    pResponse->close();
}

void HttpServerHandler::lightStatus(HttpRequest * pRequest, HttpResponse * pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    if (areLightsOn)
    {
        pResponse->sendData("On");
    }
    else
    {
        pResponse->sendData("Off");
    }
    pResponse->close();
}

void HttpServerHandler::christmas(HttpRequest * pRequest, HttpResponse * pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("HO HO HO");
    neoPixelDriver->setChristmas();
    areLightsOn = true;
    pResponse->close();
}