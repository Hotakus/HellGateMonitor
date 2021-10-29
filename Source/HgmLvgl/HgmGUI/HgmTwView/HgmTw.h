/******************************************************************
 * @file HgmTw.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/30 2:03
 * @copyright Copyright (c) 2021/10/30
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMTW_H
#define HELLGATEMONITOR_HGMTW_H

#include "HgmTwView.h"
#include "HgmTwModel.h"

#include "../../../Utils/MsgCenter/MsgCenter.h"

using namespace msgmanager;

namespace HgmGUI {

    class HgmTw {
    private:
        String _name = "HgmTw";

        static void hgm_ui_cb(msg_t* msg);
    public:
        
        HgmFramework::gui_data_t _gd;

		/**
		 * @brief View and model
		 */
        struct _def_vm {
            HgmTwView view;
            HgmTwModel model;
        } def_vm;

        subscriber_t subscriber;
        msg_t msg;

        HgmTw();
        ~HgmTw();

        void begin();
        void end();
        void setData(HgmTwModel::tw_data_t* _dat);
        HgmTwModel::tw_data_t* getData();
        String& name() {
            return this->_name;
        }
    };
};

#ifdef __cplusplus
extern "C" {
#endif

    /*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMTW_H
