/**
 * *****************************************************************************
 * @file         MD5.c/h
 * @brief        md5
 * @author       tqfx
 * @date         20210101
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD5_h__
#define __MD5_h__

/* Private includes ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief          Created the MD5 hash from a string of characters on hex
 *                 encoding. Gets an pointer to a string, and hash it to MD5.
 * @param[in]      arg: pointer to the string or array of characters.
 * @return         a pointer containing the MD5digest
*/
extern unsigned char *make_hash(const void *arg);

/**
 * @brief          Converts a digest to a string. In order for tedigest to be
 *                 readable and printed easyly, we need to conver it.
 * @param[in]      digest: pointer to the array that holds the digest
 * @param[in]      len: integer defining the lengs of the output, usually 16 for MD5
 * @return         poiner to the string that holds the String of the converted digest
*/
extern char *make_digest(const unsigned char *digest, size_t len);

/**
 * @brief          Automation function. Gets a pointer to sequence of chars, Then
 *                 Hashes it, and converts it to a readable form
 * @param[in]      arg: pointer to the string that will be hashed.
 * @return         pointer to the string that holds the string of the converted digest.
*/
extern char *md5(const void *arg);

#if 0
/**
 * @brief          Main function of the HMAC-MD5. gets the key and the text, and
 *                 creates the HMAC-MD5 digest function. in order to be pronted,
 *                 it is required for the make_digest function to be called.
 * @code           make_digest(digest,BLOCK_SIZE); @endcode
 * @param[in]      text: pointer to the text that will be hashed.
 * @param[in]      text_len: integet value of the length of the text.
 * @param[in]      key: pointer to the key that will be used in the HMAC process.
 * @param[in]      key_len: integer value of the key length.
 * @param[in]      digest: pointer to the array that will hold the digest of this process
 * @return         the digest in the memory block that the *digest is pointing.
*/
extern void hmac_md5(const void *   text,
                     size_t         text_len,
                     const void *   key,
                     size_t         key_len,
                     unsigned char *digest)
#else
/**
 * @brief          Main function of the HMAC-MD5. gets the key and the text, and
 *                 creates the HMAC-MD5 digest function in a readable format.
 * @param[in]      text: pointer to the text that will be hashed.
 * @param[in]      text_len: integet value of the length of the text.
 * @param[in]      key: pointer to the key that will be used in the HMAC process.
 * @param[in]      key_len: integer value of the key length.
 * @return         pointer that points to the digest in a readable format.
*/
extern char *hmac_md5(const void *text,
                      size_t      text_len,
                      const void *key,
                      size_t      key_len);
#endif

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __MD5_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
