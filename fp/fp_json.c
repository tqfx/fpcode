/**
 * *****************************************************************************
 * @file         fp_json.c/h
 * @brief        fp_json
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "fp_json.h"

/* Private includes ----------------------------------------------------------*/

#include "file_json.h"
#include "fp.h"
#include "fp_crypt.h"

#include <stdlib.h>
#include <string.h>

/* Private function prototypes -----------------------------------------------*/

static int fp_json_del_s(const char *filename,
                         const char *string,
                         const char *str);

/* Private user code ---------------------------------------------------------*/

int cjson_array_k(char **dst, const cJSON *cjson, int index)
{
    return cjson_array_item_s(dst, cjson, const_str_k, index);
}

int fp_json_array(const char *filename, cJSON **dst, const char *string)
{
    cJSON *cjson = NULL;
    if (cjson_r(filename, &cjson))
    {
        return -1;
    }

    *dst = cJSON_DetachItemFromObject(cjson, string);

    PFREE(cJSON_Delete, cjson);

    return 0;
}

int fp_json_fp2json(const fp_t *fp, cJSON **dst)
{
    /* {} */
    *dst = cJSON_CreateObject();
    if (!*dst)
    {
        return -1;
    }

    int ret = -1;

    do
    {
        /* {"type":0} */
        if (!cJSON_AddNumberToObject(*dst, const_str_t, fp->type))
        {
            break;
        }

        /* {"type":0,"length":16} */
        if (!cJSON_AddNumberToObject(*dst, const_str_l, fp->len))
        {
            break;
        }

        /* {"type":0,"length":16,"key":""} */
        if (!cJSON_AddStringToObject(*dst, const_str_k, fp->key))
        {
            break;
        }

        /* {"type":0,"length":16,"key":"","new":""} */
        if (fp->type == FPTYPE_NEW &&
            !cJSON_AddStringToObject(*dst, const_str_n, fp->new))
        {
            break;
        }

        ret = 0;
    } while (0);

    if (ret)
    {
        PFREE(cJSON_Delete, *dst);
    }

    return ret;
}

int fp_json_json2fp(const cJSON *cjson, fp_t **fp)
{
    *fp = (fp_t *)malloc(sizeof(fp_t));
    if (!*fp)
    {
        return -1;
    }

    int ret = -1;

    do
    {
        cJSON *cjson_object = cJSON_GetObjectItem(cjson, const_str_t);
        if (!cjson_object)
        {
            break;
        }
        (*fp)->type = (fptype_e)cJSON_GetNumberValue(cjson_object);

        cjson_object = cJSON_GetObjectItem(cjson, const_str_l);
        if (!cjson_object)
        {
            break;
        }
        (*fp)->len = (uint32_t)cJSON_GetNumberValue(cjson_object);

        cjson_object = cJSON_GetObjectItem(cjson, const_str_k);
        if (!cjson_object)
        {
            break;
        }
        char *str = cJSON_GetStringValue(cjson_object);
        if (!str)
        {
            break;
        }
        (*fp)->key = (char *)malloc(sizeof(char) * (strlen(str) + 1U));
        if (!(*fp)->key)
        {
            break;
        }
        (void)strcpy((*fp)->key, str);

        if ((*fp)->type == FPTYPE_NEW)
        {
            cjson_object = cJSON_GetObjectItem(cjson, const_str_n);
            if (!cjson_object)
            {
                break;
            }
            str = cJSON_GetStringValue(cjson_object);
            if (!str)
            {
                break;
            }
            (*fp)->new = (char *)malloc(sizeof(char) * (strlen(str) + 1U));
            if (!(*fp)->new)
            {
                break;
            }
            (void)strcpy((*fp)->key, str);
        }
        else
        {
            (*fp)->new = NULL;
        }

        ret = 0;
    } while (0);

    if (ret)
    {
        PFREE(free, *fp);
    }

    return ret;
}

int fp_json_init(const char *filename)
{
    /* {} */
    cJSON *cjson = cJSON_CreateObject();
    if (!cjson)
    {
        return -1;
    }

    int ret = -1;

    do
    {
        /* {"password":[]} */
        if (!cJSON_AddItemToObject(cjson, const_str_p, cJSON_CreateArray()))
        {
            break;
        }

        /* {"password":[],"key":[]} */
        if (!cJSON_AddItemToObject(cjson, const_str_k, cJSON_CreateArray()))
        {
            break;
        }

        ret = cjson_w(filename, cjson);
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int fp_json_add_k(const char *filename, const fp_t *fp)
{
    cJSON *cjson = NULL;
    if (cjson_r(filename, &cjson))
    {
        return -1;
    }

    int ret = -1;

    do
    {
        cJSON *cjson_array = cJSON_GetObjectItem(cjson, const_str_k);
        if (!cjson_array)
        {
            break;
        }

        int i = cJSON_GetArraySize(cjson_array);
        while (--i + 1)
        {
            char *str_cjson = NULL;
            if (cjson_array_k(&str_cjson, cjson_array, i))
            {
                break;
            }
            if (!strcmp(str_cjson, fp->key))
            {
                cJSON_DeleteItemFromArray(cjson_array, i);
            }
            else if (strcmp(str_cjson, fp->key) < 0)
            {
                break;
            }
        }

        cJSON *cjson_item = NULL;
        if (fp_json_fp2json(fp, &cjson_item))
        {
            break;
        }

        if (!cJSON_InsertItemInArray(cjson_array, ++i, cjson_item))
        {
            PFREE(cJSON_Delete, cjson_item);
            break;
        }

        ret = cjson_w(filename, cjson);
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int fp_json_add_p(const char *filename, const char *password)
{
    cJSON *cjson = NULL;
    if (cjson_r(filename, &cjson))
    {
        return -1;
    }

    int   ret = -1;
    char *out = NULL;

    do
    {
        cJSON *cjson_array = cJSON_GetObjectItem(cjson, const_str_p);
        if (!cjson_array)
        {
            break;
        }

        int i = cJSON_GetArraySize(cjson_array);
        while (--i > -1)
        {
            char *str = NULL;
            if (cjson_array_s(&str, cjson_array, i))
            {
                break;
            }
            if (fp_dncrypt(str, &out, LEN_PASSWORD))
            {
                continue;
            }
            if (!strcmp(password, out))
            {
                cJSON_DeleteItemFromArray(cjson_array, i);
            }
            PFREE(free, out);
        }

        if (fp_encrypt(password, &out, LEN_PASSWORD))
        {
            break;
        }

        cJSON *cjson_str = cJSON_CreateString(out);
        if (!cjson_str)
        {
            break;
        }

        if (!cJSON_InsertItemInArray(cjson_array, 0, cjson_str))
        {
            PFREE(cJSON_Delete, cjson_str);
            break;
        }

        ret = cjson_w(filename, cjson);
    } while (0);

    PFREE(free, out);
    PFREE(cJSON_Delete, cjson);

    return ret;
}

int fp_json_del_i(const char *filename, const char *string, unsigned int id)
{
    cJSON *cjson = NULL;
    if (cjson_r(filename, &cjson))
    {
        return -1;
    }

    int ret = -1;

    do
    {
        cJSON *cjson_array = cJSON_GetObjectItem(cjson, string);
        if (!cjson_array)
        {
            break;
        }

        if ((unsigned int)cJSON_GetArraySize(cjson_array) > id)
        {
            cJSON_DeleteItemFromArray(cjson_array, (int)id);

            ret = cjson_w(filename, cjson);
        }
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

static int fp_json_del_s(const char *filename, const char *string, const char *str)
{
    int (*func)(char **, const cJSON *, int);
    if (!strcmp(string, const_str_k))
    {
        func = cjson_array_k;
    }
    else if (!strcmp(string, const_str_p))
    {
        func = cjson_array_s;
    }
    else
    {
        return -1;
    }

    cJSON *cjson = NULL;
    if (cjson_r(filename, &cjson))
    {
        return -1;
    }

    int ret = -1;

    do
    {
        cJSON *cjson_array = cJSON_GetObjectItem(cjson, string);
        if (!cjson_array)
        {
            break;
        }

        int i = cJSON_GetArraySize(cjson_array);
        while (--i > -1)
        {
            char *str_cjson = NULL;
            if (func(&str_cjson, cjson_array, i))
            {
                break;
            }

            char *out = NULL;
            if (func == cjson_array_s)
            {
                if (fp_dncrypt(str_cjson, &out, LEN_PASSWORD))
                {
                    break;
                }
                str_cjson = out;
            }

            if (!strcmp(str_cjson, str))
            {
                cJSON_DeleteItemFromArray(cjson_array, i);
                ret = 0;
            }

            if (func == cjson_array_s)
            {
                PFREE(free, out);
            }
        }

        if (!ret)
        {
            ret = cjson_w(filename, cjson);
        }
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int fp_json_del_k(const char *filename, const char *key)
{
    return fp_json_del_s(filename, const_str_k, key);
}

int fp_json_del_p(const char *filename, const char *password)
{
    return fp_json_del_s(filename, const_str_p, password);
}

int fp_json_out_k(const char *filename, fp_t ***dst, size_t *n)
{
    cJSON *cjson = NULL;
    if (fp_json_array(filename, &cjson, const_str_k))
    {
        return -1;
    }

    int ret = -1;

    do
    {
        *n = (size_t)cJSON_GetArraySize(cjson);
        if (*n)
        {
            *dst = (fp_t **)malloc(sizeof(fp_t *) * (*n));
            if (!*dst)
            {
                break;
            }
        }

        for (size_t i = 0U; i != *n; ++i)
        {
            cJSON *item = cJSON_GetArrayItem(cjson, (int)i);

            fp_t *fp = NULL;
            if (fp_json_json2fp(item, &fp))
            {
                break;
            }

            (*dst)[i] = fp;
        }

        ret = 0;
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

int fp_json_out_p(const char *filename, char ***dst, size_t *n)
{
    cJSON *cjson = NULL;
    if (fp_json_array(filename, &cjson, const_str_p))
    {
        return -1;
    }

    int ret = -1;

    do
    {
        *n = (size_t)cJSON_GetArraySize(cjson);
        if (*n)
        {
            *dst = (char **)malloc(sizeof(char *) * (*n));
            if (!*dst)
            {
                break;
            }
        }
        for (size_t i = 0U; i != *n; ++i)
        {
            char *in = NULL;
            if (cjson_array_s(&in, cjson, (int)i))
            {
                break;
            }
            char *out = NULL;
            if (fp_dncrypt(in, &out, LEN_PASSWORD))
            {
                break;
            }
            (*dst)[i] = out;
        }

        ret = 0;
    } while (0);

    PFREE(cJSON_Delete, cjson);

    return ret;
}

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
