/******************************************************************
 * @file HgmTwModel.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/30 2:04
 * @copyright Copyright (c) 2021/10/30
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMTWMODEL_H
#define HELLGATEMONITOR_HGMTWMODEL_H

#include "../HgmFramework.h"

namespace HgmGUI {
    
	class HgmTwModel {
	private:
        
	public:

        typedef enum _tw_data_type_t{
            TIME,
            BILI,
            WEATHER,
            CONTROLLABLE
        } tw_data_type_t;

        typedef struct _bili_dat_t {
            size_t fans;        // bili 粉丝数
            uint8_t* ufb;       // bili 用户头像解码buffer地址
            String bn;          // bili 用户名
            String uid;         // bili UID
        } bili_dat_t;

        typedef struct _weather_dat_t {
            uint8_t temp;       // Unit: Celsius
            uint8_t rh;         // Unit: %
            uint16_t aqi;
            uint16_t icon;
        } weather_dat_t;

        typedef struct _time_dat_t {

        } time_dat_t;

        typedef struct _tw_data_t {
            tw_data_type_t tdt;
            bili_dat_t bd;
            weather_dat_t wd;
            time_dat_t td;
            String name;
            bool controllable;
        } tw_data_t;

        tw_data_t dat;

		HgmTwModel();
		~HgmTwModel();

		void begin();
		void end();
        tw_data_t* getData();
	};
};


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMTWMODEL_H
