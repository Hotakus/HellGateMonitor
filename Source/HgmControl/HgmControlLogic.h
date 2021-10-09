/******************************************************************
 * @file HgmControlLogic.h
 * @author Hotakus (ttowfive@gmail.com)
 * @brief
 * @version 1.0
 * @date 2021-08-09
 * @copyright Copyright (c) 2021
 *******************************************************************/

#ifndef HGM_CONTROL_LOGIC_H
#define HGM_CONTROL_LOGIC_H

#include <I2C_MPU6886.h>

namespace HGM {

#define GX_THRESHOLD 200
#define GY_THRESHOLD 200
#define GZ_THRESHOLD 200

	/* Motions' type when user confront the screen surface */
	typedef enum MotionType {
		CLOCKWISE = 0,
		ANTICLOCKWISE,

		RIGHT_TO_LEFT,
		LEFT_TO_RIGHT,

		DOWN_HEAD,
		RISE_HEAD,

		NULL_MOTION,
	};

	class HgmControlLogic {
	private:
		/* Acceleration parameters */
		float _ax = 0;
		float _ay = 0;
		float _az = 0;

		/* Gyro parameters */
		float _gx = 0;
		float _gy = 0;
		float _gz = 0;

		/* relative value */
		float *dax;
		float *day;
		float *daz;
		float *dgx;
		float *dgy;
		float *dgz;

		xSemaphoreHandle i2cSemaphore;

	public:
		MotionType mt = MotionType::NULL_MOTION;
		/* Instance of Control */
		I2C_MPU6886* imu = nullptr;
		float temp = 0;

		HgmControlLogic(TwoWire& i2cPort);
		~HgmControlLogic();

		void HgmControlbegin();

		float GetTemperature();
		void GetAccelRowParams();
		void GetGyroRowParams();

		void RelativeGyroValueConfig(float* dgx, float* dgy, float* dgz);
		void RelativeAccelValueConfig(float* dax, float* day, float* daz);
		void AnalyzeMotion();
		MotionType AnalyzeTask();
	};
}



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif // !__cplusplus
#endif // !HGM_CONTROL_LOGIC_H
