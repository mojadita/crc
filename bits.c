/* bits.c -- routines to obtain a mask and the MSB of a CRC_STATE.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Nov  3 16:18:12 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bits.h"

#define SIZE (sizeof(CRC_STATE)*8)

size_t msbpos(CRC_STATE s)
{
    int a = 0, b = 1;
    if (!s) return 0;
    while (b < SIZE-1 && (s >> b))
        b = (b << 1) + 1;
    if (s >> b) return SIZE;
    /* (s >> a != 0) && (s >> b == 0) */
    while (b - a > 1) {
        int c = (a + b) >> 1;
        if (s >> c) a = c;
        else b = c;
    }
    /* (s >> a != 0) && (s >> b == 0) && (b - a == 1) */
    return b;
} /* bits1 */

CRC_STATE msbmask(CRC_STATE s)
{
    size_t b = msbpos(s);
    switch (b) {
    case 0: return 0;
    case SIZE: return ~0LL;
    default: return (1LL << b) - 1LL;
    }
}

char *pol2str(CRC_STATE p, char *buffer, size_t left)
{
    char *res = buffer;
    int l;
    int n = msbpos(p); /* polinomial grade */
    CRC_STATE m;

#define ACT() do { buffer += l; left -= l; } while (0)

    l = snprintf(buffer, left, "x^%d", n--); ACT();
    for (m = p; m; m >>= 1) {
        if (m & 1) {
            if (n > 1) {
                l = snprintf(buffer, left,
                    "+x^%d", n); ACT();
            } else {
                l = snprintf(buffer, left,
                    "+%s",
                    n ? "x"
                      : "1"); ACT();
            }
        }
        n--;
    } /* for */

#undef ACT
    return res;
} /* pol2str */

CRC_STATE slow_do_crc(int n, CRC_STATE v, CRC_STATE p)
{
    while (n--) v = (v >> 1) ^ (v & 1 ? p : 0);
    return v;
} /* slow_do_crc */
