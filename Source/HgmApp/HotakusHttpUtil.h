/******************************************************************
 * @file HotakusHttpUtil.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/12 7:47
 * @copyright Copyright (c) 2021/10/12
*******************************************************************/
#ifndef HELLGATEMONITOR_HOTAKUSHTTPUTIL_H
#define HELLGATEMONITOR_HOTAKUSHTTPUTIL_H

#include <Arduino.h>
#include <HTTPClient.h>

namespace HgmApplication {
	class HotakusHttpUtil {
    private:
    public:
        HotakusHttpUtil();
        ~HotakusHttpUtil();

        static bool GET(HTTPClient& httpClient, String& url, uint8_t* rBuf);
        static bool GET(String& url, uint8_t* buf, size_t bufSize);
	};
}



#endif //HELLGATEMONITOR_HOTAKUSHTTPUTIL_H
