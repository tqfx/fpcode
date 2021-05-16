/**
 * *****************************************************************************
 * @file         fpcode_x.c
 * @brief        The core code of Flower Password old
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
#include <string.h>

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

/* Private variables ---------------------------------------------------------*/

/* numeration table */
static uint8_t table_x[FP_LEN_HMD5] = {0};

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

int fpcode(char **     dst,
           fptype_e    t,
           const char *p,
           const char *k,
           uint32_t    l,
           const char *table_new)
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
    l = FP_LEN_HMD5 > l ? l : FP_LEN_HMD5;

    /* Get the initial value */
    char *phmd5 = hmac_md5(p, l_p, k, l_k);

    /* Calculation by rule */
    char *pr0 = hmac_md5(phmd5, FP_LEN_HMD5, "kise", 4);
    char *pr1 = hmac_md5(phmd5, FP_LEN_HMD5, "snow", 4);

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

            l_t = l > l_t ? l_t : l;
            for (uint8_t i = 0U; i != l_t; ++i)
            {
                uint8_t x = (uint8_t)(table_x[i] % l);
                (*dst)[x] = table_new[i];
            }
        }
    }

    return 0;
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
