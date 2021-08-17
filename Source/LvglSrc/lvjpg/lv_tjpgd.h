/**
 * @file lv_tjpgd.h
 *
 */

#ifndef LV_TJPGD_H
#define LV_TJPGD_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "tjpgd.h"


/* Output configuration */
// #define LV_TJPGD_CONFIG_RGB888
#define LV_TJPGD_CONFIG_RGB565

#if defined LV_TJPGD_CONFIG_RGB565
    #define BYTES_ON_PIXEL 2
#elif defined LV_TJPGD_CONFIG_RGB888
    #define BYTES_ON_PIXEL 3
#else
    #error "Invalid TJPGD output pixel format configuration"
#endif // defined

/* Scaling factor */
#define LV_TJPGD_CONFIG_SCALING_FACTOR_NONE
//#define LV_TJPGD_CONFIG_SCALING_FACTOR_1_2
//#define LV_TJPGD_CONFIG_SCALING_FACTOR_1_4
//#define LV_TJPGD_CONFIG_SCALING_FACTOR_1_8

/* When setting scaling factor to none we should set JD_USE_SCALE to 0
 * set it to 1 otherwise */
#if defined (LV_TJPGD_CONFIG_SCALING_FACTOR_NONE)
    #define LV_TJPGD_SCALING_FACTOR     0
    #define LV_TJPGD_SCALING_FACTOR_DIV 1
#elif defined (LV_TJPGD_CONFIG_SCALING_FACTOR_1_2)
    #define LV_TJPGD_SCALING_FACTOR     1
    #define LV_TJPGD_SCALING_FACTOR_DIV 2
#elif defined (LV_TJPGD_CONFIG_SCALING_FACTOR_1_4)
    #define LV_TJPGD_SCALING_FACTOR     2
    #define LV_TJPGD_SCALING_FACTOR_DIV 4
#elif defined (LV_TJPGD_CONFIG_SCALING_FACTOR_1_8)
    #define LV_TJPGD_SCALING_FACTOR     3
    #define LV_TJPGD_SCALING_FACTOR_DIV 8
#else
    #error "Invalid TJPGD scaling factor configuration"
#endif // defined

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Register the JPG decoder functions in LittlevGL
 */
void lv_tjpgd_init(void);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TJPGD_H*/
