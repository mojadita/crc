/* $Id: crc.c,v 2.1 2005/11/05 17:51:35 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Thu Nov  3 16:18:12 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD
 */

#define IN_CRC_C

#include <sys/types.h>
#include "crc.h"

/* table based CRC calculation */
CRC_STATE do_crc(
    CRC_STATE  state,
    CRC_BYTE  *buff,
    size_t     nbytes,
    CRC_TABLE  table)
{
    CRC_STATE index;

    while (nbytes--) {
        state ^= *buff++;
        index = state & CRC_BYTE_MASK;
        state >>= CRC_BYTE_SIZE;
        state ^= table->cr_table[index];
    } /* while */

    return state;
} /* do_crc */

CRC_STATE add_crc(
    CRC_STATE  state,
    CRC_BYTE  *buff,
    size_t     nbytes,
    CRC_TABLE  table)
{
    int i;
    CRC_STATE work = state;

    if(nbytes > table->cr_bytesize)
        nbytes = table->cr_bytesize;
    work &= table->cr_mask;
    for (i = 0; i < nbytes; i++) {
        *buff++ ^= work & CRC_BYTE_MASK;
        work >>= CRC_BYTE_SIZE;
    } /* for */
    return state;
} /* add_crc */
