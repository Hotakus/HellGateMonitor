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

HgmControlLogic::HgmControlLogic(TwoWire& i2cPort)
{
	this->imu = new I2C_MPU6886(I2C_MPU6886_DEFAULT_ADDRESS, i2cPort);
	this->RelativeGyroValueConfig(&_gx, &_gy, &_gz);
	this->RelativeAccelValueConfig(&_ax, &_ay, &_az);
}

HgmControlLogic::~HgmControlLogic()
{
	delete this->imu;
}

void HgmControlLogic::HgmControlBegin()
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

void HGM::HgmControlLogic::RelativeGyroValueConfig(float* dgx, float* dgy, float* dgz)
{
	this->dgx = dgx;
	this->dgy = dgy;
	this->dgz = dgz;
}

void HGM::HgmControlLogic::RelativeAccelValueConfig(float* dax, float* day, float* daz)
{
	this->dax = dax;
	this->day = day;
	this->daz = daz;
}

/**
 * @brief  Analyze task.
 */
void HGM::HgmControlLogic::AnalyzeTask()
{
	this->GetAccelRowParams();
	this->GetGyroRowParams();

	this->mt = this->AnalyzeMotion();
	if (this->mt == MotionType::NULL_MOTION)
		return;

	switch (this->mt)
	{
	case MotionType::CLOCKWISE:
		Serial.println("Clockwise");
		break;
	case MotionType::ANTICLOCKWISE:
		Serial.println("Anticlockwise");
		break;
	case MotionType::RIGHT_TO_LEFT:
		Serial.println("RTL");
		break;
	case MotionType::LEFT_TO_RIGHT:
		Serial.println("LTR");
		break;
	case MotionType::RISE_HEAD:
		Serial.println("Rise head");
		break;
	case MotionType::DOWN_HEAD:
		Serial.println("Down head");
		break;
	default:
		break;
	}

}

/**
 * @brief  Analyze the Motion of the imu.
 *
 * @return MotionType
 */
MotionType HGM::HgmControlLogic::AnalyzeMotion()
{

	/*Serial.printf("GX: %0.2f\n", *dgx);
	Serial.printf("GY: %0.2f\n", *dgy);
	Serial.printf("GZ: %0.2f\n", *dgz);*/

	if (*dgz >= GZ_THRESHOLD)
		return MotionType::ANTICLOCKWISE;
	else if (*dgz <= -GZ_THRESHOLD)
		return MotionType::CLOCKWISE;
	else if (*dgy >= GY_THRESHOLD)
		return MotionType::LEFT_TO_RIGHT;
	else if (*dgy <= -GY_THRESHOLD)
		return MotionType::RIGHT_TO_LEFT;
	else if (*dgx >= GX_THRESHOLD)
		return MotionType::DOWN_HEAD;
	else if (*dgx <= -GX_THRESHOLD)
		return MotionType::RISE_HEAD;

	return MotionType::NULL_MOTION;
}

