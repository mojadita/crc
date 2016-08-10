# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: vie nov 28 18:41:06 EET 2014

.PHONY: all clean install deinstall

package			?= crc
version_major	?= 0.1
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

targets_install = $(lib_a) $(lib_so)
targets			= $(targets_install) test_crc test_crchash test_crc_so
RM				= rm -f
INSTALL			= install
LINK			= ln -sf
UMOD			?= -o $$(id -u) -g $$(id -g)
FMOD			?= -m 0644
DMOD			?= -m 0755
XMOD			?= -m 0711

all: $(targets)
clean:
	$(RM) $(targets) $(toclean)
install: $(targets_install)
	-for i in $(idir) $(ddir) $(bdir) $(ldir); \
	do \
		$(INSTALL) $(DMOD) $(UMOD) -d $${i}; \
	done
	$(INSTALL) $(FMOD) $(UMOD) $(lib_fullname) $(ldir)
	$(LINK) $(lib_fullname) $(ldir)/$(lib_soname)
	$(LINK) $(lib_soname) $(ldir)/$(lib_so)
	$(INSTALL) $(FMOD) $(UMOD) $(lib_a)        $(ldir)
	$(INSTALL) $(FMOD) $(UMOD) crc.h           $(idir)
	$(INSTALL) $(FMOD) $(UMOD) crc_alltables.h $(idir)
deinstall:
	-$(RM) $(ldir)/$(lib_fullname)
	-$(RM) $(ldir)/$(lib_soname)
	-$(RM) $(ldir)/$(lib_so)
	-$(RM) $(ldir)/$(lib_a)
	-$(RM) $(idir)/crc.h
	-$(RM) $(idir)/crc_alltables.h

.SUFFIXES: .c .o .so .a

.include "libcrc.mk"

tables_extra = crc crc_alltables

tables_static_objs = $(tables_names:=.o) $(tables_extra:=.o)
toclean			+= $(tables_static_objs)

tables_dynamic_objs = $(tables_names:=.so) $(tables_extra:=.so)
toclean			+= $(tables_dynamic_objs)

tables_sources = $(tables_names:=.c)
toclean			+= $(tables_sources)

$(lib_a): $(tables_static_objs)
	ar r $@ $?
	ranlib $@

$(lib_so): $(lib_soname)
	$(LINK) $? $@
$(lib_soname): $(lib_fullname)
	$(LINK) $? $@
$(lib_fullname): $(tables_dynamic_objs)
	$(CC) $(LDFLAGS) -o $@ -shared $(tables_dynamic_objs)
toclean			+= $(lib_so) $(lib_soname) $(lib_fullname)

.c.so:
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

$(tables_static_objs) $(tables_dynamic_objs): crc.h

mkcrc_objs = mkcrc.o bits.o
toclean			+= $(mkcrc_objs) mkcrc
mkcrc: $(mkcrc_objs)
	$(CC) $(LDFLAGS) -o $@ $(mkcrc_objs)
$(mkcrc_objs): crc.h bits.h

crc_alltables.{c,h}: mkcrctab.sh
	mkcrctab.sh 
toclean			+= crc_alltables.{c,h,so,o}
crc_alltables.o: crc_alltables.h

test_crc_objs = test_crc.o fprintbuf.o libcrc.a 
toclean			+= test_crc.o fprintbuf.o
test_crc: $(test_crc_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crc_objs)

test_crc_so_objs = test_crc.o fprintbuf.o libcrc.so
test_crc_so: $(test_crc_so_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crc_so_objs)

test_crchash_objs = test_crchash.o crchash.o fprintbuf.o libcrc.a
toclean			+= test_crchash.o crchash.o 
test_crchash: $(test_crchash_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crchash_objs)

test_crc.o test_crchash.o: crc.h crc_alltables.h

fprintbuf.o: fprintbuf.h

libcrc.mk: mkdeps.sh
	mkdeps.sh >$@
