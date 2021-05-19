/**
 * *****************************************************************************
 * @file         fp.c/h
 * @brief        fp
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FP_H__
#define __FP_H__

/* Includes ------------------------------------------------------------------*/
#include "fpcode.h"

/* Private includes ----------------------------------------------------------*/

#include <stdint.h>
#include <stdlib.h>

/* Exported constants --------------------------------------------------------*/

#define LEN_PASSWORD 32U

static const char const_str_p[] = "p";
static const char const_str_k[] = "k";
static const char const_str_t[] = "t";
static const char const_str_l[] = "l";
static const char const_str_i[] = "i";
static const char const_str_n[] = "n";

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

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    char *key;
    char *new;
    uint32_t len;
    fptype_e type;
} fp_t;

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int fp_str_k(fp_t ***k, size_t *n, char *s);
extern int fp_str_p(char ***p, size_t *n, char *s);

extern int fp_init(const char *filename);

extern int fp_add_p(const char *filename, const char *password);
extern int fp_del_p(const char *filename, const char *password);

extern int fp_add_k(const char *filename, const fp_t *fp);
extern int fp_del_k(const char *filename, const char *key);

extern int fp_del_i(const char *filename, const char *string, unsigned int i);

extern int fp_out_p(const char *filename, char ***dst, size_t *n);
extern int fp_out_k(const char *filename, fp_t ***dst, size_t *n);

extern int fp_import(const char *filename, const char *dataname);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

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

static inline void fp_free_p(char ***dst, size_t *n)
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
        *n   = 0U;
    }
}

static inline void fp_free_k(fp_t ***dst, size_t *n)
{
    if (*dst)
    {
        for (size_t i = 0; i < *n; i++)
        {
            fp_free(*dst + i);
        }
        free((*dst));
        *dst = NULL;
        *n   = 0U;
    }
}

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FP_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
