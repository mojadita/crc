#!/bin/sh
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Date: Mon dec  1 19:20:05 EET 2014


exec 3>"libcrc.mk"

cat <<EOF >&3
# makefile for the creation of all the crc tables.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# THIS FILE GENERATED AUTOMATICALLY, DON'T EDIT.
# Date: $(LANG=C date)
# Created-with: $0 $*
# Copyright: (C) $(date +%Y) LUIS COLORADO SISTEMAS S.L.U.
#            All rights reserved.

# individual source files dependencies
EOF

grep '^[ 	]*0x[0-9a-fA-F][0-9a-fA-F]*[ 	]*[_a-zA-Z][_a-zA-Z0-9]*' \
	crctables.dat | sort |\
while read polin name comment
do
	echo ${name}
	echo "${name}.c: mkcrc" >&3
	echo "	mkcrc -g -p $polin -n ${name} > \$@" >&3
	echo >&3
done
