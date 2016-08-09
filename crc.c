/* $Id: crc.c,v 2.1 2005/11/05 17:51:35 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Thu Nov  3 16:18:12 CET 2005
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

#define IN_CRC_C

/* Standard include files */
#include <sys/types.h>
#include "crc.h"

/* variables/tables */
static char CRC_C_RCSId[]="\n$Id: crc.c,v 2.1 2005/11/05 17:51:35 luis Exp $\n";

/* FUNCIÓN DE CÁLCULO DE CRC POR TABLA */
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

/* $Id: crc.c,v 2.1 2005/11/05 17:51:35 luis Exp $ */
