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

/* Includes ------------------------------------------------------------------*/

#include "fpcode.h"

/* Private includes ----------------------------------------------------------*/

#include <stdint.h>
#include <string.h>

/* Private define ------------------------------------------------------------*/

#define FP_LEN_HMD5 32U
#define FP_TABLE_CHAR \
    "aAbBcCdDeEfFgGhHiIjJkKlLmM0123456789nNopPqQrRsStTuUvVwWxXyYzZ"

/* Private macro -------------------------------------------------------------*/

#undef PFREE
#define PFREE(_FUN_, _) \
    do                  \
    {                   \
        (void)_FUN_(_); \
        _ = NULL;       \
    } while (0)

#undef MIN2
#define MIN2(n, x) ((n) < (x) ? (n) : (x))

/* Private variables ---------------------------------------------------------*/

/* The pointer for rules */
static const char *prule0 = NULL;
static const char *prule1 = NULL;
static const char *prule2 = NULL;
static const char *prule3 = NULL;

/* The length of rule string */
static uint32_t lrule0 = 0U;
static uint32_t lrule1 = 0U;
static uint32_t lrule2 = 0U;
static uint32_t lrule3 = 0U;

/* character table */
static const char table_char[] = FP_TABLE_CHAR;

/* numeration table */
static uint8_t table_x[FP_LEN_HMD5] = {0};

/* mark table */
static uint8_t table_mark[sizeof(FP_TABLE_CHAR) - 1U] = {0};

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief          Hexadecimal to decimal
 * @param[in]      ch: '0'-'9' 'a'-'f' 'A'-'F'
 * @return         int 0~15
*/
static int xdigit(char ch);

/* Private user code ---------------------------------------------------------*/

static int xdigit(char ch)
{
    int ret = -1;

    switch (ch)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        /* 0 ~ 9 */
        ret = ch - '0';
        break;
    }

    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    {
        /* a ~ f */
        ret = ch - 'a' + 10;
        break;
    }

    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    {
        /* A ~ F */
        ret = ch - 'A' + 10;
        break;
    }

    default:
        break;
    }

    return ret;
}

int fpcode_rule(const char *s0,
                const char *s1,
                const char *s2,
                const char *s3)
{
    int ret = -1;

    /* Check the variable */
    if (!s0 || !s1 || !s2 || !s3)
    {
        return ret;
    }

    /* Set the rules */
    prule0 = s0;
    prule1 = s1;
    prule2 = s2;
    prule3 = s3;

    /* Set the rule length */
    lrule0 = (uint32_t)strlen(s0);
    lrule1 = (uint32_t)strlen(s1);
    lrule2 = (uint32_t)strlen(s2);
    lrule3 = (uint32_t)strlen(s3);

    return ret;
}

int fpcode(char **const restrict dst,
           fptype_e t,
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
    l = MIN2(l, FP_LEN_HMD5);

    /* Get the initial value */
    char *phmd5 = hmac_md5(p, l_p, k, l_k);

    /* Calculation by rule */
    char *pr0 = hmac_md5(phmd5, FP_LEN_HMD5, prule0, lrule0);
    char *pr1 = hmac_md5(phmd5, FP_LEN_HMD5, prule1, lrule1);
    char *pr2 = hmac_md5(phmd5, FP_LEN_HMD5, prule2, lrule2);
    char *pr3 = hmac_md5(phmd5, FP_LEN_HMD5, prule3, lrule3);

    /* free the memory */
    PFREE(free, phmd5);

    /* Compute numerical sum */
    for (uint8_t i = 0U; i != l; ++i)
    {
        table_x[i] = (uint8_t)(xdigit(pr0[i]) + xdigit(pr1[i]) +
                               xdigit(pr2[i]) + xdigit(pr3[i]));
    }

    /* free the memory */
    PFREE(free, pr0);
    PFREE(free, pr1);
    PFREE(free, pr2);
    PFREE(free, pr3);

    *dst = (char *)calloc(l + 1U, sizeof(char));
    memset(table_mark, 0U, sizeof(table_mark));
    uint8_t count = 0U;

    for (uint8_t i = 0U; i != l; ++i)
    {
        uint8_t x = table_x[i];

        switch (t)
        {
        case FPTYPE_NEW:
        case FPTYPE_EMAIL:
        {
            while (table_mark[x])
            {
                if (++x == sizeof(table_char) - 1U)
                {
                    x = 0;
                }
            }
            table_mark[x]++;

            (*dst)[i] = table_char[x];

            break;
        }

        case FPTYPE_PAY:
        {
            x %= 10U;

            uint8_t m = x;
            while (table_mark[x] > count)
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
            table_mark[x]++;

            (*dst)[i] = (char)((uint8_t)'0' + x);

            break;
        }

        default:
            break;
        }
    }

    if (t == FPTYPE_NEW)
    {
        uint32_t l_t = (uint32_t)strlen(table_new);

        l_t = MIN2(l_t, l);
        for (uint8_t i = 0U; i != l_t; ++i)
        {
            (*dst)[table_x[i] % l] = table_new[i];
        }
    }

    return 0;
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
