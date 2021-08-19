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

        void HgmTcpTaskInit();

    public:
        TcpControlMethod tcm = TCP_NULL;

        HgmTCP();
        ~HgmTCP();

        void Begin();
        void Stop();

        void BeginServer();
        void StopServer();

        void BeginClient();
        void StopClient();

        static WiFiServer* GetWiFiServer();
        static WiFiClient* GetWiFiClient();
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
