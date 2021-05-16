/**
 * *****************************************************************************
 * @file         file.c/h
 * @brief        some function of the file
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "file.h"

/* Private includes ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private macro -------------------------------------------------------------*/

#undef FCLOSE
#define FCLOSE(_FILE_)        \
    do                        \
    {                         \
        if (fclose(_FILE_))   \
        {                     \
            clearerr(_FILE_); \
        }                     \
        _FILE_ = NULL;        \
    } while (0)

/* Private user code ---------------------------------------------------------*/

int file_br(const char *filename, void **dst, size_t *sz)
{
#ifdef DEBUG
    if (!filename || !dst || !sz)
    {
        return -1;
    }
#endif /* DEBUG */
    char buf[BUFSIZ] = {0};

    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
#ifdef DEBUG
        perror(filename);
#endif /* DEBUG */
        return -1;
    }

    size_t i = fread(buf, sizeof(char), BUFSIZ, fp);

    if (i)
    {
        *dst = malloc(sizeof(char) * i);
    }

    *sz = 0U;

    while (i)
    {
        memcpy((char *)(*dst) + *sz, buf, i);
        *sz += i;

        i = fread(buf, sizeof(char), BUFSIZ, fp);
        if (i)
        {
            *dst = realloc(*dst, sizeof(char) * (*sz + i));
        }
    }

    FCLOSE(fp);

    return 0;
}

int file_bw(const char *filename, void *src, size_t sz)
{
#ifdef DEBUG
    if (!filename || !src)
    {
        return -1;
    }
#endif /* DEBUG */
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
#ifdef DEBUG
        perror(filename);
#endif /* DEBUG */
        return -1;
    }

    size_t i = 0U;

    do
    {
        i += fwrite((char *)src + i, sizeof(char), sz - i, fp);
    } while (i < sz);

    FCLOSE(fp);

    return 0;
}

int file_tr(const char *filename, char **dst)
{
#ifdef DEBUG
    if (!filename || !dst)
    {
        return -1;
    }
#endif /* DEBUG */
    char buf[BUFSIZ] = {0};

    FILE *fp = fopen(filename, "rt");
    if (!fp)
    {
#ifdef DEBUG
        perror(filename);
#endif /* DEBUG */
        return -1;
    }

    size_t n = 0U;
    size_t i = fread(buf, sizeof(char), BUFSIZ, fp);

    if (i)
    {
        *dst = malloc(sizeof(char) * (i + 1U));
    }

    while (i)
    {
        memcpy(*dst + n, buf, i);
        n += i;

        i = fread(buf, sizeof(char), BUFSIZ, fp);
        if (i)
        {
            *dst = realloc(*dst, sizeof(char) * (n + i + 1U));
        }
    }

    if (n)
    {
        (*dst)[n] = 0;
    }

    FCLOSE(fp);

    return 0;
}

int file_tw(const char *filename, char *src)
{
#ifdef DEBUG
    if (!filename || !src)
    {
        return -1;
    }
#endif /* DEBUG */
    FILE *fp = fopen(filename, "wt");
    if (!fp)
    {
#ifdef DEBUG
        perror(filename);
#endif /* DEBUG */
        return -1;
    }

    size_t n = strlen(src);
    size_t i = 0U;

    do
    {
        i += fwrite(src + i, sizeof(char), n - i, fp);
    } while (i < n);

    FCLOSE(fp);

    return 0;
}

int file_exist(const char *filename)
{
#ifdef DEBUG
    if (!filename)
    {
        return 0;
    }
#endif /* DEBUG */
    int ret = 0;

    FILE *fp = fopen(filename, "rb");
    if (fp)
    {
        FCLOSE(fp);

        ret = !ret;
    }

    return ret;
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
