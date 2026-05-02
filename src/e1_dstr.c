/*
dynamic str
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

int d_append(char **ds, size_t *asize, size_t *bsize, const char *s, size_t l) {
    if (!s || l == 0) { return 0; }
    if (!ds || !asize || !bsize || *asize > *bsize) { return 1; }
    size_t as = *asize, bs = *bsize;
    if (bs == 0) { bs = 32; }
    while (as + l >= bs) {
        bs += bs / 2;
    }
    char *nds = realloc(*ds, bs);
    if (!nds) { return 1; }
    memcpy(&nds[as], s, l);
    as += l;
    nds[as] = '\0';
    *ds = nds;
    *asize = as;
    *bsize = bs;
    return 0;
}

char* d_shrink(char *ds, size_t asize, size_t bsize) {
    if (!ds || asize > bsize) { return NULL; }
    char *ret = malloc(asize + 1);
    if (!ret) { return NULL; }
    memcpy(ret, ds, asize);
    ret[asize] = '\0';
    return ret;
}
