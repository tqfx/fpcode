/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         fpcode.c/h
 * @brief        core code fo fp
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __FPCODE_H__
#define __FPCODE_H__

/* Includes ------------------------------------------------------------------*/

#include "MD5.h"

/* Private includes ----------------------------------------------------------*/

#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
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
extern int fpcode(char **dst, const char *password, const char *key, uint32_t length, uint32_t type);

__BEGIN_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __FPCODE_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
