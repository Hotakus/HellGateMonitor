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

	// HGM's components' type
	typedef enum HgmComponentType
	{
		HGM_COMPONENT_BT,
		HGM_COMPONENT_CONFIG_FILE,
		HGM_COMPONENT_WIFI,
		HGM_COMPONENT_NET_TIME,
		HGM_COMPONENT_WEATHER,
		HGM_COMPONENT_BILIBILI,

		HGM_COMPONENT_DONE,

		HGM_COMPONENT_NULL,
	};

	// HGM's components
	typedef struct HgmComponent
	{
		HgmComponentType type;
		bool curStatus;			// Component's current status
		bool waitStatus;		// Component's wait status
	};

	class HgmSetupUI
	{
	private:

	public:
		HgmSetupUI();
		~HgmSetupUI();

		void Begin();

		// Be call for other class
		static void ComponentControl(HgmComponent* component);
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
