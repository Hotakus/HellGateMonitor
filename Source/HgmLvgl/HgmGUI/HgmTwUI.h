/******************************************************************
 * @file HgmTwUI.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/31 22:54
 * @copyright Copyright (c) 2021/8/31
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMTWUI_H
#define HELLGATEMONITOR_HGMTWUI_H

#include <Arduino.h>


namespace HgmGUI {
	class HgmTwUI
	{
	private:

	public:
		HgmTwUI();
		~HgmTwUI();

		void Begin();
		void Stop();
	
	};

};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMTWUI_H
