/*!
 @file           file-xml.h
 @brief          some funtion of xml file
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
#ifndef __FILE_XML_H__
#define __FILE_XML_H__

#include "file.h"
#include "mxml.h"

__BEGIN_DECLS

/*!
 @brief          Read mxml_node_t object from XML file
 @param[in]      filename: The XML file name to be operated
 @param[out]     xml: The address of the mxml_node_t pointer
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int mxml_r(const char *restrict filename,
                  mxml_node_t **const restrict xml);

/*!
 @brief          Write mxml_node_t object to XML file
 @param[in]      filename: The XML file name to be operated
 @param[in]      xml: The mxml_node_t pointer
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int mxml_w(const char *restrict filename,
                  mxml_node_t *restrict xml);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __FILE_XML_H__ */

/* END OF FILE */
