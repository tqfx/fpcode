/*!
 @file           fp-xml.h
 @brief          xml of fp
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
#ifndef __FP_XML_H__
#define __FP_XML_H__

#include "file-xml.h"
#include "fp.h"

__BEGIN_DECLS

extern int fp_xml_fp2xml(const fp_t *fp,
                         mxml_node_t **xml);
extern int fp_xml_xml2fp(mxml_node_t *xml,
                         fp_t **fp);

extern int fp_xml_init(const char *filename);

extern int fp_xml_add_p(const char *filename,
                        const char *password);
extern int fp_xml_del_p(const char *filename,
                        const char *password);
extern int fp_xml_add_k(const char *filename,
                        const fp_t *fp);
extern int fp_xml_del_k(const char *filename,
                        const char *key);

extern int fp_xml_del_i(const char *filename,
                        const char *string,
                        unsigned int i);

extern int fp_xml_out_p(const char *filename,
                        char ***dst,
                        size_t *n);
extern int fp_xml_out_k(const char *filename,
                        fp_t ***dst,
                        size_t *n);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __FP_XML_H__ */

/* END OF FILE */
