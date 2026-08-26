VERSION = 0.6.2
SOVERSION = 1

PREFIX = /usr/local

ECFLAGS = -Iinclude -std=c99 -pedantic -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -Wall -Wextra $(CFLAGS)

CC = cc
AR = ar
