/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         file_xml.c/h
 * @brief        some function of file xml
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "file_xml.h"

/* Private includes ----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
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

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
