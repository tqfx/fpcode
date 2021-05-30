/*!
 @file           fp.h
 @brief          fp
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
#ifndef __FP_H__
#define __FP_H__

#include "fpcode.h"

#include <stdint.h>
#include <stdlib.h>

#define LEN_PASSWORD 32U

static const char const_str_p[] = "p";
static const char const_str_k[] = "k";
static const char const_str_t[] = "t";
static const char const_str_l[] = "l";
static const char const_str_i[] = "i";
static const char const_str_n[] = "n";

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

typedef struct
{
    char *key;
    char *new;
    uint32_t len;
    fptype_t type;
} fp_t;

__BEGIN_DECLS

extern int fp_str_k(fp_t ***k,
                    size_t *n,
                    char *s);
extern int fp_str_p(char ***p,
                    size_t *n,
                    char *s);

extern int fp_init(const char *filename);

extern int fp_add_p(const char *filename,
                    const char *password);
extern int fp_del_p(const char *filename,
                    const char *password);

extern int fp_add_k(const char *filename,
                    const fp_t *fp);
extern int fp_del_k(const char *filename,
                    const char *key);

extern int fp_del_i(const char *filename,
                    const char *string,
                    unsigned int i);

extern int fp_out_p(const char *filename,
                    char ***dst,
                    size_t *n);
extern int fp_out_k(const char *filename,
                    fp_t ***dst,
                    size_t *n);

extern int fp_import(const char *filename,
                     const char *dataname);

__END_DECLS

static inline void fp_free(fp_t **fp)
{
    if (*fp)
    {
        if ((*fp)->key)
        {
            free((*fp)->key);
            (*fp)->key = NULL;
        }
        if ((*fp)->new)
        {
            free((*fp)->new);
            (*fp)->new = NULL;
        }
        free(*fp);
        *fp = NULL;
    }
}

static inline void fp_free_p(char ***dst,
                             size_t *n)
{
    if (*dst)
    {
        for (size_t i = 0; i < *n; i++)
        {
            free((*dst)[i]);
            (*dst)[i] = NULL;
        }
        free((*dst));
        *dst = NULL;
        *n = 0U;
    }
}

static inline void fp_free_k(fp_t ***dst,
                             size_t *n)
{
    if (*dst)
    {
        for (size_t i = 0; i < *n; i++)
        {
            fp_free(*dst + i);
        }
        free((*dst));
        *dst = NULL;
        *n = 0U;
    }
}

/* Enddef to prevent recursive inclusion */
#endif /* __FP_H__ */

/* END OF FILE */
