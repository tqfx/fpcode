/*!
 @file           file-json.h
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

/* Define to prevent recursive inclusion */
#ifndef __FILE_JSON_H__
#define __FILE_JSON_H__

#include "cJSON.h"
#include "file.h"

__BEGIN_DECLS

/*!
 @brief          Read cJOSN object from json file
 @param[in]      filename: The json file name to be operated
 @param[out]     cjson: The address of the cJSON pointer
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int cjson_r(const char *restrict filename,
                   cJSON **const restrict cjson);

/*!
 @brief          Write cJOSN object to json file
 @param[in]      filename: The json file name to be operated
 @param[in]      cjson: The cJSON pointer
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int cjson_w(const char *restrict filename,
                   const cJSON *restrict cjson);

/*!
 @brief          Get string of array
 @param[out]     dst: the pointer of buffer variable
 @param[in]      cjson: cJSON pointer of array
 @param[in]      string: string of object
 @param[in]      index: index of string
 @return         string
*/
extern int cjson_array_item_s(char **const restrict dst,
                              const cJSON *restrict cjson,
                              const char *restrict string,
                              int index);

/*!
 @brief          Get string of array
 @param[out]     dst: the pointer of buffer variable
 @param[in]      cjson: cJSON pointer of array
 @param[in]      index: index of string
 @return         string
*/
extern int cjson_array_s(char **const restrict dst,
                         const cJSON *restrict cjson,
                         int index);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __FILE_JSON_H__ */

/* END OF FILE */
