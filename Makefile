# Author: Luis Colorado <lc@luiscoloradosistemas.com>
# Date: vie nov 28 18:41:06 EET 2014

.PHONY: all clean

targets = test_crc test_crchash

all: $(targets)
clean:
	$(MAKE) -f libcrc.mk clean
	$(RM) $(targets) \
		$(mkcrc_objs) \
		$(test_crc_objs) \
		$(test_crchash_objs) \
		mkcrc libcrc.mk

libcrc.a: libcrc.mk crc.[ch] mkcrc fprintbuf.[ch] 
	$(MAKE) -f libcrc.mk

libcrc.mk: mkcrc mkdeps.sh
	mkdeps.sh libcrc > $@

mkcrc_objs = mkcrc.o crc_table.o

mkcrc: $(mkcrc_objs)
	$(CC) $(LDFLAGS) -o $@ $(mkcrc_objs)

$(mkcrc_objs): crc.h

test_crc_objs = test_crc.o libcrc.a 

test_crc: $(test_crc_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crc_objs)

test_crchash_objs = test_crchash.o crchash.o crc32ieee8023.o libcrc.a
test_crchash: $(test_crchash_objs)
	$(CC) $(LDFLAGS) -o $@ $(test_crchash_objs)

test_crc.o: crc.h

