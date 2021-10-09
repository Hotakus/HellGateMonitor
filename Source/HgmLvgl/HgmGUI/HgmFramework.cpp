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
#include "HgmFramework.h"
#include "HgmTwUI.h"
#include <Arduino.h>


using namespace HgmGUI;

static HgmGuiType _defGui;
static HgmGuiType _curGui;
static HgmGuiType _prevGui;

HgmTwUI* hgmTwUI = NULL;


HgmFramework::HgmFramework()
{
    /* Create All UI */
    hgmTwUI = new HgmTwUI();

    this->setDefaultGui();
}

HgmFramework::~HgmFramework()
{
    /* Remove All UI */
    delete hgmTwUI;
}


/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
    /* ui init */
    _curGui = _defGui;
    switch (_curGui)
    {
    case HGM_GUI_MISC:
        hgmTwUI->begin();
        break;
    case HGM_GUI_HARDWARE_MONITOR:
        break;
    case HGM_GUI_PROJECTION:
        break;
    default:
        break;
    }
}

void HgmFramework::setDefaultGui(HgmGuiType def)
{
    _defGui = def;
}

HgmGuiType HgmFramework::getDefaultGui()
{
    return _defGui;
}

HgmGuiType HgmFramework::getCurrentGui()
{
    // TODO:
    return _curGui;
}

void HgmFramework::changeUI(HgmGuiType gui)
{
    _prevGui = _curGui;
    _curGui = gui;

    // TODO:
}
