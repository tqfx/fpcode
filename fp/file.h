/**
 * *****************************************************************************
 * @file         file.c/h
 * @brief        some function of the file
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FILE_H__
#define __FILE_H__

/* Private includes ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#undef PFREE
#define PFREE(_FUN_, _) \
    do                  \
    {                   \
        (void)_FUN_(_); \
        _ = NULL;       \
    } while (0)

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int file_br(const char *filename, void **dst, size_t *sz);
extern int file_bw(const char *filename, void *src, size_t sz);

extern int file_tr(const char *filename, char **dst);
extern int file_tw(const char *filename, char *src);

extern int file_exist(const char *filename);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FILE_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
