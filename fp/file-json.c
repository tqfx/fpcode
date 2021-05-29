/*!
 @file           file-json.c
 @brief          some funtion of json file
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

#include "file-json.h"

#include "cJSON.h"
#include "file.h"

int cjson_r(const char *restrict filename,
            cJSON **const restrict cjson)
{
#ifdef DEBUG_CHECK
    if (!filename || !cjson)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    char *s = NULL;

    int ret = file_tr(filename, &s);
    if (ret)
    {
        return ret;
    }

    *cjson = cJSON_Parse(s);
    PFREE(free, s);

    return ret;
}

int cjson_w(const char *restrict filename,
            const cJSON *restrict cjson)
{
#ifdef DEBUG_CHECK
    if (!filename || !cjson)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    int ret = -1;

    char *s = cJSON_PrintUnformatted(cjson);
    if (s)
    {
        ret = file_tw(filename, s);
        PFREE(free, s);
    }

    return ret;
}

int cjson_array_item_s(char **const restrict dst,
                       const cJSON *restrict cjson,
                       const char *restrict string,
                       int index)
{
#ifdef DEBUG_CHECK
    if (!dst || !cjson || !string || index < 0)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    int ret = -1;

    do
    {
        /* [{"string":"*dst"}, {"s":"*dst"}] */
        cjson = cJSON_GetArrayItem(cjson, index);
        if (!cjson)
        {
            break;
        }

        cjson = cJSON_GetObjectItem(cjson, string);
        if (!cjson)
        {
            break;
        }

        *dst = cJSON_GetStringValue(cjson);
        if (*dst)
        {
            ret = 0;
        }

    } while (0);

    return ret;
}

int cjson_array_s(char **const restrict dst,
                  const cJSON *restrict cjson,
                  int index)
{
#ifdef DEBUG_CHECK
    if (!dst || !cjson || index < 0)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    int ret = -1;

    do
    {
        /* ["*dst", "*dst"] */
        cjson = cJSON_GetArrayItem(cjson, index);
        if (!cjson)
        {
            break;
        }

        *dst = cJSON_GetStringValue(cjson);
        if (*dst)
        {
            ret = 0;
        }

    } while (0);

    return ret;
}

/* END OF FILE */
