# Copyright (c) 2026 etar125 Admanse
# Licensed under ISC (see LICENSE)

include config.mk

SRC = src/e1_str.c src/e1_sarr.c src/e1_dstr.c
OBJ = $(SRC:src/%.c=bin/%.o)
TSRC = tests/str_test.c tests/sarr_test.c tests/dstr_test.c
TEXE = $(TSRC:tests/%.c=tests/bin/%)

all: bin/libe1l.a bin/libe1l.so tests

tests: $(TEXE)

tests/bin/%: tests/%.c $(OBJ) include/e1l.h config.mk
	@mkdir -p tests/bin
	$(CC) $(ECFLAGS) $(OBJ) $< -o $@

bin/%.o: src/%.c include/e1l.h config.mk
	@mkdir -p bin
	$(CC) $(ECFLAGS) -c $< -o $@

bin/libe1l.a: $(OBJ)
	$(AR) rcs $@ $(OBJ)
	ranlib $@

bin/libe1l.so: $(OBJ)
	$(CC) -shared $(OBJ) -o $@

clean:
	rm -rf bin
	rm -rf tests/bin

install: bin/libe1l.a bin/libe1l.so
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp -f bin/libe1l.a $(DESTDIR)$(PREFIX)/lib/
	cp -f bin/libe1l.so $(DESTDIR)$(PREFIX)/lib/
	chmod 744 $(DESTDIR)$(PREFIX)/lib/libe1l.so
	cp -f include/e1l.h $(DESTDIR)$(PREFIX)/include/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/libe1l.a
	rm -f $(DESTDIR)$(PREFIX)/lib/libe1l.so
	rm -f $(DESTDIR)$(PREFIX)/include/e1l.h

.PHONY: all clean install uninstall tests
