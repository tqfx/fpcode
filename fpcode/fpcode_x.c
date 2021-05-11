/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         fpcode_x.c
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

#define FP_LEN_HMD5 32U

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

static uint32_t xdigit(char ch);

static int fpcode_cc(char **dst, const char *source, const char *rule, uint32_t len, uint32_t type);

/* Private user code ---------------------------------------------------------*/

static uint32_t xdigit(char ch)
{
    uint32_t x = 0U;
    if ('0' <= ch && ch <= '9')
    {
        x = (uint32_t)(ch - '0');
    }
    else if ('A' <= ch && ch <= 'F')
    {
        x = (uint32_t)(ch - 'A' + 10);
    }
    else if ('a' <= ch && ch <= 'f')
    {
        x = (uint32_t)(ch - 'a' + 10);
    }
    return x;
}

static int fpcode_cc(char **dst, const char *source, const char *rule, uint32_t len, uint32_t type)
{
    if (!dst || !source || !rule || len > 64 || type > 1)
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
        for (uint32_t i = 0; i < len; i++)
        {
            (*dst)[i] = source[i];
            if (!isdigit((*dst)[i]))
            {
                if (strchr("sunlovesnow1990090127xykab", rule[i]) != NULL)
                {
                    (*dst)[i] = (char)toupper((*dst)[i]);
                }
            }
        }

        if (isdigit((*dst)[0]))
        {
            (*dst)[0] = 'K';
        }

        break;
    }

    case 1U:
    {
        uint8_t mark[10U] = {0};
        uint8_t count     = 0U;

        for (uint32_t i = 0U; i < len; i++)
        {
            (*dst)[i] = (char)(xdigit(source[i]) + xdigit(rule[i]));
            (*dst)[i] %= (char)10;

            char j = (*dst)[i];
            while (mark[(unsigned)(*dst)[i]] > count)
            {
                (*dst)[i]++;
                if ((*dst)[i] >= (char)10)
                {
                    (*dst)[i] = (char)0;
                }
                if ((*dst)[i] == j)
                {
                    count++;
                }
            }
            mark[(unsigned)(*dst)[i]]++;

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

    char  pKise[] = "kise";
    char  pSnow[] = "snow";
    char *pHmd5   = hmac_md5(password, l_p, key, l_k);
    char *pRule   = hmac_md5(pHmd5, FP_LEN_HMD5, pKise, 4);
    char *pSource = hmac_md5(pHmd5, FP_LEN_HMD5, pSnow, 4);
    PFREE(free, pHmd5);

    int ret = fpcode_cc(dst, pSource, pRule, length, type);

    PFREE(free, pRule);
    PFREE(free, pSource);

    return ret;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
