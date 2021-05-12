/* $Id: test_crc.c,v 2.4 2005/11/07 23:22:18 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Nov  4 12:00:18 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 * CONFIGURATION_ITEM: CPCI Controller Software(0141893320300)
 * CONFIGURATION_UNIT: Low Level OS Library (0141893321800)
 */

#define IN_TEST_CRC_C

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>

#include "crc.h"
#include "crc_alltables.h"
#include "fprintbuf.h"

#define NN                  1024
#define NCOLS               64

int main(int argc, char **argv)
{

    static CRC_BYTE buffer[NN];
    struct crc_table_s *p = NULL;
    int N = 0;
    CRC_STATE m = 0;
    int opt;

    while ((opt = getopt(argc, argv, "p:")) != EOF) {
        switch(opt) {
        case 'p':
            {   int i;
                for (i = 0; i < crc_alltables_n; i++) {
                    if (strcasecmp(crc_alltables[i]->cr_name, optarg) == 0) {
                        fprintf(stderr,
                            "Pol: %s\n", crc_alltables[i]->cr_name);
                        break;
                    } /* if */
                } /* for */
                if (i < crc_alltables_n)
                    p = crc_alltables[i];
            } break;
        } /* switch */
    } /* while */

    if (!p) p = crc_alltables[0];

    argc -= optind; argv += optind;

#if 0
    while (m <= p->cr_table[0x80]) {
        N++; m <<= 8; m |= 0xff;
    } /* while */
#else
    N = p->cr_bytesize;
    m = p->cr_mask;
#endif

    while(fgets((char *)buffer, NN-N, stdin)) {
        CRC_STATE crc;
        ssize_t l = strlen((const char *)buffer);
        int i, col, nl = 0;

        while((l > 0) && iscntrl(buffer[l-1])) --l;
        if (l < 0) l = 0;
        buffer[l] = '\0';

        m = add_crc(m, buffer + l, N, p);

        m = do_crc(m, buffer, l, p);

        crc = add_crc(m, buffer + l, N, p);

        fprintbuf(stdout, l + N, buffer,
            "%s[%0*llx] %.*s",
            p->cr_name,
            (p->cr_size + 3)/4,
            crc,
            l,
            buffer);
    } /* while */

    return 0;
} /* main */
