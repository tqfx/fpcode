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

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private includes ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private user code ---------------------------------------------------------*/

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        puts(HELP); /* printf help information */
        exit(EXIT_SUCCESS);
    }

    for (int i = 1U; i != argc; ++i)
    {
        char *argp = NULL;
        char *args = NULL;

        if (argv[i][0] != '-')
        {
            (void)printf("invalid  main  %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }

        if (strstr(argv[i], "=")) /* -option=str */
        {
            size_t j = (size_t)(strchr(argv[i], '=') - argv[i]);

            argp = oc_strncpy(argv[i], j++);
            args = oc_strcpy(argv[i] + j);
        }
        else if (strlen(argv[i]) > 2U &&
                 strchr(MAIN_ARG_STR, argv[i][1])) /* -pstr */
        {
            argp = oc_strncpy(argv[i], 2U);
            args = oc_strcpy(argv[i] + 2U);
        }
        else /* -p str | --option str | -pp */
        {
            argp = oc_strcpy(argv[i]);

            if ((strstr(argv[i], "--") ||
                 strlen(argv[i]) == 2U) &&
                i + 1 < argc &&
                argv[i + 1][0] != '-') /* --option str | -p str */
            {
                args = oc_strcpy(argv[++i]);
            }
            else if (strstr(argp, "--")) /* --option */
            {
                main_str_cb(argp);

                free(argp);
                argp = NULL;
                continue;
            }
            else /* -pp */
            {
                for (size_t j = strlen(argp) - 1U; j; --j)
                {
                    main_char_cb(argp[j]);
                    argp[j] = '\0';
                }

                free(argp);
                argp = NULL;
                continue;
            }
        }

        main_arg_cb(argp, args);

        free(argp);
        argp = NULL;
        free(args);
        args = NULL;
    }

    return main_cb(argc, argv);
}

char *oc_strcpy(const char *str)
{
    char *dst = (char *)malloc(sizeof(char) * (strlen(str) + 1U));
    (void)strcpy(dst, str);
    return dst;
}

char *oc_strncpy(const char *str, size_t max)
{
#ifdef __USE_GNU
    max = strnlen(str, max);
#endif
    char *dst = (char *)malloc(sizeof(char) * (max + 1U));
    memcpy(dst, str, max);
    dst[max] = '\0';
    return dst;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
