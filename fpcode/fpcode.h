/**
 * *****************************************************************************
 * @file         fpcode.c/h
 * @brief        The core code of Flower Password
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FPCODE_H__
#define __FPCODE_H__

/* Includes ------------------------------------------------------------------*/

#include "MD5.h"

/* Private includes ----------------------------------------------------------*/

#include <stdint.h>

/* Exported types ------------------------------------------------------------*/

typedef enum
{
    FPTYPE_EMAIL,
    FPTYPE_PAY,
    FPTYPE_NEW
} fptype_e;

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief        flower password calculation code
 * @param[out]   dst the pointer of buffer
 * @param[in]    password source password needed to memory
 * @param[in]    key different key word
 * @param[in]    length the length of return code
 * @param[in]    type 0 normal 1 digital
 * @ref          1~32
 * @return       int 0 success -1 failure
 * @warning      need to free the memory
*/
extern int fpcode(char **     dst,
                  const char *password,
                  const char *key,
                  uint32_t    length,
                  uint32_t    type);

__BEGIN_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __FPCODE_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
