/* main.c -- principal module for crc program
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Wed May 12 17:41:01 EEST 2021
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "crc.h"
#include "main.h"
#include "process.h"

int conf_flags = 0;

int main(int argc, char **argv)
{
	int opt, res;
	char *polynomial;
	CRC_STATE istate;
	int status = STATUS_OK;

	while ((opt = getopt(argc, argv, "bi:p:hv")) >= 0) {
		switch (opt) {
		case 'b':
			conf_flags ^= FLAG_BINARY;
			break;

		case 'i':
			res = sscanf(optarg, "%li", &istate);
			if (res != 1) {
				ERR(EXIT_FAILURE,
					"invalid number %s, ignored\n",
					optarg);
				if (status < STATUS_CMDLINE) {
					status = STATUS_CMDLINE;
				}
			}
			break;

		case 'p':
			polynomial = optarg;
			break;

		case 'v':
			conf_flags ^= FLAG_VERBOSE;
			break;

		case 'h':
		default:
			conf_flags ^= FLAG_HELP;
			break;

		}
	}

	argc -= optind;
	argv += optind;

	if (argc) {
		int i;
		for (i = 0; i < argc; i++) {
			LOG("Processing [%s]:\n", argv[i]);
			int in = open(argv[i], O_RDONLY);
			if (in < 0) {
				ERR(0, "%s: %s (errno=%d)\n",
					argv[i],
					strerror(errno),
					errno);
				if (status < STATUS_OPENFIL) {
					status = STATUS_OPENFIL;
				}
				continue;
			}
			if (process(argv[i], in)
				&& (status < STATUS_PROCESS))
			{
				status = STATUS_PROCESS;
			}
			close(in);
		}
	} else {
		char *name = "stdin";
		LOG("Processing <%s>:\n", name);
		if (process(name, 0)
			&& (status < STATUS_PROCESS))
		{
			status = STATUS_PROCESS;
		}
	}
	return status;
}
