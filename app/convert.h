/*!
 @file           convert.h
 @brief          code conversion
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
#ifndef __CONVERT_H__
#define __CONVERT_H__

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

__BEGIN_DECLS

/*!
 @name           code_convert
 @brief          source charset transcoding destination charset
 @note           Note the support for C language localization
 @param[out]     dst: pointer of buffer variable
 @param[in]      dst_charset: charset of destination string
 @param[in]      src: source string
 @param[in]      src_charset: charset of source string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
#ifdef __WINNT__
extern int code_convert(char **      dst,
                        unsigned int dst_charset,
                        const char * src,
                        unsigned int src_charset);
#else
extern int code_convert(char **     dst,
                        const char *dst_charset,
                        const char *src,
                        const char *src_charset);
#endif /* __WINNT__ */

/*!
 @brief          utf-8 transcoding gbk
 @note           Note windows api
 @param[out]     dst: pointer of buffer variable
 @param[in]      src: source string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int utf8_gbk(char **dst, const char *src);

/*!
 @brief          gbk transcoding utf-8
 @note           Note windows api
 @param[out]     dst: pointer of buffer variable
 @param[in]      src: source string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int gbk_utf8(char **dst, const char *src);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __CONVERT_H__ */

/* END OF FILE */
