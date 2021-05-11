/**
 * *****************************************************************************
 * @file         MD5.c
 * @brief        md5 
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "MD5.h"

/* Private includes ----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define HMAC_IPAD  0x36
#define HMAC_OPAD  0x5c
#define BLOCK_SIZE 16

/* Private typedef -----------------------------------------------------------*/

typedef unsigned long MD5_u32plus;

/* Private types -------------------------------------------------------------*/

/**
 * @struct       MD5_CTX
 * @brief        MD5 context
*/
typedef struct
{
    MD5_u32plus   lo, hi;
    MD5_u32plus   a, b, c, d;
    unsigned char buffer[64];
    MD5_u32plus   block[16];
} MD5_CTX;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** 
 * @brief        This processes one or more 64-byte data blocks, but does NOT 
 *               update the bit counters. There are no alignment requirements.
 * @param        ctxBuf the ctx buffer that will be used
 * @param        data pointer to the data that will be processed
 * @param        size size_t type, that hold the size
*/
static const void *body(void *ctxBuf, const void *data, size_t size);

/** 
 * @brief        Initialized the MD5 hashing process.
 *               this function must be called before MD5Update or MD5Final
 * @param        ctxBuf the ctx buffer that will be used
*/
static void MD5Init(void *ctxBuf);

/** 
 * @brief        MD5Final finilized the Hashing process and creates the diggest.
 *               This function must be called after MD5Init and MD5Update
 * @param        result pointer that will hold the digest.
 * @param        ctxBuf the ctx buffer that will be used
 * @return       no return, the result is storesin the *result pointer
*/
static void MD5Final(unsigned char *result, void *ctxBuf);

/** 
 * @brief        MD5Update adds data in the buffers.
 *               This function can be used as many times as we want in the
 *               hashing process. Examples on hmac_md5 functions.
 * @param        ctxBuf the ctx buffer that will be used
 * @param        data the actual data that will be used in the hashing process.
 * @param        size size_t type, indicated the side of the data pointer.
*/
static void MD5Update(void *ctxBuf, const void *data, size_t size);

/* Private user code ---------------------------------------------------------*/

char *make_digest(const unsigned char *digest, size_t len) /* {{{ */
{
    char *            md5str     = (char *)malloc(sizeof(char) * (size_t)(len * 2 + 1));
    static const char hexits[17] = "0123456789abcdef";
    size_t            i;

    for (i = 0; i < len; i++)
    {
        md5str[i * 2]       = hexits[digest[i] >> 4];
        md5str[(i * 2) + 1] = hexits[digest[i] & 0x0F];
    }
    md5str[len * 2] = '\0';
    return md5str;
}

/**
 * The basic MD5 functions.
 *
 * E and G are optimized compared to their RFC 1321 definitions for
 * architectures that lack an AND-NOT instruction, just like in Colin Plumb's
 * implementation.
 * E() has been used instead of F() because F() is already defined in the Arduino core
*/
#define E(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z) ((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

/**
 * The MD5 transformation for all four rounds.
*/
#define STEP(f, a, b, c, d, x, t, s)                         \
    (a) += f((b), (c), (d)) + (x) + (t);                     \
    (a) = (((a) << (s)) | (((a)&0xffffffff) >> (32 - (s)))); \
    (a) += (b);

/**
 * SET reads 4 input bytes in little-endian byte order and stores them
 * in a properly aligned word in host byte order.
 *
 * The check for little-endian architectures that tolerate unaligned
 * memory accesses is just an optimization.  Nothing will break if it
 * doesn't work.
*/
#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
#define SET(n) (*(const MD5_u32plus *)&ptr[(n)*4])
#define GET(n) SET(n)
#else
#define SET(n)                                               \
    (ctx->block[(n)] = (MD5_u32plus)ptr[(n)*4] |             \
                       ((MD5_u32plus)ptr[(n)*4 + 1] << 8) |  \
                       ((MD5_u32plus)ptr[(n)*4 + 2] << 16) | \
                       ((MD5_u32plus)ptr[(n)*4 + 3] << 24))
#define GET(n) (ctx->block[(n)])
#endif

/**
 * This processes one or more 64-byte data blocks, but does NOT update
 * the bit counters.  There are no alignment requirements.
*/
const void *body(void *ctxBuf, const void *data, size_t size)
{
    MD5_CTX *            ctx = (MD5_CTX *)ctxBuf;
    const unsigned char *ptr;
    MD5_u32plus          a, b, c, d;
    MD5_u32plus          saved_a, saved_b, saved_c, saved_d;

    ptr = (const unsigned char *)data;

    a = ctx->a;
    b = ctx->b;
    c = ctx->c;
    d = ctx->d;

    do
    {
        saved_a = a;
        saved_b = b;
        saved_c = c;
        saved_d = d;

        /**
         *  Round 1
         * E() has been used instead of F() because F() is already defined in the Arduino core
        */
        STEP(E, a, b, c, d, SET(0), 0xd76aa478, 7)
        STEP(E, d, a, b, c, SET(1), 0xe8c7b756, 12)
        STEP(E, c, d, a, b, SET(2), 0x242070db, 17)
        STEP(E, b, c, d, a, SET(3), 0xc1bdceee, 22)
        STEP(E, a, b, c, d, SET(4), 0xf57c0faf, 7)
        STEP(E, d, a, b, c, SET(5), 0x4787c62a, 12)
        STEP(E, c, d, a, b, SET(6), 0xa8304613, 17)
        STEP(E, b, c, d, a, SET(7), 0xfd469501, 22)
        STEP(E, a, b, c, d, SET(8), 0x698098d8, 7)
        STEP(E, d, a, b, c, SET(9), 0x8b44f7af, 12)
        STEP(E, c, d, a, b, SET(10), 0xffff5bb1, 17)
        STEP(E, b, c, d, a, SET(11), 0x895cd7be, 22)
        STEP(E, a, b, c, d, SET(12), 0x6b901122, 7)
        STEP(E, d, a, b, c, SET(13), 0xfd987193, 12)
        STEP(E, c, d, a, b, SET(14), 0xa679438e, 17)
        STEP(E, b, c, d, a, SET(15), 0x49b40821, 22)

        /* Round 2 */
        STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
        STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
        STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
        STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
        STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
        STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
        STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
        STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
        STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
        STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
        STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
        STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
        STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
        STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
        STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
        STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)

        /* Round 3 */
        STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
        STEP(H, d, a, b, c, GET(8), 0x8771f681, 11)
        STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
        STEP(H, b, c, d, a, GET(14), 0xfde5380c, 23)
        STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
        STEP(H, d, a, b, c, GET(4), 0x4bdecfa9, 11)
        STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
        STEP(H, b, c, d, a, GET(10), 0xbebfbc70, 23)
        STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
        STEP(H, d, a, b, c, GET(0), 0xeaa127fa, 11)
        STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
        STEP(H, b, c, d, a, GET(6), 0x04881d05, 23)
        STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
        STEP(H, d, a, b, c, GET(12), 0xe6db99e5, 11)
        STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
        STEP(H, b, c, d, a, GET(2), 0xc4ac5665, 23)

        /* Round 4 */
        STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
        STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
        STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
        STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
        STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
        STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
        STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
        STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
        STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
        STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
        STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
        STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
        STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
        STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
        STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
        STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

        a += saved_a;
        b += saved_b;
        c += saved_c;
        d += saved_d;

        ptr += 64;
    } while (size -= 64);

    ctx->a = a;
    ctx->b = b;
    ctx->c = c;
    ctx->d = d;

    return ptr;
}

void MD5Init(void *ctxBuf)
{
    MD5_CTX *ctx = (MD5_CTX *)ctxBuf;
    ctx->a       = 0x67452301;
    ctx->b       = 0xefcdab89;
    ctx->c       = 0x98badcfe;
    ctx->d       = 0x10325476;

    ctx->lo = 0;
    ctx->hi = 0;
}

void MD5Update(void *ctxBuf, const void *data, size_t size)
{
    MD5_CTX *   ctx = (MD5_CTX *)ctxBuf;
    MD5_u32plus saved_lo;
    MD5_u32plus used, free;

    saved_lo = ctx->lo;
    if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
    {
        ctx->hi++;
    }
    ctx->hi += (MD5_u32plus)size >> 29;

    used = saved_lo & 0x3f;

    if (used)
    {
        free = 64 - used;

        if (size < free)
        {
            memcpy(&ctx->buffer[used], data, size);

            return;
        }

        memcpy(&ctx->buffer[used], data, free);
        data = (const unsigned char *)data + free;
        size -= free;
        body(ctx, ctx->buffer, 64);
    }

    if (size >= 64)
    {
        data = body(ctx, data, size & ~(size_t)0x3f);
        size &= 0x3f;
    }

    memcpy(ctx->buffer, data, size);
}

void MD5Final(unsigned char *result, void *ctxBuf)
{
    MD5_CTX *   ctx = (MD5_CTX *)ctxBuf;
    MD5_u32plus used, free;

    used = ctx->lo & 0x3f;

    ctx->buffer[used++] = 0x80;

    free = 64 - used;

    if (free < 8)
    {
        memset(&ctx->buffer[used], 0, free);
        body(ctx, ctx->buffer, 64);
        used = 0;
        free = 64;
    }

    memset(&ctx->buffer[used], 0, free - 8);

    ctx->lo <<= 3;
    ctx->buffer[56] = (unsigned char)(ctx->lo);
    ctx->buffer[57] = (unsigned char)(ctx->lo >> 8);
    ctx->buffer[58] = (unsigned char)(ctx->lo >> 16);
    ctx->buffer[59] = (unsigned char)(ctx->lo >> 24);
    ctx->buffer[60] = (unsigned char)(ctx->hi);
    ctx->buffer[61] = (unsigned char)(ctx->hi >> 8);
    ctx->buffer[62] = (unsigned char)(ctx->hi >> 16);
    ctx->buffer[63] = (unsigned char)(ctx->hi >> 24);

    body(ctx, ctx->buffer, 64);

    result[0]  = (unsigned char)(ctx->a);
    result[1]  = (unsigned char)(ctx->a >> 8);
    result[2]  = (unsigned char)(ctx->a >> 16);
    result[3]  = (unsigned char)(ctx->a >> 24);
    result[4]  = (unsigned char)(ctx->b);
    result[5]  = (unsigned char)(ctx->b >> 8);
    result[6]  = (unsigned char)(ctx->b >> 16);
    result[7]  = (unsigned char)(ctx->b >> 24);
    result[8]  = (unsigned char)(ctx->c);
    result[9]  = (unsigned char)(ctx->c >> 8);
    result[10] = (unsigned char)(ctx->c >> 16);
    result[11] = (unsigned char)(ctx->c >> 24);
    result[12] = (unsigned char)(ctx->d);
    result[13] = (unsigned char)(ctx->d >> 8);
    result[14] = (unsigned char)(ctx->d >> 16);
    result[15] = (unsigned char)(ctx->d >> 24);

    memset(ctx, 0, sizeof(*ctx));
}

unsigned char *make_hash(const void *arg)
{
    MD5_CTX        context;
    unsigned char *hash = (unsigned char *)malloc(BLOCK_SIZE);
    MD5Init(&context);
    MD5Update(&context, arg, strlen((const char *)arg));
    MD5Final(hash, &context);

    return hash;
}

char *md5(const void *arg)
{
    return make_digest(make_hash(arg), BLOCK_SIZE);
}

#if 0

void hmac_md5(const void *text, size_t text_len,const void *key, size_t key_len, unsigned char *digest)
{
    MD5_CTX context;
    unsigned char k_ipad[65];
    unsigned char k_opad[65];
    unsigned char tk[BLOCK_SIZE];
    int i;

    if (key_len > 64)
    {
        MD5_CTX tctx;
        MD5Init(&tctx);
        MD5Update(&tctx, key, key_len);
        MD5Final(tk, &tctx);

        key = tk;
        key_len = 16;
    }

    memset(k_ipad, 0, sizeof(k_ipad));
    memset(k_opad, 0, sizeof(k_opad));
    memcpy(k_ipad, key, key_len);
    memcpy(k_opad, key, key_len);

    for (i = 0; i < 64; i++)
    {
        k_ipad[i] ^= HMAC_IPAD;
        k_opad[i] ^= HMAC_OPAD;
    }

    /* inner */
    MD5Init(&context);
    MD5Update(&context, k_ipad, 64);
    MD5Update(&context, text, text_len);
    MD5Final(digest, &context);

    /* outer */
    MD5Init(&context);
    MD5Update(&context, k_opad, 64);
    MD5Update(&context, digest, 16);
    MD5Final(digest, &context);
}

#else

char *hmac_md5(const void *text, size_t text_len, const void *key, size_t key_len)
{
    unsigned char digest[17];
    digest[16] = 0x00;
    MD5_CTX       context;
    unsigned char k_ipad[65];
    unsigned char k_opad[65];
    unsigned char tk[BLOCK_SIZE];
    int           i;

    if (key_len > 64)
    {
        MD5_CTX tctx;
        MD5Init(&tctx);
        MD5Update(&tctx, key, key_len);
        MD5Final(tk, &tctx);

        key     = tk;
        key_len = 16;
    }

    memset(k_ipad, 0, sizeof(k_ipad));
    memset(k_opad, 0, sizeof(k_opad));
    memcpy(k_ipad, key, key_len);
    memcpy(k_opad, key, key_len);

    for (i = 0; i < 64; i++)
    {
        k_ipad[i] ^= HMAC_IPAD;
        k_opad[i] ^= HMAC_OPAD;
    }

    /* inner */
    MD5Init(&context);
    MD5Update(&context, k_ipad, 64);
    MD5Update(&context, text, text_len);
    MD5Final(digest, &context);

    /* outer */
    MD5Init(&context);
    MD5Update(&context, k_opad, 64);
    MD5Update(&context, digest, 16);
    MD5Final(digest, &context);

    return make_digest(digest, BLOCK_SIZE);
}
#endif

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
