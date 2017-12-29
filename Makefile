# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: vie nov 28 18:41:06 EET 2014

.PHONY: all clean install deinstall

package			?= crc
version_major	?= 1
version_minor	?= 2
prefix			?= $(HOME)
idir			?= $(prefix)/include
ddir			?= $(prefix)/share/$(package)
bdir			?= $(prefix)/bin
ldir			?= $(prefix)/lib

RM				= rm -f
INSTALL			= install
LINK			= ln -sf
UMOD			?= -o $$(id -u) -g $$(id -g)
FMOD			?= -m 0644
DMOD			?= -m 0755
XMOD			?= -m 0711

.SUFFIXES: .c .o .pico .a .so

LDFLAGS			?= -g
CFLAGS		    ?= -g -O0

tables_names 		!= mkdeps.sh
tables_basenames 	= $(tables_names:S/^/lib/) lib$(package)
tables_sos 			= $(tables_basenames:=.so)
tables_sonames 		= $(tables_sos:=.$(version_major))
tables_fullnames 	= $(tables_sonames:=.$(version_minor))
tables_picos		= $(tables_names:=.pico) crc.pico
tables_srcs			= $(tables_names:=.c)
tables_objs			= $(tables_names:=.o) crc.o
targets = $(tables_fullnames) $(tables_sonames) $(tables_sos)
targets += libcrc_alltables.so.$(version_major).$(version_minor)
targets += lib$(package).a
toclean = $(targets) $(tables_picos) $(tables_srcs) $(tables_objs)
targets				+= crc

all: $(targets)
clean:
	$(RM) $(toclean)

install: $(targets)
.for i in $(idir) $(ddir) $(bdir) $(ldir)
	$(INSTALL) $(DMOD) $(UMOD) -d ${i}
.endfor
.for i in $(tables_fullnames) \
		lib$(package).so.$(version_major).$(version_minor) \
		libcrc_alltables.so.$(version_major).$(version_minor)
	$(INSTALL) $(FMOD) $(UMOD) $i $(ldir)
	$(LINK) $i $(ldir)/$(i:.$(version_minor)=)
	$(LINK) $(i:.$(version_minor)=) $(ldir)/$(i:.$(version_major).$(version_minor)=)
.endfor
	$(INSTALL) $(FMOD) $(UMOD) lib$(package).a $(ldir)
	$(INSTALL) $(FMOD) $(UMOD) crc.h           $(idir)
	$(INSTALL) $(FMOD) $(UMOD) crc_alltables.h $(idir)
	$(INSTALL) $(XMOD) $(UMOD) mkcrc           $(bdir)

deinstall:
.for i in $(tables_fullnames) \
		lib$(package).so.$(version_major).$(version_minor) \
		libcrc_alltables.so.$(version_major).$(version_minor)
	-$(RM) $(ldir)/$i
	-$(RM) $(ldir)/$(i:.$(version_minor)=)
	-$(RM) $(ldir)/$(i:.$(version_major).$(version_minor)=)
.endfor
	-$(RM) $(ldir)/lib$(package).so.$(version_major).$(version_minor)
	-$(RM) $(ldir)/lib$(package).so.$(version_major)
	-$(RM) $(ldir)/lib$(package).so
	-$(RM) $(ldir)/lib$(package).a
	-$(RM) $(idir)/crc.h
	-$(RM) $(idir)/crc_alltables.h
	-$(RM) $(bdir)/mkcrc

$(tables_fullnames): $(@:S/^lib//:.so.$(version_major).$(version_minor)=.pico)
	$(CC) $(LDFLAGS) -o $@ -shared -Wl,-soname=$(@:.$(version_minor)=) $?
$(tables_sonames):
	$(LINK) $(@:=.$(version_minor)) $@
$(tables_sos):
	$(LINK) $(@:=.$(version_major)) $@

.include "libcrc.mk"

libcrc_alltables.so.$(version_major).$(version_minor): crc_alltables.pico $(tables_fullnames)
	$(CC) $(LDFLAGS) -o $@ -shared -Wl,-soname=libcrc_alltables.so.$(version_major) $>
toclean			+= libcrc_alltables.so.$(version_major).$(version_minor)
toclean			+= libcrc_alltables.so.$(version_major)
toclean			+= libcrc_alltables.so

lib_a_objs = $(tables_objs) crc.o crc_alltables.o

lib$(package).a: $(lib_a_objs:.o=.c)
	$(CC) $(CFLAGS) -c $?
	ar -r $@ $(?:.c=.o)
	ranlib $@

	$(RM) $(?:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
.c.pico:
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# MKCRC
mkcrc_objs = mkcrc.o bits.o
toclean			+= $(mkcrc_objs) mkcrc
mkcrc: $(mkcrc_objs)
	$(CC) $(LDFLAGS) -o $@ $(mkcrc_objs)
$(mkcrc_objs): crc.h bits.h

crc_objs = test_crc.o fprintbuf.o
crc_ldflags = -L$(ldir)
crc_libs = -lcrc -lcrc_alltables
crc: $(crc_objs)
	$(CC) $(LDFLAGS) -o $@ $(crc_ldflags) $(crc_objs) $(crc_libs)

crc_alltables.c crc_alltables.h: mkcrctab.sh
	mkcrctab.sh 
toclean			+= crc_alltables.c crc_alltables.h

crc_alltables.o: crc_alltables.h
toclean			+= crc_alltables.o
crc_alltables.pico: crc_alltables.h
toclean			+= crc_alltables.pico

fprintbuf.o: fprintbuf.h
toclean			+= fprintbuf.o

libcrc.mk: mkdeps.sh
	mkdeps.sh >$@

