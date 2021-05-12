/* $Id: crchash.h,v 2.4 2005/11/08 12:41:48 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Nov  5 20:15:26 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef CRCHASH_H
#define CRCHASH_H

#include "crc.h"

CRC_STATE crchash(char *s);
CRC_STATE crchashb(unsigned char *s, size_t n);

#endif /* CRCHASH_H */
