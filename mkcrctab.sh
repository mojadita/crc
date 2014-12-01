#!/bin/sh
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Date: lun dic  1 19:20:05 EET 2014

cat <<EOF
/* table of crcs.
 * ATTENTION: THIS FILE GENERATED AUTOMATICALLY, DON'T EDIT.
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: $(date)
 * Copyright: (C) $(date +%Y) LUIS COLORADO SISTEMAS S.L.U.
 *            All rights reserved.
 */

#include "crc.h"

/* prototypes */
EOF

for i in $(mkcrc -L)
do
	echo "extern CRC_STATE ${i}[];"
done 

cat <<EOF

/* table */
struct crc_table_s crcs_table[] = {
EOF

for i in $(mkcrc -L)
do
	echo "    \"${i}\", ${i},"
done

cat <<EOF
	NULL, NULL,
}; /* crcs_table */

/* EOF */
EOF
