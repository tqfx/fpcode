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

/**
 * @enum           fptype_e
 * @brief          The type of Flower Password
*/
typedef enum fptype_e
{
    FPTYPE_EMAIL, /* Email password */
    FPTYPE_PAY,   /* Payment password */
    FPTYPE_NEW,   /* Custom password */
} fptype_e;

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief          Set the rules
 * @param[in]      s0: The first rule
 * @param[in]      s0: The second rule
 * @param[in]      s0: The third rule
 * @param[in]      s0: The fourth rule
 * @return         int 0(success) -1(failure)
*/
extern int fpcode_rule(const char *s0,
                       const char *s1,
                       const char *s2,
                       const char *s3);

/**
 * @brief          Flower Password calculation code
 * @param[out]     dst: The pointer to char pointer
 * @param[in]      t: fptype_e FPTYPE_EMAIL FPTYPE_PAY FPTYPE_NEW
 * @param[in]      p: Passwords that need to be remembered
 * @param[in]      k: Different keywords
 * @param[in]      l: The length of the password returned (1 ~ 32)
 * @param[in]      table_new: New character table under FPTYPE_NEW
 * @return         int 0(success) -1(failure)
 * @warning        Need to free up memory
*/
extern int fpcode(char **     dst,
                  fptype_e    t,
                  const char *p,
                  const char *k,
                  uint32_t    l,
                  const char *table_new);

__BEGIN_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FPCODE_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
