/******************************************************************
 * @file HgmControlLogic.cpp
 * @author Hotakus (ttowfive@gmail.com)
 * @brief ...
 * @version 1.0
 * @date 2021-08-09
 * @copyright Copyright (c) 2021
 *******************************************************************/

#include <Arduino.h>
#include <I2C_MPU6886.h>
#include "HgmControlLogic.h"

using namespace HGM;

HgmControlLogic::HgmControlLogic(TwoWire &i2cPort)
{
    this->imu = new I2C_MPU6886(I2C_MPU6886_DEFAULT_ADDRESS, i2cPort);
}

HgmControlLogic::~HgmControlLogic()
{
    delete this->imu;
}

void HgmControlLogic::HgmCtlBegin()
{
	this->imu->begin();
}

void HgmControlLogic::GetAccelRowParams()
{
    this->imu->getAccel(&_ax, &_ay, &_az);
}

void HgmControlLogic::GetGyroRowParams()
{
    this->imu->getGyro(&_gx, &_gy, &_gz);
}
