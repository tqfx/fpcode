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

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __FILE_JSON_H__
#define __FILE_JSON_H__

/* Includes ------------------------------------------------------------------*/

#include "cJSON.h"
#include "file.h"

/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int cjson_r(const char *filename, cJSON **const dst);

extern int cjson_w(const char *filename, const cJSON *cjson);

/**
 * @brief        get string of array
 * @param[out]   dst the pointer of buffer variable
 * @param[in]    cjson cJSON pointer of array
 * @param[in]    string string of object
 * @param[in]    index index of string
 * @return       string
*/
extern int cjson_array_item_s(char **dst, const cJSON *cjson, const char *string, int index);

/**
 * @brief        get string of array
 * @param[out]   dst the pointer of buffer variable
 * @param[in]    cjson cJSON pointer of array
 * @param[in]    index index of string
 * @return       string
*/
extern int cjson_array_s(char **dst, const cJSON *cjson, int index);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __FILE_JSON_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
