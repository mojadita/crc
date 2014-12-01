/* $Id: mkcrc.c,v 2.2 2005/11/07 23:22:18 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Thu Nov  3 10:05:42 CET 2005
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

#define IN_MKCRC_C

/* Standard include files */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "crc.h"
#include "mkcrc.h"

/* constants */
/* types */

/* prototypes */

/* variables */

int config_flags = 0;

/* functions */
void do_usage(void)
{
} /* do_usage */

int fprintpol(FILE *f, CRC_STATE p)
{
	int res = 0, n = 0;
	CRC_STATE m;

	/* calculamos el grado */
	for (m = p; m; m >>= 1) n++;

	res += fprintf(f, "x^%d", n--);
	for (m = p; m; m >>= 1) {
		if (m & 1)
			res += fprintf(f,
				  (n==1) ? "+x"
				: (n==0) ? "+1"
				: "+x^%d",
				n);
		n--;
	} /* for */

	return res;
} /* fprintpol */

static CRC_STATE calc(int n, CRC_STATE v, CRC_STATE p)
{
	int i;

	for (i = 0; i < n; i++) {
		if (v & 1) v = (v >> 1) ^ p;
		else v >>= 1;
	} /* for */

	return v;
} /* calc */

static inline long cycle(CRC_STATE p)
{
	int v1, v2;
	CRC_STATE res = 0;

	v1 = v2 = 1;

	/* buscamos la repetición */
	do {
		v1 = calc(1, v1, p); /* iteramos una vez */
		v2 = calc(2, v2, p); /* iteramos dos veces */
	} while (v1 != v2); /* hasta que uno alcance al otro */

	do {
		v2 = calc(1, v2, p); /* iteramos */
		res++;
	} while (v1 != v2); /* hasta recorrer una vez el ciclo */
	
	return res;
} /* cycle */

/* main program */
int main (int argc, char **argv)
{

	extern int optind;
	extern char *optarg;
	int opt;

	CRC_STATE val;
	CRC_STATE pol_mask = DEFAULT_POL;
	CRC_STATE limite;
	int conf_index = 0;
	char name[256];

	while ((opt = getopt(argc, argv, "hp:lgvL")) != EOF) {
		switch(opt) {
		case 'h': do_usage(); exit(0);
		case 'p': { int i;
			for (i = 0; crc_table[i].name; i++)
				if (!strcmp(optarg, crc_table[i].name))
					break;
			if (crc_table[i].name) {
				pol_mask = crc_table[i].pol;
				snprintf(name, sizeof name, "%s", crc_table[i].name);
			} else {
				if (sscanf(optarg, "%llx", &pol_mask) != 1)
					pol_mask = DEFAULT_POL;
				snprintf(name, sizeof name, "pol_0x%llx", pol_mask);
			} /* if */
			break;
		} /* block */
		case 'l': config_flags |= FLAGS_LIST; break;
		case 'g': config_flags |= FLAGS_GEN; break;
		case 'v': config_flags |= FLAGS_VERBOSE; break;
		case 'L': config_flags |= FLAGS_LISTCRCS; break;
		} /* switch */
	} /* while */

	limite = 0;
	while (limite < pol_mask) {
		limite <<= 1;
		limite |= 1;
	} /* while */

	if (config_flags & FLAGS_LIST) {
		while (pol_mask <= limite) {
			CRC_STATE cy = cycle(pol_mask);

			printf("%20llu: 0x%llx %s",
				cy, pol_mask, (cy == limite) ? " OK" : "");
			if ((cy == limite) || (config_flags & FLAGS_VERBOSE)) {
				printf(" --> ");
				fprintpol(stdout, pol_mask);
			} /* if */
			printf("\n");
			pol_mask++;
		} /* for */
	} else if (config_flags & FLAGS_LISTCRCS) {
		int i;
		for (i = 0; crc_table[i].name; i++) {
			printf("%s\n",
				crc_table[i].name);
		}
	} else if (config_flags & FLAGS_GEN) {
		int i;

		printf(
"/* THIS FILE GENERATED AUTOMATICALLY, DON'T EDIT.\n"
" * Author: Luis Colorado <lc@luiscoloradosistemas.com>\n"
" * Copyright: (C) 2014 LUIS COLORADO SISTEMAS, S.L.U.\n"
" *            All rights reserved.\n"
" */\n");
		printf("#include \"crc.h\"\n");
		printf("CRC_STATE %s[] = {\n", name);

		printf("\t/* Comando usado:");
		for (i = 0; i < argc; i++) printf(" %s", argv[i]);
		printf(" */\n");

		printf("\t/* Polinomio: ");
		fprintpol(stdout, pol_mask);
		printf(" */\n");

		for (val = 0; val < BYTE_VALUES; val++) {
			if (val % N_PER_LINE == 0) printf("\t/* %3lu */", val);
			printf(" 0x%llx,", calc(BITS_PER_BYTE, val, pol_mask));
			if (val % N_PER_LINE == N_PER_LINE - 1) printf("\n");
		} /* for */
		if (val % N_PER_LINE != 0) printf("\n");
		printf("}; /* %s */\n", name);

	} /* if */

	return 0;

} /* main */

/* $Id: mkcrc.c,v 2.2 2005/11/07 23:22:18 luis Exp $ */
