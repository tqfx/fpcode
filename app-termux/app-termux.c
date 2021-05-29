/*!
 @file           app-termux.c
 @brief          application on termux
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

#include "app-termux.h"

#include "file.h"
#include "fp.h"
#include "fpcode.h"
#include "kstring.h"
#include "termux-api.h"
#include "termux-tapi.h"

static int p2vsn(char **dst,
                 char **p,
                 size_t n);
static int k2vsn(char **dst,
                 fp_t **k,
                 size_t n);

static int app_termux_input_k(fp_t *fp);
static int app_termux_input_p(char **p);
static int app_termux_fpcode(const char *password,
                             const fp_t *fp);
static int app_termux_get_key(const char *filename,
                              const fp_t *fp);

static int p2vsn(char **dst,
                 char **p,
                 size_t n)
{
    if (!n)
    {
        return -1;
    }

    kstring_t *ks = ks_init();
    for (size_t i = 0U; i != n; ++i)
    {
        (void)ksprintf(ks, "%s,", p[i]);
    }
    *dst = ks_release(ks);
    PFREE(ks_free, ks);

    return 0;
}

static int k2vsn(char **dst,
                 fp_t **k,
                 size_t n)
{
    if (!n)
    {
        return -1;
    }

    kstring_t *ks = ks_init();
    for (size_t i = 0U; i != n; ++i)
    {
        (void)ksprintf(ks, "%s,", k[i]->key);
    }
    *dst = ks_release(ks);
    PFREE(ks_free, ks);

    return 0;
}

static int app_termux_input_k(fp_t *fp)
{
    int ret = -2;

    if (!fp)
    {
        return ret;
    }

    do
    {
        ret = tapi_spinner(NULL, (int *)&fp->type, "类型", "邮箱类,数字类,自定义");
    } while (ret < -1);
    if (ret == -1)
    {
        return ret;
    }

    do
    {
        switch (fp->type)
        {
        case FPTYPE_NEW:
        case FPTYPE_EMAIL:
        {
            long l = 0;

            ret = tapi_counter(&l, "长度", "1,32,16");

            fp->len = (uint32_t)l;

            break;
        }

        case FPTYPE_PAY:
        {
            long l = 0;

            ret = tapi_counter(&l, "长度", "1,32,6");

            fp->len = (uint32_t)l;

            break;
        }

        default:
            break;
        }
    } while (ret < -1);
    if (ret == -1)
    {
        return ret;
    }

    do
    {
        ret = tapi_text(&fp->key, "标识", const_str_k, NULL);
        if (ret == -1)
        {
            break;
        }
        if (!ret && !strlen(fp->key))
        {
            PFREE(free, fp->key);
            ret = -1;
        }
    } while (ret);

    if (fp->type == FPTYPE_NEW)
    {
        do
        {
            ret = tapi_text(&fp->new, "字符表", "table", NULL);
            if (ret == -1)
            {
                break;
            }
            if (!ret && !strlen(fp->new))
            {
                PFREE(free, fp->key);
                fp->type = FPTYPE_EMAIL;
            }
        } while (ret);
    }

    return ret;
}

static int app_termux_input_p(char **p)
{
    int ret = -2;

    if (!p)
    {
        return ret;
    }

    do
    {
        char *p1 = NULL;
        do
        {
            ret = tapi_text(&p1, "密码", "first", "p");
            if (ret == -1)
            {
                return ret;
            }
            if (!ret && !strlen(p1))
            {
                PFREE(free, p1);
                ret = -1;
            }
        } while (ret);

        char *p2 = NULL;
        do
        {
            ret = tapi_text(&p2, "密码", "verify", "p");
            if (ret == -1)
            {
                break;
            }
            if (!ret && !strlen(p2))
            {
                PFREE(free, p2);
                ret = -1;
            }
        } while (ret);

        if (!ret && strcmp(p1, p2))
        {
            tapi_toast_warning("密码不一致");
            PFREE(free, p2);
            ret = -1;
        }
        else
        {
            *p = p2;
        }

        PFREE(free, p1);
    } while (ret);

    return ret;
}

static int app_termux_fpcode(const char *password,
                             const fp_t *fp)
{
    int ret = -2;

    if (fp->type == FPTYPE_NEW && !fp->new)
    {
        tapi_toast_error("空表");
        return ret;
    }

    char *p = NULL;
    if (fpcode(&p, fp->type, password, fp->key, fp->len, fp->new))
    {
        tapi_toast_error("空字符串");
        return ret;
    }

    do
    {
        ret = tapi_confirm("是否复制", p);
        if (ret)
        {
            break;
        }

        ret = termux_clipboard_set(p);
        if (ret)
        {
            tapi_toast_error("复制失败");
        }
        else
        {
            tapi_toast_ok("复制成功");
        }

        ret = 0;
    } while (0);

    PFREE(free, p);

    return ret;
}

static int app_termux_get_key(const char *filename,
                              const fp_t *fp)
{
    int ret = -2;

    char **p = NULL;
    size_t n = 0;
    if (fp_out_p(filename, &p, &n))
    {
        return ret;
    }

    do
    {
        ret = -1;
        if (!n)
        {
            tapi_toast_warning("无密码");
            break;
        }

        int i = 0;

        do
        {
            if (n == 1U)
            {
                ret = 0;
                break;
            }

            char *ss = NULL;
            if (p2vsn(&ss, p, n))
            {
                break;
            }
            ret = tapi_spinner(NULL, &i, "选择密码", ss);
            PFREE(free, ss);
        } while (0);

        if (ret < 0)
        {
            break;
        }

        ret = app_termux_fpcode(p[i], fp);
    } while (0);

    fp_free_p(&p, &n);

    return ret;
}

void app_termux_show_key(const char *filename)
{
    int ret = -2;

    fp_t **k = NULL;
    size_t n = 0;
    if (fp_out_k(filename, &k, &n))
    {
        return;
    }

    do
    {
        ret = -1;
        if (!n)
        {
            tapi_toast_warning("无数据");
            break;
        }

        char *ss = NULL;
        if (k2vsn(&ss, k, n))
        {
            break;
        }
        int i = 0;
        do
        {
            ret = tapi_radio(NULL, &i, const_str_k, ss);
        } while (ret < -1);
        PFREE(free, ss);
        if (ret == -1)
        {
            break;
        }

        ret = app_termux_get_key(filename, k[i]);
    } while (ret != -1);

    fp_free_k(&k, &n);

    return;
}

static int app_termux_del(const char *filename,
                          const char *string)
{
    int ret = -2;

    char **p = NULL;
    fp_t **k = NULL;
    size_t n = 0U;

    int (*func)(const char *, const char *);
    if (!strcmp(string, const_str_k))
    {
        func = fp_del_k;
    }
    else if (!strcmp(string, const_str_p))
    {
        func = fp_del_p;
    }
    else
    {
        return ret;
    }

    do
    {
        ret = -1;

        if (func == fp_del_k)
        {
            if (fp_out_k(filename, &k, &n))
            {
                break;
            }
        }
        else if (func == fp_del_p)
        {
            if (fp_out_p(filename, &p, &n))
            {
                break;
            }
        }
        if (!n)
        {
            tapi_toast_warning("无数据");
            break;
        }

        char *ss = NULL;
        if (func == fp_del_k)
        {
            ret = k2vsn(&ss, k, n);
        }
        else if (func == fp_del_p)
        {
            ret = p2vsn(&ss, p, n);
        }
        if (ret)
        {
            break;
        }

        char **s = NULL;
        int    l = 0;

        do
        {
            ret = tapi_checkbox(&s, NULL, &l, string, ss);
        } while (!ret && !l);
        PFREE(free, ss);
        if (ret < 0 || !l)
        {
            break;
        }

        for (int i = 0; i != l; ++i)
        {
            if (tapi_confirm("是否删除", s[i]))
            {
                continue;
            }
            if (0 == func(filename, s[i]))
            {
                tapi_toast_ok("删除成功");
            }
        }

        for (int i = 0; i != l; ++i)
        {
            PFREE(free, s[i]);
        }
        PFREE(free, s);

    } while (ret != -1);

    if (func == fp_del_k)
    {
        fp_free_k(&k, &n);
    }
    else if (func == fp_del_p)
    {
        fp_free_p(&p, &n);
    }

    return ret;
}

void app_termux_del_password(const char *filename)
{
    app_termux_del(filename, const_str_p);
    return;
}

void app_termux_del_key(const char *filename)
{
    app_termux_del(filename, const_str_k);
    return;
}

void app_termux_add_key(const char *filename)
{
    fp_t code = {0};
    if (app_termux_input_k(&code))
    {
        return;
    }

    int ret = fp_add_k(filename, &code);
    if (ret)
    {
        tapi_toast_error("添加失败");
    }
    else
    {
        tapi_toast_ok("添加成功");
    }

    PFREE(free, code.key);

    return;
}

void app_termux_add_password(const char *filename)
{
    char *password = NULL;
    if (app_termux_input_p(&password))
    {
        return;
    }

    if (fp_add_p(filename, password))
    {
        tapi_toast_error("添加失败");
    }
    else
    {
        tapi_toast_ok("添加成功");
    }

    PFREE(free, password);

    return;
}

void app_termux_create(const char *filename)
{
    fp_t code = {0};
    if (app_termux_input_k(&code))
    {
        return;
    }

    char *password = NULL;
    if (app_termux_input_p(&password))
    {
        app_termux_get_key(filename, &code);
    }
    else
    {
        app_termux_fpcode(password, &code);
        PFREE(free, password);
    }

    PFREE(free, code.key);

    return;
}

void app_termux_search_key(const char *filename)
{
    int ret = -2;

    fp_t **k = NULL;
    size_t n = 0U;

    do
    {
        fp_free_k(&k, &n);
        if (fp_out_k(filename, &k, &n))
        {
            break;
        }
        if (!n)
        {
            ret = -1;
            tapi_toast_warning("无数据");
            break;
        }

        char *key = NULL;
        do
        {
            ret = tapi_text(&key, "标识", const_str_k, NULL);
        } while (ret < -1);
        if (ret == -1)
        {
            break;
        }

        if (fp_str_k(&k, &n, key))
        {
            break;
        }
        PFREE(free, key);
        if (!n)
        {
            tapi_toast_warning("无该标识");
            continue;
        }

        int   i  = 0;
        char *vs = NULL;
        ret      = k2vsn(&vs, k, n);
        if (ret)
        {
            break;
        }
        do
        {
            ret = tapi_radio(NULL, &i, "结果", vs);
        } while (ret < -1);
        PFREE(free, vs);
        if (ret == -1)
        {
            ret = 0;
            continue;
        }

        int index = 0;
        do
        {
            ret = tapi_sheet(NULL, &index, "目录", "获取,删除");
        } while (ret < -1);
        if (ret == -1)
        {
            ret = 0;
            continue;
        }

        switch (index)
        {
        case 0:
        {
            ret = app_termux_get_key(filename, k[i]);
            break;
        }

        case 1:
        {
            if (tapi_confirm("删除", k[i]->key))
            {
                continue;
            }
            if (!fp_del_k(filename, k[i]->key))
            {
                tapi_toast_ok("删除成功");
            }
            break;
        }

        default:
            break;
        }

    } while (ret != -1);

    fp_free_k(&k, &n);

    return;
}

void app_termux_search_password(const char *filename)
{
    int ret = -2;

    char **p = NULL;
    size_t n = 0U;

    do
    {
        fp_free_p(&p, &n);
        if (fp_out_p(filename, &p, &n))
        {
            break;
        }
        if (!n)
        {
            ret = -1;
            tapi_toast_warning("无数据");
            break;
        }

        char *password = NULL;
        do
        {
            ret = tapi_text(&password, "密码", const_str_p, NULL);
        } while (ret < -1);
        if (ret == -1)
        {
            break;
        }

        if (fp_str_p(&p, &n, password))
        {
            break;
        }
        PFREE(free, password);
        if (!n)
        {
            tapi_toast_warning("无该密码");
            continue;
        }

        int   i  = 0;
        char *vs = NULL;

        ret = p2vsn(&vs, p, n);
        if (ret)
        {
            break;
        }
        do
        {
            ret = tapi_radio(NULL, &i, "结果", vs);
        } while (ret < -1);
        PFREE(free, vs);
        if (ret == -1)
        {
            ret = 0;
            continue;
        }

        if (tapi_confirm("删除", p[i]))
        {
            continue;
        }
        if (fp_del_p(filename, p[i]) == 0)
        {
            tapi_toast_ok("删除成功");
        }

    } while (ret != -1);

    fp_free_p(&p, &n);

    return;
}

/* END OF FILE */
