/*!
 @file           main-cb.c
 @brief          main call back
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

#include "app.h"
#include "main.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *filename = NULL;
static char *dataname = NULL;
static char *password = NULL;

static fp_t code = {
    .key = NULL,
    .new = NULL,
    .len = 16U,
    .type = FPTYPE_EMAIL,
};
static bool bool_id = false;
static bool bool_show = false;
static bool bool_add = false;
static bool bool_del = false;

static int prefix_home(char **s);

static int prefix_home(char **s)
{
    if (strchr(*s, '~'))
    {
        kstring_t *ks = ks_init();
        (void)ksprintf(ks, "%s", *s);

        if (getenv("HOME"))
        {
            (void)ks_mod(ks, "~", getenv("HOME"));
        }
        else if (getenv("HOMEPATH") && getenv("HOMEDRIVE"))
        {
            kstring_t *tmp_ks = ks_init();
            (void)ksprintf(tmp_ks, "%s%s", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
            (void)ks_mod(ks, "~", ks_str(tmp_ks));
            PFREE(ks_free, tmp_ks);
        }
        else
        {
            PFREE(ks_free, ks);
            return -1;
        }

        free(*s);
        *s = ks_release(ks);
        PFREE(ks_free, ks);
    }

    return 0;
}

void main_str_cb(const char *args)
{
    if (!strcmp(args, "--id"))
    {
        bool_id = true;
    }
    else if (!strcmp(args, "--add"))
    {
        bool_add = true;
    }
    else if (!strcmp(args, "--del"))
    {
        bool_del = true;
    }
    else if (!strcmp(args, "--show"))
    {
        bool_show = true;
    }
    else
    {
        (void)printf("invalid  --  %s\n", args);
    }
    return;
}

void main_char_cb(char ch)
{
    switch (ch)
    {
    case 'i':
        bool_id = true;
        break;
    case 'a':
        bool_add = true;
        break;
    case 'd':
        bool_del = true;
        break;
    case 's':
        bool_show = true;
        break;
    default:
        (void)printf("invalid  -  %c\n", ch);
        break;
    }
    return;
}

void main_arg_cb(const char *argp, const char *args)
{
    if (!strcmp(argp, "-f") || !strcmp(argp, "--filename"))
    {
        filename = oc_strcpy(args);
        prefix_home(&filename);
    }
    else if (!strcmp(argp, "-k") || !strcmp(argp, "--key"))
    {
        code.key = oc_strcpy(args);
    }
    else if (!strcmp(argp, "-p") || !strcmp(argp, "--password"))
    {
        password = oc_strcpy(args);
    }
    else if (!strcmp(argp, "-n") || !strcmp(argp, "--new"))
    {
        code.new = oc_strcpy(args);
    }
    else if (!strcmp(argp, "-l") || !strcmp(argp, "--length"))
    {
        sscanf(args, "%u", &code.len);
        if (code.len > LEN_PASSWORD)
        {
            code.len = LEN_PASSWORD;
        }
    }
    else if (!strcmp(argp, "-t") || !strcmp(argp, "--type"))
    {
        sscanf(args, "%u", &code.type);
        if (code.type > FPTYPE_NEW)
        {
            code.type = FPTYPE_EMAIL;
        }
    }
    else if (!strcmp(argp, "--import"))
    {
        dataname = oc_strcpy(args);
        prefix_home(&dataname);
    }
    else
    {
        (void)printf("invalid  arg  %s %s\n", argp, args);
    }
    return;
}

int main_cb(int argc, char *argv[])
{
    int ret = 0;
    (void)argc;

    if (!filename)
    {
        char *s = *argv;

#ifdef __clang__
        s = getenv("_");
#endif /* __clang__ */

        if (strstr(s, ".exe"))
        {
            s[strlen(s) - 4U] = 0;
        }

        kstring_t *ks = ks_init();
        if (strstr(s, "/") || strstr(s, "\\"))
        {
            ksprintf(ks, "%s%s", s, ".xml");
        }
        else
        {
            ksprintf(ks, "./%s%s", s, ".xml");
        }
        filename = ks_release(ks);
        PFREE(ks_free, ks);
    }

    if (!file_exist(filename))
    {
        ret = app_data_init(filename);
    }

    if (code.key)
    {
#ifdef __WINNT__
        char *tmp = NULL;
        gbk_utf8(&tmp, code.key);
        free(code.key);
        code.key = tmp;
        tmp = NULL;
#endif
    }

    if (dataname)
    {
        ret = app_key_import(filename, dataname);
        PFREE(free, dataname);
    }
    else if (bool_del)
    {
        if (password)
        {
            ret = app_del_password(filename, password, bool_id);
        }
        if (code.key)
        {
            ret = app_del_key(filename, code.key, bool_id);
        }
    }
    else if (bool_add)
    {
        if (password)
        {
            ret = app_add_password(filename, password);
        }
        if (code.key)
        {
            ret = app_add_key(filename, &code);
        }
    }
    else if (bool_show && !bool_id)
    {
        if (password)
        {
            ret = app_show_password(filename, password);
        }
        if (code.key)
        {
            ret = app_show_key(filename, code.key);
        }
    }
    else if (code.key && bool_id)
    {
        unsigned int id_k = 0U;
        unsigned int id_p = 0U;

        (void)sscanf(code.key, "%u", &id_k);
        if (password)
        {
            (void)sscanf(password, "%u", &id_p);
        }

        ret = app_get_id(filename, id_k, id_p);
    }
    else if (code.key)
    {
        if (password)
        {
            ret = app_fpcode(password, &code);
        }
        else
        {
            ret = app_get_key(filename, &code);
        }
    }

    PFREE(free, filename);
    if (password)
    {
        PFREE(free, password);
    }
    if (code.key)
    {
        PFREE(free, code.key);
    }
    if (code.new)
    {
        PFREE(free, code.new);
    }

    return ret;
}

/* END OF FILE */
