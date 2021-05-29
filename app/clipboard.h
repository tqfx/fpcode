/*!
 @file           clipboard.h
 @brief          clipboard
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
#ifndef __CLIPBOARD_H__
#define __CLIPBOARD_H__

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

#ifdef __WINNT__

/*!
 @brief          Set the clipboard of windows
 @param[in]      str: the data
 @return         int the WINBOOL
*/
extern int clipboard_set(const char *str);

/*!
 @brief          Get the clipboard of windows
 @param[out]     str: the data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int clipboard_get(char **dst);

#endif /* __WINNT__ */

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __CLIPBOARD_H__ */

/* END OF FILE */
