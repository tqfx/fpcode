/**
 * *****************************************************************************
 * @file         clipboard.c/h
 * @brief        clipboard
 * @author       tqfx
 * @date         20210515
 * @version      1
 * @copyright    Copyright (C) 2021 tqfx
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "clipboard.h"

/* Private includes ----------------------------------------------------------*/

#include <stdlib.h>
#ifdef __WINNT__
#include <windows.h>
#endif /* __WINNT__ */

/* Private user code ---------------------------------------------------------*/

#ifdef __WINNT__

int clipboard_set(const char *str)
{
    /**
     * OpenClipboard 打开剪切板：指定关联到打开的剪切板的窗口句柄，传入NULL表示关联到当前任务。
     * 每次只允许一个进程打开并访问。每打开一次就要关闭，否则其他进程无法访问剪切板。
     * EmptyClipboard 清空剪切板：写入前必须先清空，得到占有权
    */
    if (OpenClipboard(NULL) && EmptyClipboard())
    {
        /* 根据环境变量获取数据长度 */
        size_t n = (strlen(str) + 1U) * sizeof(char);

        /**
         * @brief 在堆上动态分配以字节为单位的全局内存区域。
         * @return 成功则指向该内存，失败NULL。1.分配内存属性 2.大小
        */
        HGLOBAL hmem = GlobalAlloc(GMEM_MOVEABLE, n);
        if (hmem == NULL)
        {
            /* 关闭剪切板,释放剪切板所有权，关闭后就不能写入数据 */
            return CloseClipboard();
        }

        /**
         * 锁定由GlobalAlloc分配的内存，并将内存对象的锁定计数器+1；
         * 成功返回指向内存对象起始地址的指针。失败NULL
        */
        LPTSTR lpdest = (LPTSTR)GlobalLock(hmem);

        /**
         * 系统为每个全局内存对象维护一个锁定计数器，初始为0，GlobalLock使计数器+1，
        */

        /** 拷贝数据到剪贴板内存。 */
        memcpy(lpdest, str, n);

        /** 解除内存锁定，将属性为GMEM_MOVEABLE的内存对象计数器-1. */
        (void)GlobalUnlock(hmem);

        UINT format = (sizeof(TCHAR) == sizeof(WCHAR))
                          ? CF_UNICODETEXT
                          : CF_TEXT;

        /** 设置数据到剪贴板。执行成功，返回数据句柄，否则返回NULL */
        (void)SetClipboardData(format, hmem);

        return CloseClipboard();
    }

    return 0;
}

int clipboard_get(char **dst)
{
    int ret = -1;

    if (OpenClipboard(NULL))
    {
        UINT format = (sizeof(TCHAR) == sizeof(WCHAR))
                          ? CF_UNICODETEXT
                          : CF_TEXT;

        HGLOBAL hmem = GetClipboardData(format);
        if (hmem != NULL)
        {
            size_t n = strlen((char *)hmem) + 1U;

            *dst = (char *)malloc(n * sizeof(char));
            memcpy(*dst, hmem, n);

            ret = 0;
        }

        (void)CloseClipboard();
    }

    return ret;
}

#endif /* __WINNT__ */

/************************ (C) COPYRIGHT TQFX *******************END OF FILE****/
