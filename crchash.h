/* $Id: crchash.h,v 2.4 2005/11/08 12:41:48 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Sat Nov  5 20:15:26 CET 2005
 *
 * Disclaimer:
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Do not include anything BEFORE the line below, as it would not be
 * protected against double inclusion from other files
 */
#ifndef CRCHASH_H
#define CRCHASH_H

#include "crc.h"

static char CRCHASH_H_RCSId[] = "\n$Id: crchash.h,v 2.4 2005/11/08 12:41:48 luis Exp $\n";

/* constants */

/* types */

/* prototypes */
CRC_STATE crchash(char *s);
CRC_STATE crchashb(unsigned char *s, size_t n);

#endif /* CRCHASH_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */

/* $Id: crchash.h,v 2.4 2005/11/08 12:41:48 luis Exp $ */