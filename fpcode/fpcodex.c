/*!
 @file           fpcodex.c
 @brief          The core code of Flower Password old
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

#include "fpcode-private.h"
#include "fpcode.h"

#include <ctype.h>
#include <stdint.h>
#include <string.h>

/*! @cond */

#define FP_LEN_HMD5 32U

#undef PFREE
#define PFREE(_FUN_, _) \
    do                  \
    {                   \
        (void)_FUN_(_); \
        _ = NULL;       \
    } while (0)

/*! @endcond */

static uint8_t table_x[FP_LEN_HMD5] = {0};

int fpcode(char **const restrict dst,
           fptype_t t,
           const char *restrict p,
           const char *restrict k,
           uint32_t l,
           const char *restrict table_new)
{
    /* Check the variable */
    if (!dst || !p || !k || (t == FPTYPE_NEW && !table_new))
    {
        return -1;
    }

    /* Gets the length of the string */
    uint32_t l_p = (uint32_t)strlen(p);
    uint32_t l_k = (uint32_t)strlen(k);

    /* Check the length */
    if (!l_p || !l_k || !l)
    {
        return -1;
    }

    /* Restrict the output password length */
    l = l < FP_LEN_HMD5 ? l : FP_LEN_HMD5;

    /* Get the initial value */
    char *phmd5 = hmac_md5(p, l_p, k, l_k);

    /* Calculation by rule */
    char *pr0 = hmac_md5(phmd5, FP_LEN_HMD5, "kise", 4U);
    char *pr1 = hmac_md5(phmd5, FP_LEN_HMD5, "snow", 4U);

    /* free the memory */
    PFREE(free, phmd5);

    /* Compute numerical sum */
    for (uint8_t i = 0U; i != l; ++i)
    {
        table_x[i] = (uint8_t)(xdigit(pr0[i]) + xdigit(pr1[i]));
    }

    *dst = (char *)calloc(l + 1U, sizeof(char));

    uint8_t count = 0U;

    uint8_t mark[10] = {0};

    for (uint8_t i = 0U; i != l; ++i)
    {
        switch (t)
        {
        case FPTYPE_NEW:
        case FPTYPE_EMAIL:
        {
            (*dst)[i] = pr1[i];
            if (!isdigit((int)(*dst)[i]))
            {
                if (strchr("sunlovesnow1990090127xykab", pr0[i]))
                {
                    (*dst)[i] = (char)toupper((*dst)[i]);
                }
            }

            break;
        }

        case FPTYPE_PAY:
        {
            uint8_t x = table_x[i] % 10U;
            uint8_t m = x;

            while (mark[x] > count)
            {
                if (++x == 10U)
                {
                    x = 0U;
                }
                if (x == m)
                {
                    count++;
                }
            }
            mark[x]++;

            (*dst)[i] = (char)((uint8_t)'0' + x);

            break;
        }

        default:
            break;
        }
    }

    /* free the memory */
    PFREE(free, pr0);
    PFREE(free, pr1);

    if (t != FPTYPE_PAY)
    {
        if (isdigit((int)(*dst)[0]))
        {
            (*dst)[0] = 'K';
        }

        if (t == FPTYPE_NEW)
        {
            uint32_t l_t = (uint32_t)strlen(table_new);
            for (uint8_t i = 0U; i != l_t; ++i)
            {
                (*dst)[table_x[i % FP_LEN_HMD5] % l] = table_new[i];
            }
        }
    }

    return 0;
}

/* END OF FILE */
