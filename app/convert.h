/**
 * *****************************************************************************
 * @file         convert.c/h
 * @brief        code conversion 
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONVERT_H__
#define __CONVERT_H__

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

/* Exported types ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @name           code_convert
 * @brief          source charset transcoding destination charset
 * @note           Note the support for C language localization
 * @param[out]     dst: pointer of buffer variable
 * @param[in]      dst_charset: charset of destination string
 * @param[in]      src: source string
 * @param[in]      src_charset: charset of source string
 * @return         int 0(success) -1(failure)
*/
#ifdef __WINNT__
extern int code_convert(char **      dst,
                        unsigned int dst_charset,
                        const char * src,
                        unsigned int src_charset);
#else
extern int code_convert(char **     dst,
                        const char *dst_charset,
                        const char *src,
                        const char *src_charset);
#endif /* __WINNT__ */

/**
 * @brief          utf-8 transcoding gbk
 * @note           Note windows api
 * @param[out]     dst: pointer of buffer variable
 * @param[in]      src: source string
 * @return         int 0(success) -1(failure)
*/
extern int utf8_gbk(char **dst, const char *src);

/**
 * @brief          gbk transcoding utf-8
 * @note           Note windows api
 * @param[out]     dst: pointer of buffer variable
 * @param[in]      src: source string
 * @return         int 0(success) -1(failure)
*/
extern int gbk_utf8(char **dst, const char *src);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __CONVERT_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
