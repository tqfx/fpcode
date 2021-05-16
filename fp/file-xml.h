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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FILE_XML_H__
#define __FILE_XML_H__

/* Includes ------------------------------------------------------------------*/

#include "file.h"
#include "mxml.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int mxml_r(const char *filename, mxml_node_t **xml);

extern int mxml_w(const char *filename, mxml_node_t *xml);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FILE_XML_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
