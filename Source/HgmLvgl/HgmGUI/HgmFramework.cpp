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

#include "HgmViews.h"
#include "HgmFramework.h"
#include "HgmTwView.h"

#define TAG "HgmFramework"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

#include <Arduino.h>

using namespace HgmGUI;

static HgmFramework* instance = NULL;

HgmTwView* hgmTwView = NULL;

HgmFramework::HgmFramework()
{
    instance = this;

    viewsGroup = (HgmViews**)malloc(sizeof(HgmViews*) * MAX_VIEWS);
    memset(viewsGroup, NULL, sizeof(HgmViews*) * MAX_VIEWS);

    /* Create All UI */
    hgmTwView = new HgmTwView();
}

HgmFramework::~HgmFramework()
{
    /* Remove All UI */
    delete hgmTwView;

    for (uint8_t i = 0; i < MAX_VIEWS; i++)
        if (!viewsGroup[i])
            hotakusFree(viewsGroup);
    instance = NULL;
}

/**
 * @brief initialize the hgm framework
 */
void HgmGUI::HgmFramework::begin()
{
    this->RegisterNewView("MiscView", (vcb_t)HgmTwView::begin, (vdb_t)HgmTwView::stop);
    this->ChangeView("MiscView");
}

bool HgmGUI::HgmFramework::RegisterNewView(String viewName, vcb_t vcb, vdb_t vdb)
{
    if (!vcb || !vdb) {
        hgm_log_e(TAG, "vcb and vdb must be assign.");
        return false;
    }

    int nullIndex = -1;
    for (uint8_t i = 0; i < MAX_VIEWS; i++) {
        if (viewsGroup[i] == NULL) {
            nullIndex = i;
            continue;
        }
        if (viewsGroup[i]->GetName().compareTo(viewName) == 0) {
            hgm_log_e(TAG, "The same view had been registered.");
            return true;
        }
    }
    
    if (nullIndex > -1) {
        viewsGroup[nullIndex] = (HgmViews*)hotakusAlloc(sizeof(HgmViews));
        viewsGroup[nullIndex]->SetName(viewName);
        viewsGroup[nullIndex]->BindCreateBehavior(vcb);
        viewsGroup[nullIndex]->BindDestroyBehavior(vdb);
        return true;
    }

    for (nullIndex = 0; nullIndex < MAX_VIEWS; nullIndex++) {
        if (viewsGroup[nullIndex] == NULL) {
            viewsGroup[nullIndex] = (HgmViews*)hotakusAlloc(sizeof(HgmViews));
            viewsGroup[nullIndex]->SetName(viewName);
            viewsGroup[nullIndex]->BindCreateBehavior(vcb);
            viewsGroup[nullIndex]->BindDestroyBehavior(vdb);
            return true;
        }
    }

    return false;
}

bool HgmGUI::HgmFramework::UnRegisterView(String viewName)
{
    for (uint8_t i = 0; i < MAX_VIEWS; i++) {
        if (viewsGroup[i]->GetName().compareTo(viewName) == 0) {
            hotakusFree(viewsGroup[i]);
            viewsGroup[i] = NULL;
            return true;
        }
    }

    return false;
}

void HgmFramework::ChangeView(String viewName)
{
    for (uint8_t i = 0; i < MAX_VIEWS; i++) {
        if (viewsGroup[i]->GetName().compareTo(viewName) == 0) {
            if (currView) {
                currView->end();
                prevView = currView;
                currView = viewsGroup[i];
                currView->begin();
            } else {
                prevView = NULL;
                currView = viewsGroup[i];
                currView->begin();
            }
            return;
        }
    }
}
