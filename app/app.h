/*!
 @file           app.h
 @brief          application
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
#ifndef __APP_H__
#define __APP_H__

#include "convert.h"
#include "file.h"
#include "fp.h"
#include "kstring.h"

#include <stdbool.h>

#define LEN_PASSWORD 32U

__BEGIN_DECLS

extern int app_fpcode(const char *password,
                      const fp_t *pcode);
extern int app_data_init(const char *filename);

extern int app_add_key(const char *filename,
                       const fp_t *code);
extern int app_add_password(const char *filename,
                            const char *password);

extern int app_del_key(const char *filename,
                       const char *key,
                       bool        id);
extern int app_del_password(const char *filename,
                            const char *password,
                            bool        id);

extern int app_show_key(const char *filename,
                        const char *key);
extern int app_show_password(const char *filename,
                             const char *password);

extern int app_get_id(const char * filename,
                      unsigned int id_k,
                      unsigned int id_p);
extern int app_get_key(const char *filename,
                       const fp_t *pcode);

extern int app_key_import(const char *filename,
                          const char *dataname);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __APP_H__ */

/* END OF FILE */
