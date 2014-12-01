/* $Id: crchash.c,v 2.4 2005/11/08 12:41:48 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Sat Nov  5 20:10:47 CET 2005
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

#define IN_CRCHASH_C

/* Standard include files */
#include <string.h>
#include "crchash.h"
#include "crc32ieee8023.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char CRCHASH_C_RCSId[]="\n$Id: crchash.c,v 2.4 2005/11/08 12:41:48 luis Exp $\n";

/* functions */

CRC_STATE crchash(char *s)
{
	int l = strlen(s);

	return do_crc(0xffffffff, (CRC_BYTE *) s, l, crc32ieee8023) ^ 0xffffffff;
} /* crchash */

CRC_STATE crchashb(unsigned char *s, size_t n)
{
	return do_crc(0xffffffff, (CRC_BYTE *) s, n, crc32ieee8023) ^ 0xffffffff;
} /* crchashb */

/* $Id: crchash.c,v 2.4 2005/11/08 12:41:48 luis Exp $ */
