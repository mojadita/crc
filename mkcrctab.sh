#!/bin/sh
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: lun dic  1 19:20:05 EET 2014

tmpfile="/tmp/mkcrctab-$$.dat"
trap "rm -f $tmpfile" EXIT
grep '^[ 	]*0x[0-9a-fA-F][0-9a-fA-F]*[ 	]*[_a-zA-Z][_a-zA-Z0-9]*[ 	]*' crctables.dat | sort >"$tmpfile"

tablename="crc_alltables"
unset polins names
while read polin name comment
do
    polins="$polins $polin"
    names="$names $name"
done <"$tmpfile"

name=crc_alltables.h
(cat <<EOF
/* ${name}.  All tables definitions.
 * ATTENTION: THIS FILE GENERATED AUTOMATICALLY, DON_T EDIT.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: $(date)
 * Generated with: $0 $*
 * Copyright: (C) $(date +%Y) LUIS COLORADO SISTEMAS S.L.U.
 *            All rights reserved.
 */

#include "crc.h"

/* external references */
EOF

for i in ${names}
do
	echo "extern CRC_TABLE ${i};"
done 

echo "extern size_t ${tablename}_n;"
) >"${name}"

name=crc_alltables.c
(cat <<EOF
/* ${name}.  Be careful, as if you use this table you_ll
 * force link of all the crc tables configured.
 * ATTENTION: THIS FILE GENERATED AUTOMATICALLY, DON_T EDIT.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: $(date)
 * Generated with: $0 $*
 * Copyright: (C) $(date +%Y) LUIS COLORADO SISTEMAS S.L.U.
 *            All rights reserved.
 */

#include "crc.h"

/* external references */
EOF

for i in ${names}
do
	echo "extern struct crc_table_s _${i};"
done 

cat <<EOF

/* table */
CRC_TABLE ${tablename}[] = {
EOF

for i in ${names}
do
	echo "    &_${i},"
done

cat <<EOF
}; /* crcs_table */

size_t ${tablename}_n = sizeof ${tablename} / sizeof ${tablename}[0];

/* EOF */
EOF
) >"${name}"
