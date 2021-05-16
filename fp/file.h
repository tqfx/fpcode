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

/**
 * @brief          Read the entire contents of the binary file
 * @param[in]      filename: File name to be operated
 * @param[out]     dst: The address where the first address of data is stored
 * @param[out]     sz: The address where the number of data is stored
 * @return         int 0(success) -1(failure)
*/
extern int file_br(const char *filename, void **dst, size_t *sz);

/**
 * @brief          Write data to binary file
 * @param[in]      filename: File name to be operated
 * @param[out]     dst: The first address of data to be written
 * @param[out]     sz: The number of data to be written
 * @return         int 0(success) -1(failure)
*/
extern int file_bw(const char *filename, void *src, size_t sz);

/**
 * @brief          Read the entire contents of the text file
 * @param[in]      filename: File name to be operated
 * @param[out]     dst: The address where the first address of string
 * @return         int 0(success) -1(failure)
*/
extern int file_tr(const char *filename, char **dst);

/**
 * @brief          Write data to text file
 * @param[in]      filename: File name to be operated
 * @param[out]     dst: The first address of string
 * @return         int 0(success) -1(failure)
*/
extern int file_tw(const char *filename, char *src);

/**
 * @brief          Check if the file exists
 * @param[in]      filename: File name to be operated
 * @return         int 1(yes) 0(no)
*/
extern int file_exist(const char *filename);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FILE_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
