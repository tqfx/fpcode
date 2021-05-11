/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         fp.c/h
 * @brief        fp
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "fp.h"

#include "file.h"
#include "fp_json.h"
#include "fp_xml.h"

/* Private includes ----------------------------------------------------------*/

#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/

typedef enum
{
    FILE_TYPE_NONE,
    FILE_TYPE_JSON,
    FILE_TYPE_XML,
} file_type_t;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

static file_type_t fp_filetype(const char *filename)
{
    char *s = NULL;
    if (file_tr(filename, &s))
    {
        return FILE_TYPE_NONE;
    }

    file_type_t type = FILE_TYPE_NONE;

    do
    {
        cJSON *cjson = cJSON_Parse(s);
        if (cjson)
        {
            PFREE(cJSON_Delete, cjson);
            type = FILE_TYPE_JSON;
            break;
        }

        mxml_node_t *xml = mxmlLoadString(NULL, s, MXML_TEXT_CALLBACK);
        if (xml)
        {
            PFREE(mxmlDelete, xml);
            type = FILE_TYPE_XML;
            break;
        }

    } while (0);

    PFREE(free, s);
    return type;
}

int fp_str_p(char ***p, size_t *n, char *s)
{
    size_t count = 0U;

    for (size_t i = 0; i < *n; i++)
    {
        if (strstr((*p)[i], s))
        {
            (*p)[count++] = (*p)[i];
        }
        else
        {
            PFREE(free, (*p)[i]);
        }
    }

    if (!count)
    {
        fp_free_p(p, n);
    }
    else if (count < *n)
    {
        *p = (char **)realloc((void *)*p, sizeof(char *) * count);
        if (!*p)
        {
            return -1;
        }
        *n = count;
    }

    return 0;
}

int fp_str_k(fp_t ***k, size_t *n, char *s)
{
    size_t count = 0U;

    for (size_t i = 0; i < *n; i++)
    {
        if (strstr((*k)[i]->key, s))
        {
            (*k)[count++] = (*k)[i];
        }
        else
        {
            fp_free(*k + i);
        }
    }

    if (!count)
    {
        fp_free_k(k, n);
    }
    else if (count < *n)
    {
        *k = (fp_t **)realloc((void *)*k, sizeof(fp_t *) * count);
        if (!*k)
        {
            return -1;
        }
        *n = count;
    }

    return 0;
}

int fp_init(const char *filename)
{
    if (strstr(filename, ".json"))
    {
        return fp_json_init(filename);
    }
    else
    {
        return fp_xml_init(filename);
    }
}

int fp_add_p(const char *filename, const char *password)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_add_p(filename, password);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_add_p(filename, password);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_del_p(const char *filename, const char *password)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_del_p(filename, password);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_del_p(filename, password);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_add_k(const char *filename, const fp_t *fp)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_add_k(filename, fp);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_add_k(filename, fp);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_del_k(const char *filename, const char *key)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_del_k(filename, key);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_del_k(filename, key);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_del_i(const char *filename, const char *string, unsigned int i)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_del_i(filename, string, i);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_del_i(filename, string, i);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_out_p(const char *filename, char ***dst, size_t *n)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_out_p(filename, dst, n);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_out_p(filename, dst, n);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_out_k(const char *filename, fp_t ***dst, size_t *n)
{
    int ret = -1;

    switch (fp_filetype(filename))
    {
    case FILE_TYPE_XML:
    {
        ret = fp_xml_out_k(filename, dst, n);
        break;
    }

    case FILE_TYPE_JSON:
    {
        ret = fp_json_out_k(filename, dst, n);
        break;
    }

    case FILE_TYPE_NONE:
    default:
        break;
    }

    return ret;
}

int fp_import(const char *filename, const char *dataname)
{
    int ret = -1;

    do
    {
        size_t n = 0U;

        char **p = NULL;
        ret      = fp_out_p(dataname, &p, &n);
        if (ret)
        {
            break;
        }
        for (size_t i = 0; i < n; i++)
        {
            fp_add_p(filename, p[i]);
        }
        fp_free_p(&p, &n);

        fp_t **k = NULL;
        ret      = fp_out_k(dataname, &k, &n);
        if (ret)
        {
            break;
        }
        for (size_t i = 0; i < n; i++)
        {
            fp_add_k(filename, k[i]);
        }
        fp_free_k(&k, &n);

    } while (0);

    return ret;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
