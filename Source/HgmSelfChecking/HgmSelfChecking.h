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

#include "../HgmLvgl/HgmGUI/HgmSetupView.h"
#include <Arduino.h>

using namespace HgmGUI;

namespace HGM {

	class HgmSC
	{
	private:
        HgmComponent component;
        HgmSetupView* hgmSetup;
        bool _cur;
        bool _wait;
	public:

        HgmSC() = default;
        ~HgmSC() = default;
        void begin();

        void setState(HgmComponentType ct, bool cur, bool wait);
        void checkBT();
        void checkSpiffs();
        void checkWiFi();
        void checkTime();
        void checkBili();
        void checkWeather();

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
