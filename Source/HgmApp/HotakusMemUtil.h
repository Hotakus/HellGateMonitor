/******************************************************************
 * @file HotakusMemUtil.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/8 4:57
 * @copyright Copyright (c) 2021/10/8
*******************************************************************/
#ifndef HELLGATEMONITOR_HOTAKUSMEMUTIL_H
#define HELLGATEMONITOR_HOTAKUSMEMUTIL_H

#include <Arduino.h>

namespace HgmApplication {

	class HotakusMem
	{
	private:
	public:
		HotakusMem();
		~HotakusMem();

		static void* alloc(size_t size);
		static void* realloc(void* ptr, size_t size);
		static void free(void* ptr);

	};

	
}



#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HOTAKUSMEMUTIL_H
