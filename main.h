/**
 * *****************************************************************************
 * @file         main.c/h
 * @brief        main
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (c) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Private includes ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/* Exported constants --------------------------------------------------------*/

#define HELP \
    "\tCopyright (C) 2021 tqfx\n\
option:\n\
-i --id \tget password by id\n\
-a --add \tadd key or password\n\
-d --del \tdelete key or password\n\
-s --show \tshow key or password\n\
parameter:\n\
-k --key \tthe key\n\
-p --password \tthe password\n\
-l --length \tthe length {1, 32}\n\
-t --type \tthe type {0 email, 1 pay, 2 new}\n\
-n --new \tthe new table\n\
-f --filename \tfilename of data\n\
   --import \tfilename of data"

#define MAIN_ARG_STR "fpkltn"

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

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

extern char *oc_strcpy(const char *str);
extern char *oc_strncpy(const char *str, size_t max);

extern void main_str_cb(const char *args);
extern void main_char_cb(char ch);
extern void main_arg_cb(const char *argp, const char *args);

extern int main_cb(int argc, char **argv);

__END_DECLS

/* Terminate definition to prevent recursive inclusion -----------------------*/
#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
