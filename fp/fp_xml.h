/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         fp_xml.c/h
 * @brief        fp_xml
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __FP_XML_H__
#define __FP_XML_H__

/* Includes ------------------------------------------------------------------*/

#include "file_xml.h"
#include "fp.h"

/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int fp_xml_fp2xml(const fp_t *fp, mxml_node_t **xml);
extern int fp_xml_xml2fp(mxml_node_t *xml, fp_t **fp);

extern int fp_xml_init(const char *filename);

extern int fp_xml_add_p(const char *filename, const char *password);
extern int fp_xml_del_p(const char *filename, const char *password);
extern int fp_xml_add_k(const char *filename, const fp_t *fp);
extern int fp_xml_del_k(const char *filename, const char *key);

extern int fp_xml_del_i(const char *filename, const char *string, unsigned int i);

extern int fp_xml_out_p(const char *filename, char ***dst, size_t *n);
extern int fp_xml_out_k(const char *filename, fp_t ***dst, size_t *n);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __FP_XML_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
