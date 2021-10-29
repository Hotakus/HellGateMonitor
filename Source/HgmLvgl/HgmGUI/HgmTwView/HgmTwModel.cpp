#include "HgmTwModel.h"

using namespace HgmGUI;

HgmGUI::HgmTwModel::HgmTwModel()
{
}

HgmGUI::HgmTwModel::~HgmTwModel()
{
}

void HgmGUI::HgmTwModel::begin()
{
}

void HgmGUI::HgmTwModel::end()
{
}

void HgmGUI::HgmTwModel::setData(tw_data_t* _dat)
{
    memcpy(&dat, _dat, sizeof(tw_data_t));
}

HgmTwModel::tw_data_t* HgmGUI::HgmTwModel::getData()
{
    return &this->dat;
}
