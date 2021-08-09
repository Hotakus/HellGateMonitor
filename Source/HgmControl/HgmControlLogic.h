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

namespace HGM {

#include <I2C_MPU6886.h>

#define GX_THRESHOLD 200
#define GY_THRESHOLD 200
#define GZ_THRESHOLD 200

	/* Motions */
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

	public:
		MotionType mt = MotionType::NULL_MOTION;
		/* Instance of Control */
		I2C_MPU6886* imu = nullptr;

		HgmControlLogic(TwoWire& i2cPort);
		~HgmControlLogic();

		void HgmControlBegin();

		void GetAccelRowParams();
		void GetGyroRowParams();

		void RelativeGyroValueConfig(float* dgx, float* dgy, float* dgz);
		void RelativeAccelValueConfig(float* dax, float* day, float* daz);
		void AnalyzeTask();
		MotionType AnalyzeMotion();

	};
}


#ifdef __cplusplus
extern "C" {
#endif





#ifdef __cplusplus
}
#endif // !__cplusplus
#endif // !HGM_CONTROL_LOGIC_H
