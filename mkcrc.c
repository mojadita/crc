/* $Id: mkcrc.c,v 2.2 2005/11/07 23:22:18 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Nov  3 10:05:42 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#define F(fmt) "%s:%d:%s:" fmt, __FILE__, __LINE__, __func__

#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "crc.h"
#include "mkcrc.h"
#include "bits.h"

int config_flags = 0;

static void do_usage(void);
static int check_name(char *s);
static inline CRC_STATE cycle(CRC_STATE p);


static inline CRC_STATE cycle(CRC_STATE p)
{
    CRC_STATE v1, v2;
    CRC_STATE res = 0;

    v1 = v2 = 1ULL;

    /* buscamos la repetición */
    do {
        v1 = slow_do_crc(1, v1, p); /* iteramos una vez */
        v2 = slow_do_crc(2, v2, p); /* iteramos dos veces */
    } while (v1 != v2); /* hasta que uno alcance al otro */

    do {
        v2 = slow_do_crc(1, v2, p); /* iteramos */
        res++;
    } while (v1 != v2); /* hasta recorrer una vez el ciclo */

    return res;
} /* cycle */

static int check_name(char *s)
{
    if (!isalpha(*s) && *s != '_') return -1;
    while (*++s)
        if (!isalnum(*s) && *s != '_') return -1;
    return 0;
}

static void do_usage(void)
{
    fprintf(stderr,
        "Usage: mkcrc [ options ... ]\n"
        "Options:\n"
        " -h  help option.  Shows this help screen.\n"
        " -n <name> Use <name> as name for generated polynomial.\n"
        " -p <pol> Use polynomial <pol>  Polinomial is\n"
        "    given in hex with least significant coefficient x0\n"
        "    in most significant bit.  Most significant bit, which\n"
        "    should be always one, is not included in hex number, so\n"
        "    for example 0x1001 represents the polynomial\n"
        "    x^13 + x^12 + 1.\n"
        " -l  lists polinomials from the given one upwards to exhaust\n"
        "    all the polynomial space.\n"
        " -g  generates the polynomial table (256 entries) of xor masks.\n"
        "    table can be used with the crc() function.\n"
        " -v  be verbose.\n"
        "\n");
} /* do_usage */

/* main program */
int main (int argc, char **argv)
{
    int opt;
    CRC_STATE val;
    CRC_STATE pol_mask = DEFAULT_POL_MASK;
    CRC_STATE limite;
    int conf_index = 0;
    char name[256] = "";

    while ((opt = getopt(argc, argv, "hp:n:lgv")) != EOF) {
        switch(opt) {
        case 'h': do_usage(); exit(0);
        case 'n':
            if (check_name(optarg)) {
                fprintf(stderr, F("invalid name format: %s\n"), optarg);
                exit(EXIT_FAILURE);
            }
            strncpy(name, optarg, sizeof name);
            break;
        case 'p':
            if (sscanf(optarg, "%lx", &pol_mask) != 1) {
                fprintf(stderr, F("invalid pol mask: %s\n"), optarg);
                exit(EXIT_FAILURE);
            }
            if (check_name(optarg)) {
                snprintf(name, sizeof name,
                        "pol_%#lx", pol_mask);
            }
            break;
        case 'l': config_flags |= FLAGS_LIST; break;
        case 'g': config_flags |= FLAGS_GEN; break;
        case 'v': config_flags |= FLAGS_VERBOSE; break;
        } /* switch */
    } /* while */

    limite = msbmask(pol_mask);

    if (config_flags & FLAGS_LIST) {
        char buffer[1024];
        while (pol_mask <= limite) {
            CRC_STATE cy = cycle(pol_mask);

            printf("%20lu: 0x%lx", cy, pol_mask);
            if ((cy == limite) || (config_flags & FLAGS_VERBOSE)) {
                printf("%s%s",
                        (cy == limite) ? " <<< " : " ",
                        pol2str(pol_mask,
                            buffer, sizeof buffer));
            } /* if */
            printf("%s\n", (cy == limite) ? " >>>" : "");
            pol_mask++;
        } /* for */
    } else if (config_flags & FLAGS_GEN) {
        int i;
        size_t size = msbpos(pol_mask);;
        char buffer[1024];
        struct tm *now = localtime(time(NULL), NULL);

        printf(
"/* THIS FILE GENERATED AUTOMATICALLY, DON'T EDIT.\n"
" * Author: Luis Colorado <luiscoloradourcola@gmail.com>\n"
" * Copyright: (C) 2005-%d LUIS COLORADO SISTEMAS, S.L.U.\n"
" *            All rights reserved.\n"
" */\n", now->tm_year + 1900);
        printf("#include \"crc.h\"\n");
        printf("struct crc_table_s _%s = {\n", name);

        printf("\t/* Comando usado:");
        for (i = 0; i < argc; i++) printf(" %s", argv[i]);
        printf(" */\n");
        printf("\t/* cr_name    : */ \"%s\",\n",    name);
        printf("\t/* cr_strpolin: */ \"%s\",\n",
                pol2str(pol_mask, buffer, sizeof buffer));
        printf("\t/* cr_size    : */ %zu,\n",      (size_t)size);
        printf("\t/* cr_bytesize: */ %zu,\n",      ((size_t)size+7) / 8);
        printf("\t/* cr_polin   : */ %#lx,\n",     pol_mask);
        printf("\t/* cr_mask    : */ %#lx,\n",     limite);
        printf("\t/* cr_table[] : */ {\n");

        for (val = 0; val < BYTE_VALUES; val++) {
            if (val % N_PER_LINE == 0) printf("\t/* %3lu */", val);
            printf(" 0x%lx,", slow_do_crc(BITS_PER_BYTE, val, pol_mask));
            if (val % N_PER_LINE == N_PER_LINE - 1) printf("\n");
        } /* for */
        if (val % N_PER_LINE != 0) printf("\n");
        printf("}}; /* %s */\n", name);
        printf("\n");
        printf("CRC_TABLE %s = &_%s;\n", name, name);

    } /* if */

    return 0;

} /* main */
