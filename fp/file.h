/*!
 @file           file.h
 @brief          some function of the file
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
#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

#undef PFREE
#define PFREE(_FUN_, _) \
    do                  \
    {                   \
        (void)_FUN_(_); \
        _ = NULL;       \
    } while (0)

__BEGIN_DECLS

/*!
 @brief          Read the entire contents of the binary file
 @param[in]      filename: File name to be operated
 @param[out]     dst: The address where the first address of data is stored
 @param[out]     sz: The address where the number of data is stored
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int file_br(const char *restrict filename,
                   void **const restrict dst,
                   size_t *const restrict sz);

/*!
 @brief          Write data to binary file
 @param[in]      filename: File name to be operated
 @param[out]     dst: The first address of data to be written
 @param[out]     sz: The number of data to be written
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int file_bw(const char *restrict filename,
                   const void *restrict src,
                   size_t sz);

/*!
 @brief          Read the entire contents of the text file
 @param[in]      filename: File name to be operated
 @param[out]     dst: The address where the first address of string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int file_tr(const char *restrict filename,
                   char **const restrict dst);

/*!
 @brief          Write data to text file
 @param[in]      filename: File name to be operated
 @param[out]     dst: The first address of string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int file_tw(const char *restrict filename,
                   const char *restrict src);

/*!
 @brief          Check if the file exists
 @param[in]      filename: File name to be operated
 @return         The state of the file exists
  @retval        1 yes
  @retval        0 no
*/
extern int file_exist(const char *restrict filename);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __FILE_H__ */

/* END OF FILE */
