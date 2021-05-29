/*!
 @file           fpcode.h
 @brief          The core code of Flower Password
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-29
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 \n \n
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 \n \n
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* Define to prevent recursive inclusion */
#ifndef __FPCODE_H__
#define __FPCODE_H__

#include "md5.h"

#include <stdint.h>

/*!
 @enum           fptype_t
 @brief          The type of Flower Password
*/
typedef enum
{
    FPTYPE_EMAIL, /* Email password */
    FPTYPE_PAY,   /* Payment password */
    FPTYPE_NEW,   /* Custom password */
} fptype_t;

__BEGIN_DECLS

/*!
 @brief          Set the rules
 @param[in]      s0: The first rule
 @param[in]      s1: The second rule
 @param[in]      s2: The third rule
 @param[in]      s3: The fourth rule
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int fpcode_rule(const char *s0,
                       const char *s1,
                       const char *s2,
                       const char *s3);

/*!
 @brief          Flower Password calculation code
 @param[out]     dst: The pointer to char pointer
 @param[in]      t: fptype_e FPTYPE_EMAIL FPTYPE_PAY FPTYPE_NEW
 @param[in]      p: Passwords that need to be remembered
 @param[in]      k: Different keywords
 @param[in]      l: The length of the password returned (1 ~ 32)
 @param[in]      table_new: New character table under FPTYPE_NEW
 @warning        Need to free up memory
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int fpcode(char **const restrict dst,
                  fptype_t t,
                  const char *restrict p,
                  const char *restrict k,
                  uint32_t l,
                  const char *restrict table_new);

__BEGIN_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __FPCODE_H__ */

/* END OF FILE */
