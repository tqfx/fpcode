/**
 * *****************************************************************************
 * @file         file_json.c/h
 * @brief        some funtion of json file
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FILE_JSON_H__
#define __FILE_JSON_H__

/* Includes ------------------------------------------------------------------*/

#include "cJSON.h"
#include "file.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int cjson_r(const char *filename, cJSON **const cjson);

extern int cjson_w(const char *filename, const cJSON *cjson);

/**
 * @brief          Get string of array
 * @param[out]     dst: the pointer of buffer variable
 * @param[in]      cjson: cJSON pointer of array
 * @param[in]      string: string of object
 * @param[in]      index: index of string
 * @return         string
*/
extern int cjson_array_item_s(char **      dst,
                              const cJSON *cjson,
                              const char * string,
                              int          index);

/**
 * @brief          Get string of array
 * @param[out]     dst: the pointer of buffer variable
 * @param[in]      cjson: cJSON pointer of array
 * @param[in]      index: index of string
 * @return         string
*/
extern int cjson_array_s(char **      dst,
                         const cJSON *cjson,
                         int          index);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FILE_JSON_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
