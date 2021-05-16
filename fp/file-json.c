/**
 * *****************************************************************************
 * @file         file-json.c/h
 * @brief        some funtion of json file
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "file-json.h"

/* Private includes ----------------------------------------------------------*/

#include "cJSON.h"
#include "file.h"

/* Private user code ---------------------------------------------------------*/

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

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
