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

bool HotakusHttpUtil::GET(String& url, uint8_t* buf, size_t bufSize)
{
    int httpCode = 0;
    HTTPClient* https = new HTTPClient();
    https->setConnectTimeout(3 * 1000);
    https->setTimeout(3 * 1000);
    https->setReuse(false);

    WiFiClient* client = NULL;
    size_t packSize = 0;

    hgm_log_d(TAG, "GET begin...\n");
    if (https->begin(url)) {
        httpCode = https->GET();
        if (httpCode != HTTP_CODE_OK)
            goto _http_util_out0;
        else {
            client = https->getStreamPtr();
            packSize = client->available();
            if (bufSize < packSize + 1) 
                goto _http_util_out0;

            memset(buf, 0, packSize + 1);
            buf[packSize] = '\0';
            client->readBytes(buf, packSize);
        }
    }
    hgm_log_d(TAG, "GET sucssessfully\n");
    delete https;
    return true;

_http_util_out0:
    hgm_log_e(TAG, "GET error code: %d\n", httpCode);
    https->end();
    delete https;
    return false;
}

bool HotakusHttpUtil::GET(HTTPClient& httpClient, String& url, uint8_t* rBuf)
{

}
