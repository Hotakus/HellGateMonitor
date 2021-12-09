/******************************************************************
 * @file HgmSR.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/12/1 10:57
 * @copyright Copyright (c) 2021/12/1
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMSR_H
#define HELLGATEMONITOR_HGMSR_H

#include "HgmSRModel.h"
#include "HgmSRView.h"
#include "../../../Utils/MsgCenter/MsgCenter.h"

#include "../HgmFramework.h"

#include <Arduino.h>

using namespace msgmanager;

namespace HgmGUI {
    class HgmSR {
    private:
        String _name = "HgmSR";

        static void sr_ui_cb(msg_t* msg);
        static void sr_status_cb(msg_t* msg);

    public:

        /**
         * @brief View and model
         */
        struct _def_vm {
            HgmSRModel model;
            HgmSRView view;
        } def_vm;

        subscriber_t gui_subs;
        subscriber_t update_subs;
        msg_t gui_msg;
        msg_t update_msg;
        msg_t status_msg;

        HgmSR();
        ~HgmSR();

        void begin();
        void end();
        String& name() {
            return this->_name;
        }
    };
}

#endif //HELLGATEMONITOR_HGMSR_H
