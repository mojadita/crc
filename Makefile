# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: vie nov 28 18:41:06 EET 2014

.PHONY: all clean install deinstall

package			?= crc
version_major	?= 1
version_minor	?= 8
prefix			?= $(HOME)
idir			?= $(prefix)/include
ddir			?= $(prefix)/share/$(package)
bdir			?= $(prefix)/bin
ldir			?= $(prefix)/lib

RM				 = rm -f
INSTALL			 = install
LINK			 = ln -sf
UMOD			?= -o $$(id -u) -g $$(id -g)
FMOD			?= -m 0644
DMOD			?= -m 0755
XMOD			?= -m 0711

.SUFFIXES: .pico

.c.pico:
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

LDFLAGS			?= -g
CFLAGS		    ?= -g -O0

tables_names   != mkdeps.sh
tables_picos	= $(tables_names:=.pico)
tables_srcs		= $(tables_names:=.c)
tables_objs		= $(tables_names:=.o)
lib_base		= lib$(package)
lib_a			= $(lib_base).a
lib_so			= $(lib_base).so
lib_soname		= $(lib_so).$(version_major)
lib_fullname	= $(lib_soname).$(version_minor)
toclean		   += $(tables_picos) crc.pico crchash.pico crc_alltables.pico
toclean		   += $(tables_srcs)
toclean		   += $(lib_a) $(lib_so) $(lib_soname) $(lib_fullname)

targets         = test_crc test_crchash crc
toclean        += $(targets)

all: $(targets)
clean:
	$(RM) $(toclean)

install: $(targets)
	$(INSTALL) $(DMOD) $(UMOD) -d ${idir}
	$(INSTALL) $(DMOD) $(UMOD) -d ${ddir}
	$(INSTALL) $(DMOD) $(UMOD) -d ${bdir}
	$(INSTALL) $(DMOD) $(UMOD) -d ${ldir}
	$(INSTALL) $(FMOD) $(UMOD) $(lib_a) 		$(ldir)
	$(INSTALL) $(FMOD) $(UMOD) $(lib_fullname) 	$(ldir)
	$(LINK) $(lib_fullname)	$(ldir)/$(lib_soname)
	$(LINK) $(lib_soname)	$(ldir)/$(lib_so)
	$(INSTALL) $(FMOD) $(UMOD) crc.h           	$(idir)
	$(INSTALL) $(FMOD) $(UMOD) crc_alltables.h 	$(idir)
	$(INSTALL) $(XMOD) $(UMOD) mkcrc           	$(bdir)

deinstall:
	-$(RM) $(bdir)/mkcrc
	-$(RM) $(idir)/crc_alltables.h
	-$(RM) $(idir)/crc.h
	-$(RM) $(ldir)/$(lib_so)
	-$(RM) $(ldir)/$(lib_soname)
	-$(RM) $(ldir)/$(lib_fullname)
	-$(RM) $(ldir)/$(lib_a)

# STATIC LIBRARY
lib_a_srcs = $(tables_srcs) crc.c crc_alltables.c crchash.c
$(lib_a): $(lib_a_srcs)
	$(CC) $(CFLAGS) -c $?
	ar -r $@ $(?:.c=.o)
	...
	$(RM) $(?:.c=.o)
	ranlib $@

# DYNAMIC LIBRARY
lib_fullname_deps =
lib_fullname_objs = $(tables_picos) crc.pico crc_alltables.pico crchash.pico

$(lib_so): $(lib_soname)
	$(LINK) $> $@
$(lib_soname): $(lib_fullname)
	$(LINK) $> $@
$(lib_fullname): $(lib_fullname_objs)
	$(LD) $(LDFLAGS) -o $@ -shared -soname=$(lib_soname) $(lib_fullname_objs)

.include "libcrc.mk"

# CRC
crc_deps          = $(lib_a) $(lib_so)
crc_objs          = main.o
crc_libs          = -lcrc
crc_ldfl          = -L.
toclean          += $(crc_objs) crc
crc: $(crc_deps) $(crc_objs)
	$(CC) $(LDFLAGS) $($@_ldfl) -o $@ $($@_objs) $($@_libs)

# MKCRC
mkcrc_deps        =
mkcrc_objs        = mkcrc.o bits.o
mkcrc_ldfl        =
mkcrc_libs        =
toclean	         += $(mkcrc_objs) mkcrc
mkcrc: $(mkcrc_objs)
	$(CC) $(LDFLAGS) -o $@ $(mkcrc_objs)

# test programs
test_crc_deps     = $(lib_so) $(lib_a)
test_crc_objs     = test_crc.o fprintbuf.o
test_crc_ldfl     = -L. -L$(ldir)
test_crc_libs     = -lcrc
toclean		     += test_crc.o
test_crc: $(test_crc_objs) $(test_crc_deps)
	$(CC) $(LDFLAGS) -o $@ $($@_ldfl) $($@_objs) $($@_libs)
test_crc.o: crc.h crc_alltables.h

test_crchash_deps = $(lib_so) $(lib_a)
test_crchash_objs = test_crchash.o fprintbuf.o
test_crchash_ldfl = -L. -L$(ldir)
test_crchash_libs = -lcrc
toclean			 += test_crchash.o
test_crchash: $(test_crchash_deps) $(test_crchash_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_ldfl) $($@_objs) $($@_libs)
test_crchash.o: crc.h crc_alltables.h

mod_alltables 	  = crc_alltables.c crc_alltables.h
$(mod_alltables): mkcrctab.sh crctables.dat
	mkcrctab.sh 
toclean			 += $(mod_alltables)

crc_alltables.o crc_alltables.pico: crc_alltables.h

fprintbuf.o: fprintbuf.h
toclean		 	 += fprintbuf.o
