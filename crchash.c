/* $Id: crchash.c,v 2.4 2005/11/08 12:41:48 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Nov  5 20:10:47 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <string.h>
#include "crc.h"
#include "crc_alltables.h"
#include "crchash.h"

CRC_STATE crchash(char *s)
{
    int l = strlen(s);

    return do_crc(
            0xffffffffffffffff,
            (CRC_BYTE *) s,
            l,
            crc64ecma182)
        ^ 0xffffffffffffffff;
} /* crchash */

CRC_STATE crchashb(unsigned char *s, size_t n)
{
    return do_crc(
            0xffffffffffffffff,
            (CRC_BYTE *) s,
            n,
            crc64ecma182)
        ^ 0xffffffffffffffff;
} /* crchashb */
