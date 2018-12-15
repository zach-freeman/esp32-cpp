
#include "NtpClient.hpp"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <arpa/inet.h>
#include <ctime>

Socket * NtpClient::ntpSocket;
NtpClient::NtpClient()
{
    connect();

    vTaskDelay(100 / portTICK_PERIOD_MS);

    getCurrentTime();
}

NtpClient::~NtpClient()
{
    ESP_LOGI(NTP_CLIENT_TAG, "destroy ntp client");
    ntpSocket->close();
    free(ntpSocket);
}

void NtpClient::connect()
{
    ntpSocket = new Socket();

    ESP_LOGE(NTP_CLIENT_TAG, "ntp socket created");
    int isConnected = ntpSocket->connect(NTP_SERVER_ADDRESS, NTP_UDP_PORT_NUMBER);
}

void NtpClient::getCurrentTime()
{
    ESP_LOGE(NTP_CLIENT_TAG, "connected to ntp server");
    ntp_packet ntpPacket = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    memset( &ntpPacket, 0, sizeof( ntp_packet ) );

    // Set the first byte's bits to 00,011,011 for li = 0, vn = 3, and mode = 3. The rest will be left set to zero.

    *( ( char * ) &ntpPacket + 0 ) = 0x1b; // Represents 27 in base 10 or 00011011 in base 2.
    int isPacketSent = ntpSocket->send((uint8_t*)&ntpPacket, sizeof(ntp_packet));
    if (isPacketSent >= 0)
    {
        ESP_LOGE(NTP_CLIENT_TAG, "sent the ntp packet");
        size_t receivedDataSize = ntpSocket->receive((uint8_t*)&ntpPacket, sizeof(ntp_packet));
        if (receivedDataSize > 0)
        {
            ESP_LOGE(NTP_CLIENT_TAG, "got some data back from the ntp server");
            ESP_LOGI(NTP_CLIENT_TAG, "data size is %d", receivedDataSize);
            // These two fields contain the time-stamp seconds as the packet left the NTP server.
            // The number of seconds correspond to the seconds passed since 1900.
            // ntohl() converts the bit/byte order from the network's to host's "endianness".

            ntpPacket.txTm_s = ntohl( ntpPacket.txTm_s ); // Time-stamp seconds.
            ntpPacket.txTm_f = ntohl( ntpPacket.txTm_f ); // Time-stamp fraction of a second.

            // Extract the 32 bits that represent the time-stamp seconds (since NTP epoch) from when the packet left the server.
            // Subtract 70 years worth of seconds from the seconds since 1900.
            // This leaves the seconds since the UNIX epoch of 1970.
            // (1900)------------------(1970)**************************************(Time Packet Left the Server)

            time_t txTm = ( time_t ) ( ntpPacket.txTm_s - NTP_TIMESTAMP_DELTA );

            // Print the time we got from the server, accounting for local timezone and conversion from UTC time.

            ESP_LOGI(NTP_CLIENT_TAG, "Time: %s", ctime( ( const time_t* ) &txTm ) );
        }
    }
    else
    {
        ESP_LOGE(NTP_CLIENT_TAG, "packet not sent");
    }
}