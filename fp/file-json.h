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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FILE_JSON_H__
#define __FILE_JSON_H__

/* Includes ------------------------------------------------------------------*/

#include "cJSON.h"
#include "file.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief          Read cJOSN object from json file
 * @param[in]      filename: The json file name to be operated
 * @param[out]     cjson: The address of the cJSON pointer
 * @return         int 0(success) -1(failure)
*/
extern int cjson_r(const char *restrict filename,
                   cJSON **const restrict cjson);

/**
 * @brief          Write cJOSN object to json file
 * @param[in]      filename: The json file name to be operated
 * @param[in]      cjson: The cJSON pointer
 * @return         int 0(success) -1(failure)
*/
extern int cjson_w(const char *restrict filename,
                   const cJSON *restrict cjson);

/**
 * @brief          Get string of array
 * @param[out]     dst: the pointer of buffer variable
 * @param[in]      cjson: cJSON pointer of array
 * @param[in]      string: string of object
 * @param[in]      index: index of string
 * @return         string
*/
extern int cjson_array_item_s(char **const restrict dst,
                              const cJSON *restrict cjson,
                              const char *restrict string,
                              int index);

/**
 * @brief          Get string of array
 * @param[out]     dst: the pointer of buffer variable
 * @param[in]      cjson: cJSON pointer of array
 * @param[in]      index: index of string
 * @return         string
*/
extern int cjson_array_s(char **const restrict dst,
                         const cJSON *restrict cjson,
                         int index);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FILE_JSON_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
