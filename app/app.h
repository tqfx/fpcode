/**
 * *****************************************************************************
 * @file         app.c/h
 * @brief        application
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_H__
#define __APP_H__

/* Includes ------------------------------------------------------------------*/

#include "convert.h"
#include "file.h"
#include "fp.h"
#include "kstring.h"

/* Private includes ----------------------------------------------------------*/

#include <stdbool.h>

/* Exported constants --------------------------------------------------------*/

#define LEN_PASSWORD 32U

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int app_fpcode(const char *password,
                      const fp_t *pcode);
extern int app_data_init(const char *filename);

extern int app_add_key(const char *filename,
                       const fp_t *code);
extern int app_add_password(const char *filename,
                            const char *password);

extern int app_del_key(const char *filename,
                       const char *key,
                       bool        id);
extern int app_del_password(const char *filename,
                            const char *password,
                            bool        id);

extern int app_show_key(const char *filename,
                        const char *key);
extern int app_show_password(const char *filename,
                             const char *password);

extern int app_get_id(const char * filename,
                      unsigned int id_k,
                      unsigned int id_p);
extern int app_get_key(const char *filename,
                       const fp_t *pcode);

extern int app_key_import(const char *filename,
                          const char *dataname);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __APP_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
