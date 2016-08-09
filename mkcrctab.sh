#!/bin/sh
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Date: lun dic  1 19:20:05 EET 2014

cat <<EOF
/* table of crc.  Be careful, as if you use this table you'll
 * force link of all the crc tables configured.
 * ATTENTION: THIS FILE GENERATED AUTOMATICALLY, DON'T EDIT.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: $(date)
 * Generated with: $0 $*
 * Copyright: (C) $(date +%Y) LUIS COLORADO SISTEMAS S.L.U.
 *            All rights reserved.
 */

#include "crc.h"

/* external references */
EOF

TABLES=$(sort crctables.dat | cut -f2 -d"	")

for i in ${TABLES}
do
	echo "extern struct crc_table_s ${i};"
done 

cat <<EOF

/* table */
struct crc_table_s *crcs_table[] = {
EOF

for i in ${TABLES}
do
	echo "    &${i},"
done

cat <<EOF
}; /* crcs_table */

size_t ${i}_n = sizeof ${i} / sizeof ${i}[0];

/* EOF */
EOF
