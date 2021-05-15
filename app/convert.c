/**
 * *****************************************************************************
 * @file         convert.c/h
 * @brief        code conversion 
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "convert.h"

/* Private includes ----------------------------------------------------------*/

#ifdef __WINNT__
#include <windows.h>
#else
#include <locale.h>
#include <stdlib.h>
#endif

/* Private define ------------------------------------------------------------*/

#ifndef __WINNT__
#define CHARSET_UTF8 "zh_CN.utf8"
#define CHARSET_GBK  "zh_CN.gbk"
#endif

/* Private user code ---------------------------------------------------------*/

#ifdef __WINNT__
int code_convert(char **      dst,
                 unsigned int dst_charset,
                 const char * src,
                 unsigned int src_charset)
{
    if (!dst || !src)
    {
        return -1;
    }

    int n = MultiByteToWideChar(src_charset, 0, src, -1, NULL, 0);
    if (!n)
    {
        return -1;
    }
    wchar_t *str = (wchar_t *)malloc(sizeof(wchar_t) * (size_t)n);
    (void)MultiByteToWideChar(src_charset, 0, src, -1, str, n);

    do
    {
        n = WideCharToMultiByte(dst_charset, 0, str, -1, NULL, 0, NULL, 0);
        if (!n)
        {
            n = -1;
            break;
        }
        *dst = (char *)malloc(sizeof(char) * (size_t)n);
        (void)WideCharToMultiByte(dst_charset, 0, str, -1, *dst, n, NULL, 0);

        n = 0;
    } while (0);

    free(str);
    str = NULL;

    return n;
}
#else
int code_convert(char **     dst,
                 const char *dst_charset,
                 const char *src,
                 const char *src_charset)
{
    if (!dst || !src)
    {
        return -1;
    }

    if (!setlocale(LC_CTYPE, src_charset))
    {
        return -1;
    }

    size_t n = mbstowcs(NULL, src, 0);
    if (!n)
    {
        return -1;
    }
    wchar_t *str = (wchar_t *)malloc(sizeof(wchar_t) * n);
    (void)mbstowcs(str, src, n);

    int ret = -1;

    do
    {
        if (!setlocale(LC_CTYPE, dst_charset))
        {
            break;
        }

        n = wcstombs(NULL, str, 0);
        if (!n)
        {
            break;
        }

        *dst = (char *)malloc(sizeof(char) * (n + 1U));

        (*dst)[n] = '\0';
        (void)wcstombs(*dst, str, n);

        ret = 0;
    } while (0);

    free(str);
    str = NULL;

    return ret;
}
#endif

int utf8_gbk(char **dst, const char *src)
{
#ifdef __WINNT__
    return code_convert(dst, 936, src, 65001);
#else
    return code_convert(dst, CHARSET_GBK, src, CHARSET_UTF8);
#endif
}

int gbk_utf8(char **dst, const char *src)
{
#ifdef __WINNT__
    return code_convert(dst, 65001, src, 936);
#else
    return code_convert(dst, CHARSET_UTF8, src, CHARSET_GBK);
#endif
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
