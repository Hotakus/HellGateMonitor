/******************************************************************
 * @file HgmTCP.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/12 20:21
 * @copyright Copyright (c) 2021/8/12
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMTCP_H
#define HELLGATEMONITOR_HGMTCP_H

#include <WiFi.h>

namespace HgmApplication {
#define TCP_PACK_HEADER "HgmTCP"
    typedef enum HgmTcpPackMethod
    {
        // Send method
        HGM_TCP_PACK_METHOD_HGMC_IDENTIFY,          // (0) Identify TCP client is HGMC or not
        HGM_TCP_PACK_METHOD_OK,                     // (1) OK
        HGM_TCP_PACK_METHOD_ERROR,                  // (2) ERROR

        HGM_TCP_PACK_METHOD_REQUEST_HWI,		    // (3) Request Hardware info from HGMC, it will get hardware info from HGMC according to config params
        HGM_TCP_PACK_METHOD_HWI,                    // (4) Hardware info pack

        HGM_TCP_PACK_METHOD_PROJECTION,             // (5) 

        HGM_TCP_PACK_METHOD_NORMAL,                 // (M-1) Pack is Normal data
        HGM_TCP_PACK_METHOD_NULL,                   // (M) Null
    };

    typedef enum TcpControlMethod
    {
        TCP_BEGIN_SERVER,
        TCP_STOP_SERVER,
        TCP_BEGIN_CLIENT,
        TCP_STOP_CLIENT,

        TCP_NULL
    };

    class HgmTCP
    {
    private:
        WiFiServer* wifiServer = nullptr;
        WiFiClient* wifiClient = nullptr;

        void initTask();
        void deInitTask();

    public:
        bool isReady = false;
        bool isHGM = false;
        TcpControlMethod tcm = TCP_NULL;
        WiFiClient accept;

        struct _frtos {
            TaskHandle_t tcpControlTaskHandle = NULL;
            QueueHandle_t beginMsgbox = NULL;
            TaskHandle_t tcpServerTaskHandle = NULL;
            TaskHandle_t tcpClientTaskHandle = NULL;
        } frtos;

        HgmTCP();
        ~HgmTCP();

        void begin();
        void stop();

        void BeginServer();
        void StopServer();

        void BeginClient();
        void StopClient();

        static WiFiServer* GetWiFiServer();
        static WiFiClient* GetWiFiClient();

        /* Pack the raw data as a data frame via designated method */
        static String packRawData(String& dataToPack, HgmTcpPackMethod method);
        /* To send data pack, used by another Hgm App */
        static void sendDatePack(String& rawData, HgmTcpPackMethod method);
        static HgmTcpPackMethod receiveDataPack();
    };


};


#ifdef __cplusplus
extern "C" {
#endif

    /*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMTCP_H
