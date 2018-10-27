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

bool HttpServerHandler::areLightsOn;
NeoPixelDriver *HttpServerHandler::neoPixelDriver;

HttpServerHandler::HttpServerHandler()
{
    neoPixelDriver = new NeoPixelDriver();
    areLightsOn = false;
}

HttpServerHandler::~HttpServerHandler()
{

}

void HttpServerHandler::lightOn(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Light On");
    neoPixelDriver->setAllPixels(128, 128, 128);
    areLightsOn = true;
    pResponse->close();
}

void HttpServerHandler::lightOff(HttpRequest* pRequest, HttpResponse* pResponse)
{
    pResponse->setStatus(HttpResponse::HTTP_STATUS_OK, "OK");
    pResponse->addHeader(HttpRequest::HTTP_HEADER_CONTENT_TYPE, "text/plain");
    pResponse->sendData("Light Off");
    neoPixelDriver->setAllPixels(0, 0, 0);
    areLightsOn = false;
    pResponse->close();
}

void HttpServerHandler::lightStatus(HttpRequest *pRequest, HttpResponse* pResponse)
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