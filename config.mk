VERSION = 0.5.5
SOVERSION = 0

PREFIX = /usr/local

ECFLAGS = -Iinclude -std=c99 -pedantic -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -Wall -Wextra $(CFLAGS)

CC = cc
AR = ar
