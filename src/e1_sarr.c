/*
sarr
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estrdup.h"
#include "e1l.h"

size_t sarr_count(char *sarr, size_t sarrlen) {
    size_t count = 0, i;
    if (sarrlen == 0) { return 0; }
    for (i = 0; i < sarrlen; i++) {
        if (sarr[i] == '\n') { count++; }
    } return count;
}

int sarr_add(char **sarr, size_t *sarrlen, char *str, size_t len);

int sarr_remove(char **sarr, size_t *sarrlen, size_t at);

char* sarr_getdup(char *sarr, size_t sarrlen, size_t at, size_t *outlen);

int sarr_insert(char **sarr, size_t *sarrlen, size_t at, char *str, size_t len);
