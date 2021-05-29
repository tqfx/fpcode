/*!
 @file           app-termux.h
 @brief          application on termux
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
#ifndef __APP_TERMUX_H__
#define __APP_TERMUX_H__

#include "termux-tapi.h"

__BEGIN_DECLS

extern void app_termux_show_key(const char *filename);

extern void app_termux_del_key(const char *filename);
extern void app_termux_del_password(const char *filename);

extern void app_termux_add_key(const char *filename);
extern void app_termux_add_password(const char *filename);

extern void app_termux_search_key(const char *filename);
extern void app_termux_search_password(const char *filename);

extern void app_termux_create(const char *filename);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __APP_TERMUX_H__ */

/* END OF FILE */
