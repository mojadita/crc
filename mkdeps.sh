#!/bin/sh
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Date: lun dic  1 19:20:05 EET 2014

tmpfile="/tmp/mkdeps-$$.dat"
trap "rm -f $tmpfile" EXIT

grep '^[ 	]*0x[0-9a-fA-F]*[ 	]*[_a-zA-Z][_a-zA-Z0-9]*[ 	]' crctables.dat | sort >"$tmpfile"

unset CRC_TABLES
while read polin name comment
do
	CRC_TABLES="$CRC_TABLES ${name}"
done <"$tmpfile"

cat <<EOF
# makefile for the creation of all the crc tables.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# THIS FILE GENERATED AUTOMATICALLY, DON'T EDIT.
# Date: $(LANG=C date)
# Created-with: $0 $*
# Copyright: (C) $(date +%Y) LUIS COLORADO SISTEMAS S.L.U.
#            All rights reserved.

tables_names =$CRC_TABLES

# individual source files dependencies
EOF

while read polin name comment
do
	echo "${name}.c: mkcrc"
	echo "	mkcrc -g -p $polin -n $name > ${name}.c"
	echo
done <"$tmpfile"
