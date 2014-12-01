#!/bin/sh
# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Date: lun dic  1 19:20:05 EET 2014

libname="$1"

echo -n "${libname}_objs ="

for i in $(mkcrc -L)
do
	echo "	${i}.o \\"
done 

cat <<EOF

targets = ${libname}.a

all: \$(targets)
clean:
	\$(RM) \$(targets) \$(${libname}_objs:.o=.c) crctables.c

\$(${libname}_objs:.o=.c): mkcrc
	for i in \$\$(mkcrc -L); \\
	do \\
		mkcrc -g -p \$\${i} > \$\${i}.c; \\
	done

${libname}.a: ${libname}.a(\$(${libname}_objs)) \\
	${libname}.a(crctables.o crc.o fprintbuf.o)

${libname}.a(crc.o): crc.h
${libname}.a(fprintbuf.o): fprintbuf.h

crctables.c: mkcrctab.sh
	mkcrctab.sh > \$@

EOF

	

