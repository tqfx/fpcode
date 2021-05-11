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
    "aAbBcCd0DeEf1FgGh2HiIj3JkKl4LmMn5NopP6qQrR7sStT8uUvV9wWxXyYzZ"

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
/* Private function prototypes -----------------------------------------------*/

/**
 * @brief        Hexadecimal to decimal
 * @param[in]    ch '0'-'9' 'A'-'F' 'a'-'f'
 * @return       0~15
*/
static int xdigit(char ch);

static int fpcode_cc(char **dst, const char *source, const char *rule, uint32_t len, uint32_t type);

/* Private user code ---------------------------------------------------------*/

static int xdigit(char ch)
{
    int x = 0;
    if ('0' <= ch && ch <= '9')
    {
        x = ch - '0';
    }
    else if ('A' <= ch && ch <= 'F')
    {
        x = ch - 'A' + 10;
    }
    else if ('a' <= ch && ch <= 'f')
    {
        x = ch - 'a' + 10;
    }
    return x;
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
