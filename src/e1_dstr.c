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
    size_t as, bs;
    char *nds;

    if (!s || l == 0) { return 0; }
    if (!ds || !asize || !bsize) { return 1; }
    as = *asize, bs = *bsize;
    if (as > bs) { return 2; }
    
    if (bs == 0) { bs = 32; }
    while (as + l >= bs) {
        bs += bs / 2;
    }
    nds = realloc(*ds, bs);
    if (!nds) { return 3; }
    memcpy(&nds[as], s, l);
    as += l;
    nds[as] = '\0';
    *ds = nds;
    *asize = as;
    *bsize = bs;
    return 0;
}

char* d_shrink(const char *ds, size_t asize, size_t bsize) {
    char *ret;

    if (!ds || asize > bsize) { return NULL; }
    ret = malloc(asize + 1);
    if (!ret) { return NULL; }
    memcpy(ret, ds, asize);
    ret[asize] = '\0';
    return ret;
}
