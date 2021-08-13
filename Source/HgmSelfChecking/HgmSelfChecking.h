/******************************************************************
 * @file HgmSelfChecking.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 17:57
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/

#ifndef HELLGATEMONITOR_HGMSELFCHECKING_H
#define HELLGATEMONITOR_HGMSELFCHECKING_H

#include <Arduino.h>

namespace HGM {

	class HgmSC
	{
	private:

	public:

		bool beginFlag = false;

		HgmSC();
		~HgmSC();

		void Begin();
	};
};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMSELFCHECKING_H
