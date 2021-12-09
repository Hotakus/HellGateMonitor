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

using namespace HGM;

namespace HgmApplication {

    typedef enum _sr_open_methid_t {
        SR_OPEN_SINGLE_BUFF,
        SR_OPEN_DOUBLE_BUFF,
    } sr_open_methid_t;

    typedef enum _sr_recv_methid_t {
        SR_IMG_FMT_JPG,
        SR_IMG_FMT_RAW,
    } sr_recv_methid_t;

    class ScreenRecv {
    private:
    public:

        struct {
            uint8_t* recv_frame_buf;        // 用于接收投屏数据的buf （如果可行，将分配内部RAM，否则分配外部RAM）
            uint8_t* decode_frame_buf1;     // 用于存放解码后数据的buf1（如果使用jpg投屏）
            uint8_t* decode_frame_buf2;     // 用于存放解码后数据的buf2（如果使用jpg投屏）
            uint8_t* curr_frame_buf;        // 指向当前buf的指针， buf1 或 buf2
        } sr;

        ScreenRecv ();
        ~ScreenRecv ();

        void begin(sr_open_methid_t om, sr_recv_methid_t rm);
        void end();

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
