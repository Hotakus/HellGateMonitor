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
	class HgmControlLogic {
	private:
		/* Acceleration parameters */
		float _ax;
		float _ay;
		float _az;

		/* Gyro parameters */
		float _gx;
		float _gy;
		float _gz;

	public:
		/* Instance of Control */
		I2C_MPU6886 *imu = nullptr;

		/* Motions */
		enum {
			CLOCKWISE = 0,
			ANTICLOCKWISE,

			RIGHT_TO_LEFT,
			LEFT_TO_RIGHT,

			DOWN_HEAD,
			RISE_HEAD,
		};

		HgmControlLogic(TwoWire &i2cPort);
		~HgmControlLogic();

		void HgmCtlBegin();

		void GetAccelRowParams();
		void GetGyroRowParams();

	};
}


#ifdef __cplusplus
extern "C" {
#endif





#ifdef __cplusplus
}
#endif // !__cplusplus
#endif // !HGM_CONTROL_LOGIC_H
