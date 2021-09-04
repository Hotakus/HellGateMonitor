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
#define BILI_CONFIG_FILE_PATH "/bilibili.conf"
#define BILI_GET_GAP (10 * 60 * 1000)   // 10min

    class BiliInfoRecv
    {
    private:

    public:
        BiliInfoRecv();
        ~BiliInfoRecv();

        void Begin();

        static void SetUID(String uid);
        static void GetUID(String& uid);

        static int GetFollower();
        static void GetBasicInfo();
        static int GetUserFaceImg(uint16_t imgWidth = 64, uint16_t imgHeight = 64);
        static uint8_t* GetUserFaceImgBuf(size_t* imgSize);
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
