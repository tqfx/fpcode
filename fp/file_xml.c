/**
 * *****************************************************************************
 * @file         file_xml.c/h
 * @brief        some function of file xml
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "file_xml.h"

/* Private user code ---------------------------------------------------------*/

int mxml_r(const char *filename, mxml_node_t **xml)
{
#ifdef DEBUG
    if (!filename || !xml)
    {
        return -1;
    }
#endif /* DEBUG */
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        return -1;
    }

    *xml = mxmlLoadFile(*xml, fp, MXML_TEXT_CALLBACK);

    PFREE(fclose, fp);

    return 0;
}

int mxml_w(const char *filename, mxml_node_t *xml)
{
#ifdef DEBUG
    if (!filename || !xml)
    {
        return -1;
    }
#endif /* DEBUG */
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
