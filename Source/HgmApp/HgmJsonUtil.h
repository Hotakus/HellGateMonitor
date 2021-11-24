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

#include "./HotakusMemUtil.h"

#include <Arduino.h>
#include <ArduinoJson.h>

namespace HgmApplication {
	namespace HgmJsonParseUtil{
		struct HotakusDefaultAllocator {
			void *allocate(size_t size)
			{
				return hotakusAlloc(size);
			}

			void deallocate(void *ptr)
			{
				hotakusFree(ptr);
			}

			void *reallocate(void *ptr, size_t new_size)
			{
				return hotakusRealloc(ptr, new_size);
			}
		};
		typedef BasicJsonDocument <HotakusDefaultAllocator> HotakusDynamicJsonDocument;
        typedef HotakusDynamicJsonDocument HDJsonDoc;
	}

	class HgmJsonUtil {
	private:
	public:
		HgmJsonUtil();
		~HgmJsonUtil();
	};
}

#endif //HELLGATEMONITOR_HGMJSONUTIL_H
