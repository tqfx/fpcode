/**
 * *****************************************************************************
 * @file         fp_json.c/h
 * @brief        fp_json
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __FP_JSON__
#define __FP_JSON__

/* Includes ------------------------------------------------------------------*/

#include "file-json.h"
#include "fp-crypt.h"
#include "fp.h"

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern int cjson_array_k(char **dst, const cJSON *cjson, int index);
extern int fp_json_array(const char *filename, cJSON **dst, const char *string);

extern int fp_json_fp2json(const fp_t *fp, cJSON **pcjson);
extern int fp_json_json2fp(const cJSON *pcjson, fp_t **fp);

extern int fp_json_init(const char *filename);

extern int fp_json_add_k(const char *filename, const fp_t *fp);
extern int fp_json_add_p(const char *filename, const char *password);

extern int fp_json_del_i(const char * filename,
                         const char * string,
                         unsigned int id);

extern int fp_json_del_k(const char *filename, const char *key);
extern int fp_json_del_p(const char *filename, const char *password);

extern int fp_json_out_k(const char *filename, fp_t ***dst, size_t *n);
extern int fp_json_out_p(const char *filename, char ***dst, size_t *n);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FP_JSON__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
