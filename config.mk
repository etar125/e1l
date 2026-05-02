PREFIX = /usr/local

ECFLAGS = -Iinclude -std=c99 -pedantic -D_XOPEN_SOURCE=700 -Wall $(CFLAGS)

CC = cc
AR = ar
