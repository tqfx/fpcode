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

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __FILE_XML_H__
#define __FILE_XML_H__

/* Includes ------------------------------------------------------------------*/

#include "file.h"
#include "mxml.h"

/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int mxml_r(const char *filename, mxml_node_t **xml);

extern int mxml_w(const char *filename, mxml_node_t *xml);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __FILE_XML_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
