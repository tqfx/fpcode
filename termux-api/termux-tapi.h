/*!
 @file           termux-tapi.h
 @brief          api termux packaging
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
#ifndef __TERMUX_TAPI_H__
#define __TERMUX_TAPI_H__

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
 @brief          Validation of the fingerprint
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_auth_finger(void);

/*!
 @brief          Show confirmation dialog
 @param[in]      title: set title of dialog (optional)
 @param[in]      hint: text hint (optional)
 @return         The state
  @retval        0  yes
  @retval        -1 no
  @retval        -2 error
*/
extern int tapi_confirm(const char *title,
                        const char *hint);

/*!
 @brief          Select multiple values using checkboxes
 @param[out]     text: the pointer of test list
 @param[out]     index: the pointer of index list
 @param[out]     n: the pointer of list length
 @param[in]      title: set title of dialog (optional)
 @param[in]      values: comma delim values to use (required)
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_checkbox(char ***    text,
                         int **      index,
                         int *       n,
                         const char *title,
                         const char *values);

/*!
 @brief          Pick a number in specified range
 @param[out]     pl: the pointer of count variable
 @param[in]      title: set title of dialog (optional)
 @param[in]      values: comma delim values to use (required)
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_counter(long int *  pl,
                        const char *title,
                        const char *values);

/*!
 @brief          Pick a single value from radio buttons
 @param[out]     text: the pointer of text variable
 @param[out]     index: the pointer of index variable
 @param[in]      title: set title of dialog (optional)
 @param[in]      values: comma delim values to use (required)
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_radio(char **     text,
                      int *       index,
                      const char *title,
                      const char *values);

/*!
 @brief          Pick a value from sliding bottom sheet
 @param[out]     text: the pointer of text variable
 @param[out]     index: the pointer of index variable
 @param[in]      title: set title of dialog (optional)
 @param[in]      values: comma delim values to use (required)
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_sheet(char **     text,
                      int *       index,
                      const char *title,
                      const char *values);

/*!
 @brief          Pick a single value from a dropdown spinner
 @param[out]     text: the pointer of text variable
 @param[out]     index: the pointer of index variable
 @param[in]      title: set title of dialog (optional)
 @param[in]      values: comma delim values to use (required)
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_spinner(char **     text,
                        int *       index,
                        const char *title,
                        const char *values);

/*!
 @brief          nput text (default if no widget specified)
 @param[out]     dst: the pointer of buffer variable
 @param[in]      title: set title of dialog (optional)
 @param[in]      hint: text hint (optional)
 @param[in]      op: optional
  @arg           m multiple lines instead of single (optional)
  @arg           n enter input as numbers (optional)
  @arg           p enter input as password (optional)
 @note           cannot use m with n
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_text(char **     dst,
                     const char *title,
                     const char *hint,
                     const char *op);
/*!
 @brief          Show error in a Toast.
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_toast_error(const char *text);

/*!
 @brief          Show warning in a Toast.
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_toast_warning(const char *text);

/*!
 @brief          Show ok in a Toast.
 @return         The state
  @retval        0  success
  @retval        -1 failure
  @retval        -2 error
*/
extern int tapi_toast_ok(const char *text);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __TERMUX_TAPI_H__ */

/* END OF FILE */
