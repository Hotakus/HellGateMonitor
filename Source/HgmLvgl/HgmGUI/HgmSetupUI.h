/******************************************************************
 * @file HgmSetupUI.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/18 23:17
 * @copyright Copyright (c) 2021/8/18
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMSETUPUI_H
#define HELLGATEMONITOR_HGMSETUPUI_H

#include <TJpg_Decoder.h>

namespace HgmGUI {
	class HgmSetupUI
	{
	private:

	public:
		HgmSetupUI();
		~HgmSetupUI();

		void Begin();

		static void ProgressUIBegin();
		static void ProgressSet(uint8_t progress);

	};

};



#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMSETUPUI_H
