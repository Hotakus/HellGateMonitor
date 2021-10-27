/******************************************************************
 * @file HgmViews.cpp
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/26 20:20
 * @copyright Copyright (c) 2021/10/26
*******************************************************************/
#include "HgmViews.h"

using namespace HgmGUI;

HgmViews::HgmViews()
{
	
}

HgmViews::~HgmViews()
{
}

void HgmViews::begin()
{
    this->Create();
}

void HgmViews::end()
{
    this->Destroy();
}

void HgmGUI::HgmViews::SetName(String viewName)
{
    name = viewName;
}

void HgmViews::BindCreateBehavior(vcb_t vcb)
{
    this->Create = vcb;
}

void HgmViews::BindDestroyBehavior(vdb_t vdb)
{
    this->Destroy = vdb;
}

String& HgmViews::GetName()
{
    return this->name;
}
