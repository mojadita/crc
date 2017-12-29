/* $Id: test_crchash.c,v 2.2 2005/11/08 12:08:57 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
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

#define IN_TEST_CRCHASH_C

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

#include "crchash.h"

/* constants */

/* types */

/* prototypes */

/* variables */
static char TEST_CRC_C_RCSId[]="\n$Id: test_crchash.c,v 2.2 2005/11/08 12:08:57 luis Exp $\n";

/* functions */

int main(int argc, char **argv)
{
	static char buffer[1024];

	while(fgets(buffer, sizeof buffer, stdin)) {
		char *s = strtok(buffer, "\n");
		if (!s) continue;
		printf("0x%016llx: %s\n", crchash(s), s);
	} /* while */

	return 0;
} /* main */

/* $Id: test_crchash.c,v 2.2 2005/11/08 12:08:57 luis Exp $ */
