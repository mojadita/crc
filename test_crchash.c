/* $Id: test_crchash.c,v 2.2 2005/11/08 12:08:57 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Nov  4 12:00:18 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 * CONFIGURATION_ITEM: CPCI Controller Software(0141893320300)
 * CONFIGURATION_UNIT: Low Level OS Library (0141893321800)
 */

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

int main(int argc, char **argv)
{
    static char buffer[1024];

    while(fgets(buffer, sizeof buffer, stdin)) {
        char *s = strtok(buffer, "\n");
        if (!s) continue;
        printf("0x%016lx: %s\n", crchash(s), s);
    } /* while */

    return 0;
} /* main */

/* $Id: test_crchash.c,v 2.2 2005/11/08 12:08:57 luis Exp $ */
