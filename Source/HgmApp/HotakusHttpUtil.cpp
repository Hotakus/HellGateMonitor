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

static size_t _GET(HTTPClient& https, String& url, uint8_t* buf, size_t bufSize)
{
    int httpCode = 0;
    WiFiClient* client = NULL;
    size_t packSize = 0;

    hgm_log_d(TAG, "begin...");
    if (https.begin(url)) {
        httpCode = https.GET();
        if (httpCode != HTTP_CODE_OK) {
            hgm_log_e(TAG, "Sending URL(%s) request error (%d)", url.c_str(), httpCode);
            https.end();
        } else {
            client = https.getStreamPtr();
            packSize = client->available();
            if (bufSize < packSize + 1) {
                hgm_log_e(TAG, "The URL request buffer is too small.");
                return packSize;
            }
            memset(buf, 0, packSize + 1);
            buf[packSize] = '\0';
            client->readBytes(buf, packSize);
            hgm_log_d(TAG, "sucssessfully");
            https.end();
        }
    }

    return packSize;
}

size_t HotakusHttpUtil::GET(String& url, uint8_t* buf, size_t bufSize, size_t timeout)
{
    if (!buf || bufSize == 0) {
        hgm_log_e(TAG, "GET buffer is null");
        return 0;
    }

    HTTPClient* https = new HTTPClient();
    https->setConnectTimeout(timeout);
    https->setTimeout(timeout);
    https->setReuse(false);
    size_t ret = _GET(*https, url, buf, bufSize);
    delete https;
    return ret;
}

size_t HotakusHttpUtil::GET(HTTPClient& https, String& url, uint8_t* buf, size_t bufSize, size_t timeout)
{
    if (!buf || bufSize == 0) {
        hgm_log_e(TAG, "GET buffer is null");
        return false;
    }
    https.end();
    https.setConnectTimeout(timeout);
    https.setTimeout(timeout);
    https.setReuse(false);
    size_t ret = _GET(https, url, buf, bufSize);
    return ret;
}
