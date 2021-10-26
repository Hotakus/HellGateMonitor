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
    typedef void (*viewsCreateBehavior_t)(void);
    typedef void (*viewsDestroyBehavior_t)(void);
    typedef viewsCreateBehavior_t(*vcb_t)(void);
    typedef viewsDestroyBehavior_t(*vdb_t)(void);
    class HgmViews
    {
    private:
        vcb_t Create  = NULL;
        vcb_t Destroy = NULL;

        String name = "";
    public:

        HgmViews();
        ~HgmViews();

        void begin();
        void end();

        void SetName(String viewName);
        String& GetName();
        void BindCreateBehavior(vcb_t vcb);
        void BindDestroyBehavior(vdb_t vdb);
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
