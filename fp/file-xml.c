/*!
 @file           file-xml.c
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

#include "file-xml.h"

int mxml_r(const char *restrict filename,
           mxml_node_t **const xml)
{
#ifdef DEBUG_CHECK
    if (!filename || !xml)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        return -1;
    }

    *xml = mxmlLoadFile(*xml, fp, MXML_TEXT_CALLBACK);

    PFREE(fclose, fp);

    return 0;
}

int mxml_w(const char *restrict filename,
           mxml_node_t *restrict xml)
{
#ifdef DEBUG_CHECK
    if (!filename || !xml)
    {
        return -1;
    }
#endif /* DEBUG_CHECK */
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        return -1;
    }

    int ret = mxmlSaveFile(xml, fp, MXML_TEXT_CALLBACK);

    PFREE(fclose, fp);

    return ret;
}

/* END OF FILE */
