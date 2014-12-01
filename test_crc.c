/* $Id: test_crc.c,v 2.4 2005/11/07 23:22:18 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Fri Nov  4 12:00:18 CET 2005
 * CONFIGURATION_ITEM: CPCI Controller Software(0141893320300)
 * CONFIGURATION_UNIT: Low Level OS Library (0141893321800)
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

#define IN_TEST_CRC_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "crc.h"
#include "fprintbuf.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char TEST_CRC_C_RCSId[]="\n$Id: test_crc.c,v 2.4 2005/11/07 23:22:18 luis Exp $\n";

/* functions */

extern CRC_STATE crc32[];

int main(int argc, char **argv)
{
#define N 4
	static CRC_BYTE buffer[1024 + N],
		buffer2[] = {
			0x00, 0x0A, 0xE6, 0xF0, 0x05, 0xA3,
			0x00, 0x12, 0x34, 0x56, 0x78, 0x90,
			0x08, 0x00, 0x45, 0x00, 0x00, 0x30, 0xB3, 0xFE,
			0x00, 0x00, 0x80, 0x11, 0x72, 0xBA, 0x0A, 0x00,
			0x00, 0x03, 0x0A, 0x00, 0x00, 0x02, 0x04, 0x00,
			0x04, 0x00, 0x00, 0x1C, 0x89, 0x4D, 0x00, 0x01,
			0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
			0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
			0x12, 0x13, 0x00, 0x00, 0x00, 0x00,

			//7A D5 6B B3 //frame checksum
	};
	int l = sizeof buffer2, i;
	CRC_STATE crc;

	crc = 0xffffffff ^ add_crc(0xffffffff, buffer2, l, crc32, N);
	for (i = 0; i < N; i++) buffer2[l-N+i] ^= 0xff;

#if 1
	fprintbuf(stdout, l, buffer2, "trama ethernet, crc=0x%llx", crc);
#endif
	
	while((l = read(0, (char *)buffer, sizeof buffer - N)) > 0) {
		CRC_STATE crc;
		memset(buffer + l, 0xff, N);
		fprintbuf(stdout, l, buffer, "buffer sin CRC");
		l += N;
		crc = 0xffffffff ^ add_crc(0xffffffff, buffer, l, crc32, N);
		for (i = 0; i < N; i++) buffer[l-N+i] ^= 0xff;
		fprintbuf(stdout, l, buffer, "CRC = 0x%llx", crc);

	} /* while */

	return 0;
} /* main */

/* $Id: test_crc.c,v 2.4 2005/11/07 23:22:18 luis Exp $ */
