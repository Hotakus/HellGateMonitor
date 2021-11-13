/******************************************************************
 * @file HgmMonitorModel.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/11/7 20:41
 * @copyright Copyright (c) 2021/11/7
*******************************************************************/
#include "HgmMonitorModel.h"

using namespace HgmGUI;

HgmGUI::HgmMonitorModel::HgmMonitorModel()
{
}

HgmGUI::HgmMonitorModel::~HgmMonitorModel()
{
}

void HgmGUI::HgmMonitorModel::begin()
{
    hrr = new HardwareRequest;
    hrr->begin();
}

void HgmGUI::HgmMonitorModel::end()
{
    hrr->end();
    delete hrr;
}

HgmGUI::HgmMonitorModel::monitor_data_t* HgmGUI::HgmMonitorModel::getData()
{
    return nullptr;
}
