/******************************************************************
 * @file HgmViews.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/26 20:20
 * @copyright Copyright (c) 2021/10/26
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMVIEWS_H
#define HELLGATEMONITOR_HGMVIEWS_H

#include <Arduino.h>

namespace HgmGUI {
    class HgmViews
    {
    private:

    public:

        HgmViews() = default;
        ~HgmViews() = default;

        virtual void begin();
        virtual void end();
    };
};

#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMVIEWS_H
