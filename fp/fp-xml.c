/*!
 @file           fp-xml.c
 @brief          xml of fp
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-29
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 \n \n
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 \n \n
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "fp-xml.h"

#include "file-xml.h"
#include "fp-crypt.h"
#include "fp.h"

int fp_xml_fp2xml(const fp_t *fp,
                  mxml_node_t **xml)
{
#ifdef DEBUG
    if (!fp || !xml)
    {
        return -1;
    }
#endif /* DEBUG */
    *xml = mxmlNewElement(*xml, const_str_k);
    mxmlElementSetAttr(*xml, const_str_i, fp->key);

    mxml_node_t *k_l = mxmlNewElement(*xml, const_str_l);
    (void)mxmlNewTextf(k_l, 0, "%u", fp->len);

    mxml_node_t *k_t = mxmlNewElement(*xml, const_str_t);
    (void)mxmlNewTextf(k_t, 0, "%u", fp->type);

    if (fp->type == FPTYPE_NEW)
    {
        (void)mxmlNewCDATA(*xml, fp->new);
    }

    return 0;
}

int fp_xml_xml2fp(mxml_node_t *xml,
                  fp_t **fp)
{
#ifdef DEBUG
    if (!xml || !fp)
    {
        return -1;
    }
#endif /* DEBUG */
    *fp = (fp_t *)calloc(1, sizeof(fp_t));
    if (!*fp)
    {
        return -1;
    }

    int ret = -1;

    do
    {
        mxml_node_t *k_l = mxmlFindElement(xml,
                                           xml,
                                           const_str_l,
                                           NULL,
                                           NULL,
                                           MXML_DESCEND);

        const char *s = mxmlGetText(k_l, 0);
        if (!s)
        {
            break;
        }
        sscanf(s, "%u", &((*fp)->len));

        mxml_node_t *k_t = mxmlFindElement(xml,
                                           xml,
                                           const_str_t,
                                           NULL,
                                           NULL,
                                           MXML_DESCEND);

        s = mxmlGetText(k_t, 0);
        if (!s)
        {
            break;
        }
        sscanf(s, "%u", &((*fp)->type));

        s = mxmlElementGetAttr(xml, const_str_i);
        if (!s)
        {
            break;
        }
        (*fp)->key = (char *)malloc(strlen(s) + 1U);
        if (!((*fp)->key))
        {
            break;
        }
        (void)strcpy((*fp)->key, s);

        if ((*fp)->type == FPTYPE_NEW)
        {
            mxml_node_t *new = mxmlGetLastChild(xml);

            s = mxmlGetCDATA(new);
            if (!s)
            {
                break;
            }
            (*fp)->new = (char *)malloc(strlen(s) + 1U);
            if (!((*fp)->new))
            {
                break;
            }
            (void)strcpy((*fp)->new, s);
        }

        ret = 0;
    } while (0);

    if (ret)
    {
        fp_free(fp);
    }

    return ret;
}

int fp_xml_init(const char *filename)
{
#ifdef DEBUG
    if (!filename)
    {
        return -1;
    }
#endif /* DEBUG */
    int ret = 0;

    mxml_node_t *xml = mxmlNewXML(NULL);

    mxml_node_t *passwd = mxmlNewElement(xml, const_str_p);
    mxmlElementSetAttrf(passwd, const_str_n, "%i", 0);

    mxml_node_t *key = mxmlNewElement(xml, const_str_k);
    mxmlElementSetAttrf(key, const_str_n, "%i", 0);

    ret = mxml_w(filename, xml);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_add_k(const char *filename,
                 const fp_t *fp)
{
#ifdef DEBUG
    if (!filename || !fp)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *k = mxmlFindElement(xml,
                                         xml,
                                         const_str_k,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!k)
        {
            break;
        }

        unsigned int n = 0U;
        sscanf(mxmlElementGetAttr(k, const_str_n), "%u", &n);

        mxml_node_t *k_k = mxmlFindElement(k,
                                           k,
                                           const_str_k,
                                           const_str_i,
                                           fp->key,
                                           MXML_DESCEND);
        if (k_k)
        {
            mxml_node_t *k_l = mxmlFindElement(k_k,
                                               k_k,
                                               const_str_l,
                                               NULL,
                                               NULL,
                                               MXML_DESCEND);

            ret = mxmlSetTextf(k_l, 0, "%u", fp->len);
            if (ret)
            {
                break;
            }

            mxml_node_t *k_t = mxmlFindElement(k_k,
                                               k_k,
                                               const_str_t,
                                               NULL,
                                               NULL,
                                               MXML_DESCEND);

            ret = mxmlSetTextf(k_t, 0, "%u", fp->type);
            if (ret)
            {
                break;
            }

            mxml_node_t *k_n = mxmlGetLastChild(k_k);
            if (fp->type == FPTYPE_NEW)
            {
                if (mxmlSetCDATA(k_n, fp->new))
                {
                    (void)mxmlNewCDATA(k_k, fp->new);
                }
            }
            else if (mxmlGetCDATA(k_n))
            {
                mxmlDelete(k_n);
            }
        }
        else
        {
            k_k = mxmlGetLastChild(k);
            while (k_k)
            {
                const char *key = mxmlElementGetAttr(k_k, const_str_i);
                if (key && strcmp(key, fp->key) > 0) /* key > fp->key */
                {
                    k_k = mxmlWalkPrev(k_k, k, MXML_NO_DESCEND);
                }
                else
                {
                    break;
                }
            }

            mxml_node_t *k_tmp = NULL;
            if (fp_xml_fp2xml(fp, &k_tmp))
            {
                break;
            }

            if (k_k)
            {
                mxmlAdd(k, MXML_ADD_AFTER, k_k, k_tmp);
            }
            else
            {
                mxmlAdd(k, MXML_ADD_BEFORE, k_k, k_tmp);
            }

            mxmlElementSetAttrf(k, const_str_n, "%u", n + 1U);
        }

        ret = mxml_w(filename, xml);
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_del_k(const char *filename,
                 const char *key)
{
#ifdef DEBUG
    if (!filename || !key)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *k = mxmlFindElement(xml,
                                         xml,
                                         const_str_k,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!k)
        {
            break;
        }

        unsigned int n = 0U;
        sscanf(mxmlElementGetAttr(k, const_str_n), "%u", &n);

        mxml_node_t *k_k = mxmlFindElement(k,
                                           k,
                                           const_str_k,
                                           const_str_i,
                                           key,
                                           MXML_DESCEND);
        if (k_k)
        {
            mxmlDelete(k_k);
            mxmlElementSetAttrf(k, const_str_n, "%u", n - 1U);
            ret = mxml_w(filename, xml);
        }
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_add_p(const char *filename,
                 const char *password)
{
#ifdef DEBUG
    if (!filename || !password)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *p = mxmlFindElement(xml,
                                         xml,
                                         const_str_p,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!p)
        {
            break;
        }

        unsigned int n = 1U;

        char *out = NULL;

        mxml_node_t *p_p = mxmlGetFirstChild(p);
        while (p_p)
        {
            mxml_node_t *tmp = mxmlGetFirstChild(p_p);

            const char *in = mxmlGetCDATA(tmp);
            if (!in || fp_dncrypt(in, &out, LEN_PASSWORD))
            {
                break;
            }
            if (strcmp(out, password))
            {
                mxmlElementSetAttrf(p_p, const_str_i, "%u", n++);
            }
            else
            {
                tmp = mxmlWalkPrev(p_p, p, MXML_NO_DESCEND);
                mxmlDelete(p_p);
                p_p = tmp;
            }
            PFREE(free, out);

            p_p = mxmlWalkNext(p_p, p, MXML_NO_DESCEND);
        }

        p_p = mxmlNewElement(NULL, const_str_p);
        mxmlElementSetAttrf(p_p, const_str_i, "%i", 0);

        if (fp_encrypt(password, &out, LEN_PASSWORD))
        {
            break;
        }
        (void)mxmlNewCDATA(p_p, out);
        PFREE(free, out);

        mxmlAdd(p, MXML_ADD_BEFORE, NULL, p_p);

        mxmlElementSetAttrf(p, const_str_n, "%u", n);

        ret = mxml_w(filename, xml);
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_del_p(const char *filename,
                 const char *password)
{
#ifdef DEBUG
    if (!filename || !password)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *p = mxmlFindElement(xml,
                                         xml,
                                         const_str_p,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!p)
        {
            break;
        }

        unsigned int n = 0U;

        char *out = NULL;

        mxml_node_t *p_p = mxmlGetFirstChild(p);
        while (p_p)
        {
            mxml_node_t *tmp = mxmlGetFirstChild(p_p);

            const char *in = mxmlGetCDATA(tmp);
            if (!in || fp_dncrypt(in, &out, LEN_PASSWORD))
            {
                break;
            }
            if (strcmp(out, password))
            {
                mxmlElementSetAttrf(p_p, const_str_i, "%u", n++);
            }
            else
            {
                tmp = mxmlWalkPrev(p_p, p, MXML_NO_DESCEND);
                mxmlDelete(p_p);
                if (tmp)
                {
                    p_p = tmp;
                }
                else
                {
                    p_p = mxmlGetFirstChild(p);
                }
            }
            PFREE(free, out);

            if (tmp)
            {
                p_p = mxmlWalkNext(p_p, p, MXML_NO_DESCEND);
            }
        }

        unsigned int i = 0U;
        sscanf(mxmlElementGetAttr(p, const_str_n), "%u", &i);
        if (i != n)
        {
            mxmlElementSetAttrf(p, const_str_n, "%u", n);

            ret = mxml_w(filename, xml);
        }
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_del_i(const char *filename,
                 const char *string,
                 unsigned int i)
{
#ifdef DEBUG
    if (!filename || !string)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *e = mxmlFindElement(xml,
                                         xml,
                                         string,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!e)
        {
            break;
        }

        int flag = 0;
        if (!strcmp(string, const_str_p))
        {
            flag = !flag;
        }

        unsigned int n = 0;

        mxml_node_t *e_e = mxmlGetFirstChild(e);
        while (e_e)
        {
            mxml_node_t *tmp = e_e;
            if (i == n)
            {
                tmp = mxmlWalkPrev(e_e, e, MXML_NO_DESCEND);
                mxmlDelete(e_e);
                if (tmp)
                {
                    e_e = tmp;
                }
                else
                {
                    e_e = mxmlGetFirstChild(e);
                }
                i = --n;
            }
            else if (flag)
            {
                mxmlElementSetAttrf(e_e, const_str_i, "%u", n);
            }
            if (tmp)
            {
                e_e = mxmlWalkNext(e_e, e, MXML_NO_DESCEND);
            }
            n++;
        }

        sscanf(mxmlElementGetAttr(e, const_str_n), "%u", &i);
        if (i != n)
        {
            mxmlElementSetAttrf(e, const_str_n, "%u", n);

            ret = mxml_w(filename, xml);
        }
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_out_p(const char *filename,
                 char ***dst,
                 size_t *n)
{
#ifdef DEBUG
    if (!filename || !dst || !n)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *p = mxmlFindElement(xml,
                                         xml,
                                         const_str_p,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!p)
        {
            break;
        }

        sscanf(mxmlElementGetAttr(p, const_str_n), "%zu", n);
        if (*n)
        {
            *dst = (char **)malloc(sizeof(char *) * (*n));
            if (!*dst)
            {
                break;
            }
        }

        size_t i = 0U;

        mxml_node_t *p_p = mxmlGetFirstChild(p);
        while (p_p)
        {
            mxml_node_t *tmp = mxmlGetFirstChild(p_p);

            const char *in = mxmlGetCDATA(tmp);

            char *out = NULL;
            if (!in || fp_dncrypt(in, &out, LEN_PASSWORD))
            {
                break;
            }
            (*dst)[i++] = out;

            p_p = mxmlWalkNext(p_p, p, MXML_NO_DESCEND);
        }

        ret = 0;
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

int fp_xml_out_k(const char *filename,
                 fp_t ***dst,
                 size_t *n)
{
#ifdef DEBUG
    if (!filename || !dst || !n)
    {
        return -1;
    }
#endif /* DEBUG */
    mxml_node_t *xml = NULL;

    int ret = mxml_r(filename, &xml);
    if (ret)
    {
        return ret;
    }
    ret = -1;

    do
    {
        mxml_node_t *k = mxmlFindElement(xml,
                                         xml,
                                         const_str_k,
                                         const_str_n,
                                         NULL,
                                         MXML_DESCEND);
        if (!k)
        {
            break;
        }

        sscanf(mxmlElementGetAttr(k, const_str_n), "%zu", n);
        if (*n)
        {
            *dst = (fp_t **)malloc(sizeof(fp_t *) * (*n));
            if (!*dst)
            {
                break;
            }
        }

        size_t i = 0U;

        mxml_node_t *k_k = mxmlGetFirstChild(k);
        while (k_k)
        {
            fp_t *fp = NULL;
            if (fp_xml_xml2fp(k_k, &fp))
            {
                break;
            }
            (*dst)[i++] = fp;

            k_k = mxmlWalkNext(k_k, k, MXML_NO_DESCEND);
        }

        ret = 0;
    } while (0);

    PFREE(mxmlDelete, xml);

    return ret;
}

/* END OF FILE */
