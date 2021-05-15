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

#include <ctype.h>
#include <stdint.h>

/* Private define ------------------------------------------------------------*/

#define FP_LEN_HMD5   32U
#define FP_RULE_STR   "qwertyuiop"
#define FP_SOURCE_STR "asdfghjkl"
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

/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* The pointer for rules */
static const char *prule0 = NULL;
static const char *prule1 = NULL;
static const char *prule2 = NULL;
static const char *prule3 = NULL;

/* Private function prototypes -----------------------------------------------*/

/**
 * @brief          Hexadecimal to decimal
 * @param[in]      ch: '0'-'9' 'a'-'f' 'A'-'F'
 * @return         int 0~15
*/
static int xdigit(char ch);

/**
 * @brief          Set the rules
 * @param[in]      s0: The first rule
 * @param[in]      s0: The second rule
 * @param[in]      s0: The third rule
 * @param[in]      s0: The fourth rule
 * @return         int 0(success) -1(parameter error)
*/
static int fpcode_rule(const char *s0,
                       const char *s1,
                       const char *s2,
                       const char *s3);

static int fpcode_cc(char **     dst,
                     const char *source,
                     const char *rule,
                     uint32_t    len,
                     uint32_t    type);

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

static int fpcode_rule(const char *s0,
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

    return ret;
}

static int fpcode_cc(char **dst, const char *source, const char *rule, uint32_t len, uint32_t type)
{
    if (len > 64 || type > 1)
    {
        return -1;
    }

    *dst = (char *)calloc(len + 1U, sizeof(char));
    if (!*dst)
    {
        return -1;
    }

    switch (type)
    {
    case 0U:
    {
        const char table_char[] = FP_TABLE_CHAR;

        uint8_t *mark =
            (uint8_t *)calloc(sizeof(table_char) - 1U, sizeof(uint8_t));

        for (uint32_t i = 0U; i < len; i++)
        {
            (*dst)[i] = (char)(xdigit(rule[i]) * 3 + xdigit(source[i]));

            while (mark[(uint8_t)(*dst)[i]])
            {
                (*dst)[i]++;
                if ((size_t)(*dst)[i] >= sizeof(table_char) - 1U)
                {
                    (*dst)[i] = 0;
                }
            }
            mark[(uint8_t)(*dst)[i]]++;

            (*dst)[i] = table_char[(uint8_t)(*dst)[i]];
        }

        free(mark);
        mark = NULL;

        break;
    }

    case 1U:
    {
        uint8_t mark[10U] = {0};
        uint8_t count     = 0U;

        for (uint32_t i = 0U; i < len; i++)
        {
            (*dst)[i] = (char)(xdigit(source[i]) + xdigit(rule[i]));
            (*dst)[i] %= 10;

            char j = (*dst)[i];
            while (mark[(uint8_t)(*dst)[i]] > count)
            {
                (*dst)[i]++;
                if ((*dst)[i] >= 10)
                {
                    (*dst)[i] = 0;
                }
                if ((*dst)[i] == j)
                {
                    count++;
                }
            }
            mark[(uint8_t)(*dst)[i]]++;

            (*dst)[i] = (char)('0' + (*dst)[i]);
        }

        break;
    }

    default:
        break;
    }

    return 0;
}

int fpcode(char **dst, const char *password, const char *key, uint32_t length, uint32_t type)
{
    if (!dst || !password || !key)
    {
        return -1;
    }

    uint32_t l_p = (uint32_t)strlen(password);
    uint32_t l_k = (uint32_t)strlen(key);

    length = FP_LEN_HMD5 > length ? length : FP_LEN_HMD5;

    if ((l_p < 1U) || (l_k < 1U) || (length < 1U))
    {
        return -1;
    }

    char *phmd5 = hmac_md5(password, l_p, key, l_k);
    char *prule =
        hmac_md5(phmd5, FP_LEN_HMD5, FP_RULE_STR, strlen(FP_RULE_STR));
    char *psource =
        hmac_md5(phmd5, FP_LEN_HMD5, FP_SOURCE_STR, strlen(FP_SOURCE_STR));
    PFREE(free, phmd5);

    int ret = fpcode_cc(dst, psource, prule, length, type);

    PFREE(free, psource);
    PFREE(free, prule);

    return ret;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
