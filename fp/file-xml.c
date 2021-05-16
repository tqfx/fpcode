/**
 * *****************************************************************************
 * @file         file-xml.c/h
 * @brief        some function of file xml
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "file-xml.h"

/* Private user code ---------------------------------------------------------*/

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

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
