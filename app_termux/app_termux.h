/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         app_termux.c/h
 * @brief        application on termux
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __APP_TERMUX_H__
#define __APP_TERMUX_H__

/* Includes ------------------------------------------------------------------*/

#include "tapi.h"

/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
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

/* Private defines -----------------------------------------------------------*/

#endif /* __APP_TERMUX_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
