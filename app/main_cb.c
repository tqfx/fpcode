/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         main_cb.c
 * @brief        main call back
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private includes ----------------------------------------------------------*/

#include "app.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static const char const_filename[] = ".fp.xml";

static char *filename = NULL;
static char *dataname = NULL;
static char *password = NULL;

static fp_t code      = {NULL, 16U, 0U};
static bool bool_id   = false;
static bool bool_show = false;
static bool bool_add  = false;
static bool bool_del  = false;

/* Private function prototypes -----------------------------------------------*/

static int prefix_home(char **s);

/* Private user code ---------------------------------------------------------*/

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
    else if (!strcmp(argp, "-l") || !strcmp(argp, "--length"))
    {
        sscanf(args, "%hhu", &code.len);
        if (code.len > LEN_PASSWORD)
        {
            code.len = (uint8_t)LEN_PASSWORD;
        }
    }
    else if (!strcmp(argp, "-t") || !strcmp(argp, "--type"))
    {
        sscanf(args, "%u", &code.type);
        if (code.type > FP_TYPE_DIGITAL)
        {
            code.type = FP_TYPE_DIGITAL;
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

    if (!filename)
    {
        char *s = getenv("_");
        if (!s)
        {
            s = argv[!argc];
        }

        size_t n = strlen(s);
        for (size_t i = n; i < n + 1U; i--)
        {
            if (s[i] == '\\' || s[i] == '/')
            {
                break;
            }
            else
            {
                s[i] = 0;
            }
        }

        kstring_t *ks = ks_init();
        ksprintf(ks, "%s%s", s, const_filename);
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
        tmp      = NULL;
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

    return ret;
}
