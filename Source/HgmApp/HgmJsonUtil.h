/******************************************************************
 * @file HgmJsonUtil.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/9/21 21:22
 * @copyright Copyright (c) 2021/9/21
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMJSONUTIL_H
#define HELLGATEMONITOR_HGMJSONUTIL_H

#include <Arduino.h>
#include <ArduinoJson.h>

namespace HgmApplication {
	namespace HgmJsonParseUtil{
		struct HotakusDefaultAllocator {
			void *allocate(size_t size)
			{
				return heap_caps_calloc(1, size, MALLOC_CAP_SPIRAM);
			}

			void deallocate(void *ptr)
			{
				heap_caps_free(ptr);
			}

			void *reallocate(void *ptr, size_t new_size)
			{
				return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);
			}
		};
		typedef BasicJsonDocument <HotakusDefaultAllocator> HotakusDynamicJsonDocument;
	}

	class HgmJsonUtil {
	private:
	public:
		HgmJsonUtil();
		~HgmJsonUtil();
	};
}

#endif //HELLGATEMONITOR_HGMJSONUTIL_H
