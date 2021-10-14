/******************************************************************
 * @file HotakusHttpUtil.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/12 7:47
 * @copyright Copyright (c) 2021/10/12
*******************************************************************/
#include "HotakusHttpUtil.h"

#include <Arduino.h>
#include <HTTPClient.h>

#define TAG "HTTPUtil"
#define HGM_DEBUG 1
#include "../HgmLogUtil.h"

using namespace HgmApplication;

HotakusHttpUtil::HotakusHttpUtil()
{

}

HotakusHttpUtil::~HotakusHttpUtil()
{

}

static bool _GET(HTTPClient& https, String& url, uint8_t* buf, size_t bufSize)
{
    int httpCode = 0;
    WiFiClient* client = NULL;
    size_t packSize = 0;

    hgm_log_d(TAG, "begin...");
    if (https.begin(url)) {
        httpCode = https.GET();
        if (httpCode != HTTP_CODE_OK) {
            hgm_log_e(TAG, "error code: %d", httpCode);
            https.end();
            return false;
        } else {
            client = https.getStreamPtr();
            packSize = client->available();
            if (bufSize < packSize + 1) {
                
            }

            memset(buf, 0, packSize + 1);
            buf[packSize] = '\0';
            client->readBytes(buf, packSize);

            hgm_log_d(TAG, "sucssessfully");
        }
    }
}

bool HotakusHttpUtil::GET(String& url, uint8_t* buf, size_t bufSize, size_t timeout)
{
    if (!buf || bufSize == 0) {
        hgm_log_e(TAG, "GET buffer is null");
        return false;
    }

    HTTPClient* https = new HTTPClient();
    https->setConnectTimeout(3 * 1000);
    https->setTimeout(3 * 1000);
    https->setReuse(false);
    bool ret = _GET(*https, url, buf, bufSize);
    delete https;
    return ret;
}

bool HotakusHttpUtil::GET(HTTPClient& https, String& url, uint8_t* buf, size_t bufSize, size_t timeout)
{
    if (!buf || bufSize == 0) {
        hgm_log_e(TAG, "GET buffer is null");
        return false;
    }
    bool ret = _GET(https, url, buf, bufSize);
    return ret;
}
