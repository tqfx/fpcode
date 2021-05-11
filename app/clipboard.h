/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         clipboard.c/h
 * @brief        clipboard
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __CLIPBOARD_H__
#define __CLIPBOARD_H__

/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

#ifdef __WINNT__

/**
 * @brief        set the clipboard of windows
 * @param[in]    str the data
 * @return       int the WINBOOL
*/
extern int clipboard_set(const char *str);

/**
 * @brief        get the clipboard of windows
 * @param[out]   str the data
 * @return       int 0 sucess -1 failure
*/
extern int clipboard_get(char **dst);

#endif /* __WINNT__ */

__END_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __CLIPBOARD_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
