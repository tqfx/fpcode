/*!
 @file           termux-tapi.c
 @brief          api termux packaging
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

#include "termux-tapi.h"

#include "cJSON.h"
#include "termux-api.h"

#include <stdlib.h>
#include <string.h>

typedef int (*dialog_ci_t)(char **, const char *, const char *);

static int tapi_dialog_ci(char **     text,
                          int *       index,
                          int         code,
                          const char *title,
                          const char *values,
                          dialog_ci_t func);

int tapi_auth_finger(void)
{
    int ret = -2;

    char *ss = NULL;
    if (termux_fingerprint(&ss, "验证", NULL, NULL, "取消"))
    {
        return ret;
    }
    cJSON *cjson = cJSON_Parse(ss);
    PFREE(free, ss);
    if (!cjson)
    {
        return ret;
    }

    do
    {
        ss = cJSON_GetStringValue(cJSON_GetObjectItem(cjson, "auth_result"));
        if (!ss)
        {
            break;
        }
        if (!strcmp(ss, "AUTH_RESULT_SUCCESS"))
        {
            ret = 0;
        }
        else if (!strcmp(ss, "AUTH_RESULT_FAILURE"))
        {
            ret = -1;
        }
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int tapi_confirm(const char *title, const char *hint)
{
    int ret = -2;

    char *ss = NULL;
    if (termux_dialog_confirm(&ss, title, hint))
    {
        return ret;
    }
    cJSON *cjson = cJSON_Parse(ss);
    PFREE(free, ss);
    if (!cjson)
    {
        return ret;
    }

    do
    {
        ss = cJSON_GetStringValue(cJSON_GetObjectItem(cjson, "text"));
        if (!ss)
        {
            break;
        }
        if (!strcmp(ss, "yes"))
        {
            ret = 0;
        }
        else if (!strcmp(ss, "no"))
        {
            ret = -1;
        }
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int tapi_checkbox(char ***    text,
                  int **      index,
                  int *       n,
                  const char *title,
                  const char *values)
{
    int ret = -2;

    char *ss = NULL;
    if (termux_dialog_checkbox(&ss, title, values))
    {
        return ret;
    }
    cJSON *cjson = cJSON_Parse(ss);
    PFREE(free, ss);
    if (!cjson)
    {
        return ret;
    }

    do
    {
        cJSON *cjson_object = cJSON_GetObjectItem(cjson, "code");
        if (!cjson_object)
        {
            break;
        }
        if (-1 != (int)cJSON_GetNumberValue(cjson_object))
        {
            ret = -1;
            break;
        }

        cjson_object = cJSON_GetObjectItem(cjson, "values");

        *n = cJSON_GetArraySize(cjson_object);
        if (*n)
        {
            if (text)
            {
                *text = (char **)malloc(sizeof(char *) * (size_t)(*n));
            }
            if (index)
            {
                *index = (int *)malloc(sizeof(int) * (size_t)(*n));
            }
        }

        for (int i = 0; i != *n; ++i)
        {
            cJSON *item = cJSON_GetArrayItem(cjson_object, i);
            if (index)
            {
                cJSON *num = cJSON_GetObjectItem(item, "index");
                if (num)
                {
                    (*index)[i] = (int)cJSON_GetNumberValue(num);
                }
            }
            if (text)
            {
                item = cJSON_GetObjectItem(item, "text");
                if (item)
                {
                    (*text)[i] = cJSON_GetStringValue(item);

                    item->valuestring = NULL;
                }
            }
        }

        ret = 0;
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int tapi_counter(long int *  pl,
                 const char *title,
                 const char *values)
{
    int ret = -2;

    char *ss = NULL;
    if (termux_dialog_counter(&ss, title, values))
    {
        return ret;
    }
    cJSON *cjson = cJSON_Parse(ss);
    PFREE(free, ss);
    if (!cjson)
    {
        return ret;
    }

    do
    {
        cJSON *cjson_object = cJSON_GetObjectItem(cjson, "code");
        if (!cjson)
        {
            break;
        }
        if (-1 != (int)cJSON_GetNumberValue(cjson_object))
        {
            ret = -1;
            break;
        }
        if (pl)
        {
            cjson_object = cJSON_GetObjectItem(cjson, "text");
            if (!cjson_object)
            {
                break;
            }
            *pl = atol(cJSON_GetStringValue(cjson_object));
        }

        ret = 0;
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

static int tapi_dialog_ci(char **     text,
                          int *       index,
                          int         code,
                          const char *title,
                          const char *values,
                          dialog_ci_t func)
{
    int ret = -2;

    char *ss = NULL;
    if (func(&ss, title, values))
    {
        return ret;
    }
    cJSON *cjson = cJSON_Parse(ss);
    PFREE(free, ss);
    if (!cjson)
    {
        return ret;
    }

    do
    {
        cJSON *cjson_object = cJSON_GetObjectItem(cjson, "code");
        if (!cjson)
        {
            break;
        }
        if (code != (int)cJSON_GetNumberValue(cjson_object))
        {
            ret = -1;
            break;
        }
        if (index)
        {
            cjson_object = cJSON_GetObjectItem(cjson, "index");
            if (!cjson_object)
            {
                break;
            }
            *index = (int)cJSON_GetNumberValue(cjson_object);
        }
        if (text)
        {
            cjson_object = cJSON_GetObjectItem(cjson, "text");
            if (!cjson_object)
            {
                break;
            }
            *text = cJSON_GetStringValue(cjson_object);

            cjson_object->valuestring = NULL;
        }

        ret = 0;
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int tapi_radio(char **     text,
               int *       index,
               const char *title,
               const char *values)
{
    return tapi_dialog_ci(text,
                          index,
                          -1,
                          title,
                          values,
                          termux_dialog_radio);
}

int tapi_sheet(char **     text,
               int *       index,
               const char *title,
               const char *values)
{
    return tapi_dialog_ci(text,
                          index,
                          0,
                          title,
                          values,
                          termux_dialog_sheet);
}

int tapi_spinner(char **     text,
                 int *       index,
                 const char *title,
                 const char *values)
{
    return tapi_dialog_ci(text,
                          index,
                          -1,
                          title,
                          values,
                          termux_dialog_spinner);
}

int tapi_text(char **     dst,
              const char *title,
              const char *hint,
              const char *op)
{
    int ret = -2;

    char *ss = NULL;
    if (termux_dialog_text(&ss, title, hint, op))
    {
        return ret;
    }
    cJSON *cjson = cJSON_Parse(ss);
    PFREE(free, ss);
    if (!cjson)
    {
        return ret;
    }

    do
    {
        cJSON *cjson_object = cJSON_GetObjectItem(cjson, "code");
        if (!cjson_object)
        {
            break;
        }
        if (-1 != (int)cJSON_GetNumberValue(cjson_object))
        {
            ret = -1;
            break;
        }
        if (dst)
        {
            cjson_object = cJSON_GetObjectItem(cjson, "text");
            if (!cjson_object)
            {
                break;
            }
            *dst = cJSON_GetStringValue(cjson_object);

            cjson_object->valuestring = NULL;
        }

        ret = 0;
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int tapi_toast_error(const char *text)
{
    return termux_toast(text, "red", "white", NULL, 1);
}

int tapi_toast_warning(const char *text)
{
    return termux_toast(text, "yellow", NULL, NULL, 1);
}

int tapi_toast_ok(const char *text)
{
    return termux_toast(text, "green", "white", NULL, 1);
}

/* END OF FILE */
