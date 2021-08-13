/******************************************************************
 * @file HgmBT.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/8/13 5:07
 * @copyright Copyright (c) 2021/8/13
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMBT_H
#define HELLGATEMONITOR_HGMBT_H

#include <BluetoothSerial.h>

namespace HgmApplication {
#define BT_DEFAULT_NAME "HellGateMonitorBT"

	typedef enum HgmBTPackMethod
	{

	};

	class HgmBT
	{
	private:

		void BluetoothTaskInit();
		/* Pack the raw data as a data frame via designated method */
		void PackRawData(const char* dataToPack, size_t size, HgmBTPackMethod method);

	public:
		BluetoothSerial *bs = nullptr;

		HgmBT(char* name = BT_DEFAULT_NAME);
		~HgmBT();

		void Begin();
		void Stop();
		
		/* To send data pack, used by another Hgm App */
		void SendDatePack(const char* rawData, size_t size, HgmBTPackMethod method);
	};
};

#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMBT_H
