/**
 * *****************************************************************************
 * @file         clipboard.c/h
 * @brief        clipboard
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CLIPBOARD_H__
#define __CLIPBOARD_H__

/* Exported macro ------------------------------------------------------------*/

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

#ifdef __WINNT__

/**
 * @brief          Set the clipboard of windows
 * @param[in]      str: the data
 * @return         int the WINBOOL
*/
extern int clipboard_set(const char *str);

/**
 * @brief          Get the clipboard of windows
 * @param[out]     str: the data
 * @return         int 0(success) -1(failure)
*/
extern int clipboard_get(char **dst);

#endif /* __WINNT__ */

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __CLIPBOARD_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
