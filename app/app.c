/**
 * *****************************************************************************
 * @file         app.c/h
 * @brief        application
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "app.h"

/* Private includes ----------------------------------------------------------*/

#include "clipboard.h"
#include "convert.h"
#include "fp.h"
#include "fpcode.h"
#include "kstring.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

static const char const_format_log[]     = "%s  %s  %s\n";
static const char const_format_item_id[] = "%04u      %s\n";

static const char const_str_ok[]    = "ok";
static const char const_str_error[] = "error";
static const char const_str_empty[] = "empty";

/* Private function prototypes -----------------------------------------------*/

#ifdef __clang__
static int cmdout(const char *str);
#endif /* __clang__ */

/* Private user code ---------------------------------------------------------*/

#ifdef __clang__
static int cmdout(const char *str)
{
    FILE *pipe = popen(str, "r");
    if (!pipe)
    {
        perror(str);
        return -1;
    }
    for (;;)
    {
        (void)fgetc(pipe);
        if (feof(pipe))
        {
            break;
        }
    }
    pclose(pipe);
    pipe = NULL;

    return 0;
}
#endif /* __clang__ */

int app_fpcode(const char *password,
               const fp_t *fp)
{
    char *p = NULL;

    if (fp->type == FPTYPE_NEW && !fp->new)
    {
        (void)printf("%s  %s\n",
                     const_str_n,
                     const_str_empty);
    }

    if (fpcode(&p, fp->type, password, fp->key, fp->len, fp->new))
    {
        (void)printf("%s  %s\n",
                     const_str_empty,
                     const_str_error);
        return -1;
    }

#ifdef __WINNT__
    (void)clipboard_set(p);
    char *tmp = NULL;
    utf8_gbk(&tmp, fp->key);
    (void)printf("%s %s\n", tmp, const_str_ok);
    PFREE(free, tmp);
#else
#ifndef __clang__
    (void)printf("%s %s\n", fp->key, p);
#endif /* __clang__ */
#endif /* __WINNT__ */

#ifdef __clang__
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-clipboard-set %s", p);
    (void)cmdout(ks_str(ks));
    PFREE(ks_free, ks);
    (void)printf("%s %s\n", fp->key, const_str_ok);
#endif /* __clang__ */

    PFREE(free, p);

    return 0;
}

int app_data_init(const char *filename)
{
    int ret = fp_init(filename);

    if (ret)
    {
        (void)printf("%s %i\n", const_str_error, ret);
    }
    else
    {
        (void)printf(const_format_log,
                     filename,
                     "init",
                     const_str_ok);
    }

    return ret;
}

int app_add_key(const char *filename,
                const fp_t *fp)
{
    if (!strlen(fp->key))
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_k,
                     const_str_empty);
        return -1;
    }

    if (fp->type == FPTYPE_NEW && !fp->new)
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_n,
                     const_str_empty);
        return -1;
    }

    int ret = fp_add_k(filename, fp);

    if (ret)
    {
        (void)printf("%s %i\n", const_str_error, ret);
    }
    else
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_k,
                     const_str_ok);

        ret = app_get_key(filename, fp);
    }

    return ret;
}

int app_add_password(const char *filename,
                     const char *password)
{
    if (!strlen(password))
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_p,
                     const_str_empty);
        return -1;
    }

    int ret = fp_add_p(filename, password);

    if (ret)
    {
        (void)printf("%s %i\n", const_str_error, ret);
    }
    else
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_p,
                     const_str_ok);
    }

    return ret;
}

static int app_del_id(const char * filename,
                      const char * string,
                      unsigned int id)
{
    int ret = -1;

    do
    {
        size_t n = 0U;
        if (!strcmp(string, const_str_p))
        {
            char **p = NULL;

            ret = fp_out_p(filename, &p, &n);
            if (ret)
            {
                break;
            }
            if (id < n)
            {
                (void)printf(const_format_item_id, id, p[id]);
            }
            fp_free_p(&p, &n);
        }
        else if (!strcmp(string, const_str_k))
        {
            fp_t **k = NULL;

            ret = fp_out_k(filename, &k, &n);
            if (ret)
            {
                break;
            }
            if (id < n)
            {
#ifdef __WINNT__
                char *tmp = NULL;
                utf8_gbk(&tmp, k[id]->key);
                free(k[id]->key);
                k[id]->key = tmp;
#endif /* __WINNT__ */
                (void)printf(const_format_item_id, id, k[id]->key);
            }
            fp_free_k(&k, &n);
        }

        ret = fp_del_i(filename, string, id);
    } while (0);

    return ret;
}

int app_del_key(const char *filename,
                const char *key,
                bool        id)
{
    int ret = 0;

    if (id)
    {
        unsigned int i = 0U;
        sscanf(key, "%u", &i);
        ret = app_del_id(filename, const_str_k, i);
    }
    else if (fp_del_k(filename, key) == 0)
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_k,
                     const_str_ok);
    }

    return ret;
}

int app_del_password(const char *filename,
                     const char *password,
                     bool        id)
{
    int ret = 0;

    if (id)
    {
        unsigned int i = 0U;
        sscanf(password, "%u", &i);
        ret = app_del_id(filename, const_str_p, i);
    }
    else if (fp_del_p(filename, password) == 0)
    {
        (void)printf(const_format_log,
                     filename,
                     const_str_p,
                     const_str_ok);
    }

    return ret;
}

static int app_show_str(const char *filename,
                        const char *string,
                        const char *str)
{
    int ret = -1;

    do
    {
        size_t n = 0U;
        if (!strcmp(string, const_str_p))
        {
            char **p = NULL;
            if (fp_out_p(filename, &p, &n))
            {
                break;
            }
            (void)printf("%4s      %s\n", const_str_i, const_str_p);
            for (size_t i = 0; i != n; ++i)
            {
                if (strstr(p[i], str))
                {
                    (void)printf("%04zu      %s\n", i, p[i]);
                }
            }
            fp_free_p(&p, &n);
        }
        else if (!strcmp(string, const_str_k))
        {
            fp_t **k = NULL;
            if (fp_out_k(filename, &k, &n))
            {
                break;
            }
            (void)printf("%4s %s %2s %s\n",
                         const_str_i,
                         const_str_t,
                         const_str_l,
                         const_str_k);
            for (size_t i = 0; i != n; ++i)
            {
                if (strstr(k[i]->key, str))
                {
#ifdef __WINNT__
                    char *tmp = NULL;
                    utf8_gbk(&tmp, k[i]->key);
                    free(k[i]->key);
                    k[i]->key = tmp;
#endif /* __WINNT__ */
                    (void)printf("%04zu %u %2u %s\n",
                                 i,
                                 k[i]->type,
                                 k[i]->len,
                                 k[i]->key);
                }
            }
            fp_free_k(&k, &n);
        }
    } while (0);

    return ret;
}

int app_show_key(const char *filename,
                 const char *key)
{
    return app_show_str(filename, const_str_k, key);
}

int app_show_password(const char *filename,
                      const char *password)
{
    return app_show_str(filename, const_str_p, password);
}

int app_get_key(const char *filename,
                const fp_t *fp)
{
    int ret = -1;

    do
    {
        char **p = NULL;
        size_t n = 0U;
        if (fp_out_p(filename, &p, &n))
        {
            break;
        }
        if (n)
        {
            ret = app_fpcode(p[0], fp);
            fp_free_p(&p, &n);
        }
    } while (0);

    return ret;
}

int app_get_id(const char * filename,
               unsigned int id_k,
               unsigned int id_p)
{
    int    ret = -1;
    char **p   = NULL;
    size_t n   = 0U;
    fp_t **k   = NULL;
    size_t l   = 0U;

    do
    {
        if (fp_out_p(filename, &p, &n))
        {
            break;
        }
        if (!n)
        {
            (void)printf(const_format_log,
                         filename,
                         const_str_p,
                         const_str_empty);
            break;
        }
        else if (id_p >= n)
        {
            (void)printf(const_format_log,
                         filename,
                         const_str_p,
                         const_str_error);
            break;
        }

        if (fp_out_k(filename, &k, &l))
        {
            break;
        }
        if (!l)
        {
            (void)printf(const_format_log,
                         filename,
                         const_str_k,
                         const_str_empty);
            break;
        }
        else if (id_k >= l)
        {
            (void)printf(const_format_log,
                         filename,
                         const_str_k,
                         const_str_error);
            break;
        }

        if (app_fpcode(p[id_p], k[id_k]))
        {
            break;
        }

        ret = fp_add_p(filename, p[id_p]);
    } while (0);

    fp_free_p(&p, &n);
    fp_free_k(&k, &l);

    return ret;
}

int app_key_import(const char *filename,
                   const char *dataname)
{
    int ret = fp_import(filename, dataname);

    if (ret)
    {
        printf("%s  %s  %i\n",
               filename,
               dataname,
               ret);
    }
    else
    {
        printf(const_format_log,
               filename,
               "import",
               const_str_ok);
    }

    return ret;
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
