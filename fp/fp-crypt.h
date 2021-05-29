/*!
 @file           fp-crypt.h
 @brief          crypt fp
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
#ifndef __FP_CRYPT_H__
#define __FP_CRYPT_H__

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
 @brief          Encrypt password
 @param[in]      in: the password need to encrypt
 @param[out]     out: the pointer
 @param[in]      len: length of password
 @return         The state of the file exists
  @retval        0  success
  @retval        -1 failure
*/
extern int fp_encrypt(const char *restrict in,
                      char **const restrict out,
                      unsigned int len);

/*!
 @brief          Dncrypt password
 @param[in]      in: the password encrypted
 @param[out]     out: the pointer
 @param[in]      len: length of password
 @return         The state of the file exists
  @retval        0  success
  @retval        -1 failure
*/
extern int fp_dncrypt(const char *restrict in,
                      char **const restrict out,
                      unsigned int len);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __FP_CRYPT_H__ */

/* END OF FILE */
