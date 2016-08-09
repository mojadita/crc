# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: vie nov 28 18:41:06 EET 2014

.PHONY: all clean install deinstall

package			?= crc
version_major	?= 0.0
version_minor	?= 1
prefix			?= $(HOME)
idir			?= $(prefix)/include
ddir			?= $(prefix)/share/$(package)
bdir			?= $(prefix)/bin
ldir			?= $(prefix)/lib

LDFLAGS			?=
CFLAGS		    ?=

lib				= lib$(package)
lib_so			= $(lib).so
lib_a			= $(lib).a
lib_soname		= $(lib_so).$(version_major)
lib_fullname	= $(lib_soname).$(version_minor)

targets			= $(lib_a) $(lib_so) #test_crc test_crchash
RM				= rm -f
INSTALL			= install
LINK			= ln -sf

all: $(targets)
clean:
	$(RM) $(targets) \


.SUFFIXES: .c .o .so .a

.include "libcrc.mk"

tables_static_objs = $(tables_names:=.o)
tables_dynamic_objs = $(tables_names:=.so)
tables_sources = $(tables_names:=.c)

$(lib_fullname)_objs = $(tables_dynamic_objs) crc.so crc_alltables.so

$(lib_a):: $(lib_a)($(tables_static_objs) crc.o crc_alltables.o)
	ar r $@ $?
	ranlib $@

$(lib_so): $(lib_soname)
	$(LINK) $? $@
$(lib_soname): $(lib_fullname)
	$(LINK) $? $@
$(lib_fullname): $($(lib_fullname)_objs)
	$(CC) $(LDFLAGS) -o $@ -shared $($(lib_fullname)_objs)

.c.so:
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

libcrc.mk: mkdeps.sh
	mkdeps.sh >$@

mkcrc_objs = mkcrc.o bits.o
mkcrc: $(mkcrc_objs)
	$(CC) $(LDFLAGS) -o $@ $(mkcrc_objs)
$(mkcrc_objs): crc.h bits.h

crc_alltables.c: mkcrctab.sh
	mkcrctab.sh >crc_alltables.c

test_crc_objs = test_crc.o libcrc.a 

test_crc: $(test_crc_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crc_objs)

test_crchash_objs = test_crchash.o crchash.o crc32ieee8023.o libcrc.a
test_crchash: $(test_crchash_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crchash_objs)

test_crc.o: crc.h

