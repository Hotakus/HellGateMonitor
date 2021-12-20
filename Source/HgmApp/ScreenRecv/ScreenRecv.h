/******************************************************************
 * @file ScreenRecv.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/12/5 19:51
 * @copyright Copyright (c) 2021/12/5
*******************************************************************/
#ifndef HELLGATEMONITOR_SCREENRECV_H
#define HELLGATEMONITOR_SCREENRECV_H

#include "../../HgmLvgl/HgmGUI/HgmFramework.h"
#include "../../HgmLvgl/HgmLvgl.h"

#include <Arduino.h>
#include <WiFi.h>

using namespace HGM;

namespace HgmApplication {

    typedef enum _sr_open_methid_t {
        SR_OPEN_SINGLE_BUFF,
        SR_OPEN_DOUBLE_BUFF,
    } sr_open_methid_t;

    typedef enum _sr_recv_methid_t {
        SR_IMG_FMT_JPG,
        SR_IMG_FMT_PNG,
        SR_IMG_FMT_RAW,
    } sr_recv_methid_t;

    typedef struct _sr_data_t {
        size_t  fb; 
        sr_recv_methid_t cf;
    } sr_data_t;

    typedef struct _sr_t {
        uint8_t* recv_frame_buf;        // 用于接收投屏数据的buf （如果可行，将分配内部RAM，否则分配外部RAM）
        uint8_t* decode_frame_buf1;     // 用于存放解码后数据的buf1（如果使用jpg投屏）
        uint8_t* decode_frame_buf2;     // 用于存放解码后数据的buf2（如果使用jpg投屏）
        uint8_t* curr_frame_buf;        // 指向当前buf的指针， buf1 或 buf2

        sr_data_t dat;
        size_t fps;
    } sr_t;

    class ScreenRecv {
    private:
        

        static void decode_task(void* params);
        
    public:
        sr_t sr;
        bool beginFlag = false;

        struct _frtos {
            TaskHandle_t decode_th = NULL;
            QueueHandle_t decode_mb = NULL;
        } frtos;

        ScreenRecv ();
        ~ScreenRecv ();

        void begin(sr_open_methid_t om);
        void end();

        void initTask();
        void deInitTask();

        bool setFrameHead(sr_data_t dat);
        bool imgReceive(WiFiClient& wc, size_t timeout = (5 * 1000));
        static void decode_start();

    };
}

#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_SCREENRECV_H
