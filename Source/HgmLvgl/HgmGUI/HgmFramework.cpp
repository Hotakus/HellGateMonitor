/******************************************************************
 * @file hgm_top_framework.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/8 18:36
 * @copyright Copyright (c) 2021/8/8
*******************************************************************/
#include "../../LvglSrc/lvgl/lvgl.h"
#include "../../HgmApp/HotakusMemUtil.h"

#include "HgmFramework.h"
#include "HgmTwView/HgmTw.h"

#define TAG "HgmFramework"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

#include <Arduino.h>

using namespace HgmGUI;

static HgmFramework* instance = nullptr;

HgmTw* hgmTw = nullptr;

HgmFramework::HgmFramework()
{
    instance = this;

    hgmFwCenter.begin();
    guiChain = hgmFwCenter.msgChain();

    /* Create All UI */
    hgmTw = new HgmTw();
}

HgmFramework::~HgmFramework()
{
    /* Remove All UI */
    delete hgmTw;

    hgmFwCenter.end();
    
    instance = NULL;
}

/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
    changeGUI(guiChain.head()->name());
}

/**
 * @brief Change GUI by name.
 * @param name : Name of GUI
 * @return Boolean
 */
bool HgmGUI::HgmFramework::changeGUI(String name)
{
    msg_t* msg = nullptr;
    bool ret = false;

	/* Kill the previous GUI  */
    if (!curr.isEmpty()) {
        msg = hgmFwCenter.findMsg(curr);
        if (!msg) return false;

        _gd.ctl = END;
        msg->pData(&_gd);
        ret = hgmFwCenter.notify(curr, curr);
        if (ret) return false;
    }

	/* Create the designated GUI  */
    msg = hgmFwCenter.findMsg(name);
    if (!msg) return false;
    _gd.ctl = BEGIN;
    msg->pData(&_gd);
    ret = hgmFwCenter.notify(name, name);
    if (ret) {
        prev = curr;
        curr = name;
    }
    return ret;
}

bool HgmGUI::HgmFramework::changePrev()
{
    return false;
}

bool HgmGUI::HgmFramework::changeNext()
{
    return false;
}

HgmFramework* HgmGUI::HgmFramework::getInstance()
{
    return instance;
}
