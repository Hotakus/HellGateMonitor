/******************************************************************
 * @file BiliInfoRecv.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/15 16:33
 * @copyright Copyright (c) 2021/8/15
*******************************************************************/
#ifndef HELLGATEMONITOR_BILIINFORECV_H
#define HELLGATEMONITOR_BILIINFORECV_H

#include <Arduino.h>
#include <HTTPClient.h>

namespace HgmApplication {
#define BILI_CONFIG_FILE_PATH "/bilibili.json"
#define BILI_GET_GAP (10 * 60 * 1000)   // 10min

    class BiliInfoRecv
    {
    private:

    public:

        BiliInfoRecv();
        ~BiliInfoRecv();

        void initTask();
        void deInitTask();

        void begin();

        static void SetUID(String uid);
        static String GetUID();
        static bool Done();

        static uint8_t getLevel();
        static size_t getFollower();
        static String& getUserName();
        static void getBasicInfo();
        static int getUserFaceImg(uint16_t imgWidth = 64, uint16_t imgHeight = 64);
        static uint8_t* getUserFaceImgBuf(size_t* imgSize);
        static void* getUserFaceBitmap();
    };
};



#ifdef __cplusplus
extern "C" {
#endif

    /*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_BILIINFORECV_H
