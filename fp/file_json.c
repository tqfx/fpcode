/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         file_json.c/h
 * @brief        some funtion of json file
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "file_json.h"

/* Private includes ----------------------------------------------------------*/

#include "cJSON.h"
#include "file.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

int cjson_r(const char *filename, cJSON **const dst)
{
#ifdef DEBUG
    if (!filename || !cjson)
    {
        return -1;
    }
#endif /* DEBUG */
    char *s   = NULL;
    int   ret = file_tr(filename, &s);
    if (ret)
    {
        return ret;
    }

    *dst = cJSON_Parse(s);
    PFREE(free, s);

    return ret;
}

int cjson_w(const char *filename, const cJSON *cjson)
{
#ifdef DEBUG
    if (!filename || !cjson)
    {
        return -1;
    }
#endif /* DEBUG */
    int   ret = -1;
    char *s   = cJSON_PrintUnformatted(cjson);
    if (s)
    {
        ret = file_tw(filename, s);
        PFREE(free, s);
    }

    return ret;
}

int cjson_array_item_s(char **dst, const cJSON *cjson, const char *string, int index)
{
#ifdef DEBUG
    if (!dst || !cjson || !string || index < 0)
    {
        return -1;
    }
#endif /* DEBUG */
    int ret = -1;

    do
    {
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

int cjson_array_s(char **dst, const cJSON *cjson, int index)
{
#ifdef DEBUG
    if (!dst || !cjson || index < 0)
    {
        return -1;
    }
#endif /* DEBUG */
    int ret = -1;

    do
    {
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

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
