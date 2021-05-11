/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         fp_crypt.c/h
 * @brief        crypt fp
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __FP_CRYPT_H__
#define __FP_CRYPT_H__

/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief        encrypt password
 * @param[in]    in the password need to encrypt
 * @param[out]   out the pointer
 * @param[in]    len length of password
 * @return       int 0 SUCCESS -1 FAILURE
*/
extern int fp_encrypt(const char *in, char **out, unsigned int len);

/**
 * @brief        dncrypt password
 * @param[in]    in the password encrypted
 * @param[out]   out the pointer
 * @param[in]    len length of password
 * @return       int 0 SUCCESS -1 FAILURE
*/
extern int fp_dncrypt(const char *in, char **out, unsigned int len);

__END_DECLS

/* Private defines -----------------------------------------------------------*/

#endif /* __FP_CRYPT_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
