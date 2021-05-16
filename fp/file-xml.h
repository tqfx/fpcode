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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FILE_XML_H__
#define __FILE_XML_H__

/* Includes ------------------------------------------------------------------*/

#include "file.h"
#include "mxml.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief          Read mxml_node_t object from XML file
 * @param[in]      filename: The XML file name to be operated
 * @param[out]     xml: The address of the mxml_node_t pointer
 * @return         int 0(success) -1(failure)
*/
extern int mxml_r(const char *restrict filename,
                  mxml_node_t **const restrict xml);

/**
 * @brief          Write mxml_node_t object to XML file
 * @param[in]      filename: The XML file name to be operated
 * @param[in]      xml: The mxml_node_t pointer
 * @return         int 0(success) -1(failure)
*/
extern int mxml_w(const char *restrict filename,
                  mxml_node_t *restrict xml);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FILE_XML_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
