/**
 * *****************************************************************************
 * @file         fp_crypt.c/h
 * @brief        crypt fp
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FP_CRYPT_H__
#define __FP_CRYPT_H__

/* Exported macro ------------------------------------------------------------*/

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @brief          Encrypt password
 * @param[in]      in: the password need to encrypt
 * @param[out]     out: the pointer
 * @param[in]      len: length of password
 * @return         int 0(SUCCESS) -1(FAILURE)
*/
extern int fp_encrypt(const char *in, char **out, unsigned int len);

/**
 * @brief          Dncrypt password
 * @param[in]      in: the password encrypted
 * @param[out]     out: the pointer
 * @param[in]      len: length of password
 * @return         int 0(SUCCESS) -1(FAILURE)
*/
extern int fp_dncrypt(const char *in, char **out, unsigned int len);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __FP_CRYPT_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
