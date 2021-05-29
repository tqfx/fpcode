/*!
 @file           fp-crypt.c
 @brief          crypt fp
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

#include "fp-crypt.h"

#include <stdlib.h>
#include <string.h>

/*! @cond */

#define LEN_CRYPT_CHAR 16U

/*! @endcond */

static const char *table_encode =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static unsigned long srands_next = 1UL;

static void srands(unsigned long seed)
{
    srands_next = seed;
}

static unsigned int rands(void)
{
    srands_next = srands_next * 1103515245UL + 12345UL;
    return (unsigned int)((srands_next / 65536UL) % 32768UL);
}

int fp_encrypt(const char *restrict in,
               char **const restrict out,
               unsigned int len)
{
#ifdef DEBUG_CHECK
    if (!in || !out)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    unsigned int n_table = (unsigned int)strlen(table_encode);
    unsigned int n_in    = (unsigned int)strlen(in);
    unsigned int i       = 0U;

    *out = (char *)malloc(len * LEN_CRYPT_CHAR + 1U);
    if (!(*out))
    {
        return -1;
    }

    for (unsigned int j = 0U; i != len * LEN_CRYPT_CHAR; i += LEN_CRYPT_CHAR)
    {
        char         ch   = '\0';
        unsigned int site = (unsigned int)-1;

        if (j < n_in)
        {
            ch   = in[j++];
            site = rands() % 4U * 4U;
        }

        unsigned int k = 0;
        while (k < LEN_CRYPT_CHAR)
        {
            unsigned int temp = k + i + 1U;
            if (k == site)
            {
                srands((unsigned char)ch);
                temp = 0U;
            }

            (*out)[i + k++] = table_encode[(rands() + temp) % n_table];
            (*out)[i + k++] = table_encode[(rands() + temp * 2U) % n_table];
            (*out)[i + k++] = table_encode[(rands() + temp * 3U) % n_table];
            (*out)[i + k++] = table_encode[(rands() + temp * 4U) % n_table];
        }
    }

    (*out)[i] = '\0';

    return 0;
}

int fp_dncrypt(const char *restrict in,
               char **const restrict out,
               unsigned int len)
{
#ifdef DEBUG_CHECK
    if (!in || !out)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    unsigned int n_table = (unsigned int)strlen(table_encode);
    unsigned int j       = 0U;

    *out = (char *)malloc(len + 1U);
    if (!(*out))
    {
        return -1;
    }

    for (unsigned int i = 0U; i != len * LEN_CRYPT_CHAR; i += LEN_CRYPT_CHAR)
    {
        char ch = '\0';

        for (unsigned int k = 0U; k < LEN_CRYPT_CHAR; k += 4U)
        {
            for (char t = '!'; t <= '~'; ++t)
            {
                srands((unsigned char)t);

                if (in[i + k + 0U] == table_encode[rands() % n_table] &&
                    in[i + k + 1U] == table_encode[rands() % n_table] &&
                    in[i + k + 2U] == table_encode[rands() % n_table] &&
                    in[i + k + 3U] == table_encode[rands() % n_table])
                {
                    ch = t;
                    break;
                }
            }

            if (ch != '\0')
            {
                break;
            }
        }

        (*out)[j++] = ch;

        if (ch == '\0')
        {
            break;
        }
    }

    (*out)[j] = '\0';

    return 0;
}

/* END OF FILE */
