# Copyright (c) 2026 etar125 Admanse
# Licensed under ISC (see LICENSE)
.POSIX:

include config.mk

SRC = src/e1_str.c src/e1_sarr.c src/e1_dstr.c
OBJ = $(SRC:src/%.c=bin/%.o)

all: bin/libe1l.a

bin/%.o: src/%.c include/e1l.h config.mk
	@mkdir -p bin
	$(CC) $(ECFLAGS) -c $< -o $@

bin/libe1l.a: $(OBJ)
	$(AR) rcs $@ $(OBJ)
	ranlib $@

clean:
	rm -rf bin

install: libe1l.a
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp -f bin/libe1l.a $(DESTDIR)$(PREFIX)/lib/
	cp -f include/e1l.h $(DESTDIR)$(PREFIX)/include/

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/libe1l.a
	rm -f $(DESTDIR)$(PREFIX)/include/e1l.h

.PHONY: all clean install uninstall
