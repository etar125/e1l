# Copyright (c) 2026 etar125 Admanse
# Licensed under ISC (see LICENSE)

include config.mk

SRC = src/e1_str.c src/e1_sarr.c src/e1_dstr.c
OBJ = $(SRC:src/%.c=bin/%.o)
OBJ_SHARED = $(SRC:src/%.c=bin/%_shared.o)
TSRC = tests/str_test.c tests/sarr_test.c tests/dstr_test.c
TEXE = $(TSRC:tests/%.c=tests/bin/%)

all: bin/libe1l.a bin/libe1l.so.$(VERSION) tests

tests: $(TEXE)

tests/bin/%: tests/%.c $(OBJ) include/e1l.h config.mk
	@mkdir -p tests/bin
	$(CC) $(ECFLAGS) $(OBJ) $< -o $@

bin/%_shared.o: src/%.c include/e1l.h config.mk
	@mkdir -p bin
	$(CC) $(ECFLAGS) -c $< -o $@ -fPIC

bin/%.o: src/%.c include/e1l.h config.mk
	@mkdir -p bin
	$(CC) $(ECFLAGS) -c $< -o $@

bin/libe1l.a: $(OBJ)
	$(AR) rcs $@ $(OBJ)
	ranlib $@

bin/libe1l.so.$(VERSION): $(OBJ_SHARED)
	$(CC) -shared -Wl,-soname,libe1l.so.$(SOVERSION) $(OBJ_SHARED) -o $@
	ln -sf libe1l.so.$(VERSION) bin/libe1l.so.$(SOVERSION)
	ln -sf libe1l.so.$(SOVERSION) bin/libe1l.so

clean:
	rm -rf bin
	rm -rf tests/bin

install: bin/libe1l.a bin/libe1l.so.$(VERSION)
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp -f bin/libe1l.a $(DESTDIR)$(PREFIX)/lib/
	cp -f bin/libe1l.so.$(VERSION) $(DESTDIR)$(PREFIX)/lib/
	ln -sf libe1l.so.$(VERSION) $(DESTDIR)$(PREFIX)/lib/libe1l.so.$(SOVERSION)
	ln -sf libe1l.so.$(SOVERSION) $(DESTDIR)$(PREFIX)/lib/libe1l.so
	chmod 755 $(DESTDIR)$(PREFIX)/lib/libe1l.so.$(VERSION)
	cp -f include/e1l.h $(DESTDIR)$(PREFIX)/include/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/libe1l.*
	rm -f $(DESTDIR)$(PREFIX)/include/e1l.h

.PHONY: all clean install uninstall tests
