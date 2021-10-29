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
        typedef struct _tw_data_t {
            // TODO:
            HgmFramework::CTL_t ctl;
        } tw_data_t;

        tw_data_t dat;

		HgmTwModel();
		~HgmTwModel();

		void begin();
		void end();
        void setData(tw_data_t* _dat);
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
