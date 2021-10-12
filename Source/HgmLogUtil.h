/******************************************************************
 * @file HgmLogUtil.h
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/12 7:11
 * @copyright Copyright (c) 2021/10/12
*******************************************************************/
#ifndef HELLGATEMONITOR_HGMLOGUTIL_H
#define HELLGATEMONITOR_HGMLOGUTIL_H

#define HGM_LOG_FORMAT(tag, letter, format)  ARDUHAL_LOG_COLOR_ ## letter "[" #letter "/" tag "][%s:%u] %s(): " format ARDUHAL_LOG_RESET_COLOR "\r\n", pathToFileName(__FILE__), __LINE__, __FUNCTION__
#if HGM_DEBUG == 1
#define hgm_log_d(tag, format, ...) log_printf(HGM_LOG_FORMAT(TAG, D, format), ##__VA_ARGS__)
#define hgm_log_e(tag, format, ...) log_printf(HGM_LOG_FORMAT(TAG, E, format), ##__VA_ARGS__)
#else 
#define hgm_log_d(tag, format, ...)
#define hgm_log_e(tag, format, ...)
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HELLGATEMONITOR_HGMLOGUTIL_H
