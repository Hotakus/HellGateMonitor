/******************************************************************
 * @file HgmBT.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 5:07
 * @copyright Copyright (c) 2021/9/16
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMBT_H
#define HELLGATEMONITOR_HGMBT_H
#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

namespace HgmApplication {
#define BT_DEFAULT_NAME "HellGateMonitorBT"
#define BT_PACK_HEADER "HgmBT"
    typedef enum _HgmBTPackMethod
    {
        HGM_BT_PACK_METHOD_GET_M,			// (0) Get max length of the "HgmBTPackMethod"
        HGM_BT_PACK_METHOD_OK,				// (1) Ok pack
        HGM_BT_PACK_METHOD_ERROR,    		// (2) Error
        HGM_BT_PACK_METHOD_NORMAL,			// (3) Pack is Normal data

        // Received method
        HGM_BT_PACK_METHOD_WIFI_CONF,		// (4) WiFi config
        HGM_BT_PACK_METHOD_WIFI_CLOSE,		// (5) WiFi close
        HGM_BT_PACK_METHOD_WEATHER_CONF,	// (6) Weather config
        HGM_BT_PACK_METHOD_BILIBILI_CONF,	// (7) BiliBili config
        HGM_BT_PACK_METHOD_HWM_CONF,		// (8) Hardware monitor config


        /* Add new method in here */


        HGM_BT_PACK_METHOD_NULL,			// (M) Null pack, and represent the max commands length
    } HgmBTPackMethod;

    class HgmBT
    {
    private:
        void BluetoothTaskInit();
        void BluetoothTaskDelete();

    public:
        BluetoothSerial* bs = nullptr;

        HgmBT();
        ~HgmBT();

        void begin();
        void stop();

        static void setName(String _name = BT_DEFAULT_NAME);

        /* Pack the raw data as a data frame via designated method */
        static String packRawData(String& dataToPack, HgmBTPackMethod method);
        /* To send data pack, used by another Hgm App */
        static void sendDatePack(String& rawData, HgmBTPackMethod method);
        static HgmBTPackMethod receiveDataPack(String& dataToSave, HgmBTPackMethod* method);
    };
};




#ifdef __cplusplus
extern "C" {
#endif

    /*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMBT_H
