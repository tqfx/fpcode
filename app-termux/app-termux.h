/**
 * *****************************************************************************
 * @file         app-termux.c/h
 * @brief        application on termux
 * @author       tqfx
 * @date         20210516
 * @version      1
 * @copyright    Copyright (c) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_TERMUX_H__
#define __APP_TERMUX_H__

/* Includes ------------------------------------------------------------------*/

#include "termux-tapi.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern void app_termux_show_key(const char *filename);

extern void app_termux_del_key(const char *filename);
extern void app_termux_del_password(const char *filename);

extern void app_termux_add_key(const char *filename);
extern void app_termux_add_password(const char *filename);

extern void app_termux_search_key(const char *filename);
extern void app_termux_search_password(const char *filename);

extern void app_termux_create(const char *filename);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __APP_TERMUX_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
