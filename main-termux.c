
#include "app-termux.h"
#include "file.h"
#include "fp.h"
#include "kstring.h"
#include "tapi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *oc_strcpy(const char *str)
{
    char *dst = (char *)malloc(sizeof(char) * (strlen(str) + 1U));
    (void)strcpy(dst, str);
    return dst;
}

void menu_search(const char *filename)
{
    int index = 0;
    while (tapi_sheet(NULL, &index, "目录", "搜索标识,搜索密码") > -1)
    {
        switch (index)
        {
        case 0:
        {
            app_termux_search_key(filename);
            break;
        }

        case 1:
        {
            app_termux_search_password(filename);
            break;
        }

        default:
            break;
        }
    }
    return;
}

void menu_edit(const char *filename)
{
    int index = 0;
    while (tapi_sheet(NULL, &index, "目录", "添加标识,添加密码,删除标识,删除密码") > -1)
    {
        switch (index)
        {
        case 0:
        {
            app_termux_add_key(filename);
            break;
        }

        case 1:
        {
            app_termux_add_password(filename);
            break;
        }

        case 2:
        {
            app_termux_del_key(filename);
            break;
        }

        case 3:
        {
            app_termux_del_password(filename);
            break;
        }

        default:
            break;
        }
    }
    return;
}

void menu(const char *filename)
{
    int index = 0;
    while (tapi_sheet(NULL, &index, "目录", "查找,生成,搜索,编辑") > -1)
    {
        switch (index)
        {
        case 0:
        {
            app_termux_show_key(filename);
            break;
        }

        case 1:
        {
            app_termux_create(filename);
            break;
        }

        case 2:
        {
            menu_search(filename);
            break;
        }

        case 3:
        {
            menu_edit(filename);
            break;
        }

        default:
            break;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    if (tapi_auth_finger())
    {
        return EXIT_FAILURE;
    }

    char *filename = NULL;
    if (argc > 1)
    {
        filename = oc_strcpy(argv[argc - 1]);
    }
    else
    {
        char *s = getenv("_");
        if (!s)
        {
            s = argv[!argc];
        }

        kstring_t *ks = ks_init();
        ksprintf(ks, "%s%s", s, ".xml");
        filename = ks_release(ks);
        PFREE(ks_free, ks);
    }

    if (!file_exist(filename))
    {
        (void)fp_init(filename);
    }

    menu(filename);

    PFREE(free, filename);

    return EXIT_SUCCESS;
}
