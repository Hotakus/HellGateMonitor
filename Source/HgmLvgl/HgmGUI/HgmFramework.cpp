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
#include "HgmMonitorView/HgmMonitor.h"

#define TAG "HgmFramework"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

#include <Arduino.h>

using namespace HgmGUI;

static HgmTw* hgmTw = nullptr;
static HgmMonitor* hgmMonitor = nullptr;

static HgmFramework* instance = nullptr;

HgmFramework::HgmFramework()
{
    instance = this;

    viewsCenter.begin();
    dataCenter.begin();

    /* Create All UI */
    hgmMonitor = new HgmMonitor();
    hgmTw = new HgmTw();
}

HgmFramework::~HgmFramework()
{
    /* Remove All UI */
    delete hgmTw;
    delete hgmMonitor;

    dataCenter.end();
    viewsCenter.end();
    
    instance = NULL;
}

void HgmGUI::HgmFramework::framework_task(void* params)
{
    String name = "";

    while (true) {
        if (xQueueReceive(instance->msgBox, &name, portMAX_DELAY) != pdPASS)
            continue;

        name = instance->to;

        hgm_log_d(TAG, "Change to %s", name.c_str());

        msg_t* msg = nullptr;
        bool ret = false;

        /* Kill the previous GUI  */
        if (!instance->curr.isEmpty()) {
            msg = instance->viewsCenter.findMsg(instance->curr);
            if (!msg) continue;

            instance->_gd.ctl = END;
            msg->pData(&instance->_gd);
            ret = instance->viewsCenter.notify(instance->curr, instance->curr);
            if (!ret) continue;
            instance->prev = instance->curr;
        }

        /* Create the designated GUI  */
        msg = instance->viewsCenter.findMsg(name);
        if (!msg) continue;
        instance->_gd.ctl = BEGIN;
        msg->pData(&instance->_gd);
        ret = instance->viewsCenter.notify(name, name);
        if (ret)
            instance->curr = name;
        
        name = "";
    }
}

/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
    instance->msgBox = xQueueCreate(1, sizeof(void*));
    xTaskCreatePinnedToCore(
        framework_task,
        "framework_task",
        3072,
        NULL,
        3,
        &this->th,
        1
    );

    //changeGUI("HgmTw");
    changeGUI("HgmMonitor");
}


/**
 * @brief Change GUI by name.
 * @param name : Name of GUI
 * @return Boolean
 */
bool HgmGUI::HgmFramework::changeGUI(String name)
{
    to = name;
    xQueueSend(instance->msgBox, &to, portMAX_DELAY);
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
