/* bits.h -- definitions for functions on module bits.c
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Tue Aug  9 09:38:41 EEST 2016
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD
 */
#ifndef _BITS_H
#define _BITS_H

#include <sys/types.h>
#include "crc.h"

size_t msbpos(CRC_STATE state);

CRC_STATE msbmask(CRC_STATE state);

char *pol2str(CRC_STATE pol, char *buffer, size_t bufsz);

CRC_STATE slow_do_crc(int n, CRC_STATE v, CRC_STATE p);

#endif /* _BITS_H */
