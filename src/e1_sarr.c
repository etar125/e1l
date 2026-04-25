/*
sarr
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESTRDUP
#include "estrdup.h"
#include "e1l.h"

int sarr_update(sarr *a) {
    size_t ac = 8;
    size_t *ofs = malloc(sizeof(size_t) * 8);
    size_t s = 0, c = 0, i = 0;
    for (; i < a->size; i++) {
        if (a->strs[i] == '\n' || a->strs[i] == '\0') {
            a->strs[i] = '\0';
            ofs[c++] = s;
            if (c == ac) {
                ac += ac / 2;
                ofs = realloc(ofs, sizeof(size_t) * ac);
            }
            s = i + 1;
        }
    }
    if (i != 0) { ofs[c++] = s; }
    if (c < ac) {
        ac = c;
        ofs = realloc(ofs, sizeof(size_t) * ac);
    }
    a->offsets = ofs;
    a->count = ac;
    return 0;
}

sarr sarr_init(char *s, size_t l) {
    sarr ret;
    if (l > 0 && s[l - 1] == '\n') {
        ret.strs = realloc(s, l);
        ret.size = l - 1;
    } else {
        ret.strs = estrdup(s);
        ret.size = l;
    }
    sarr_update(&ret);
    return ret;
}

int sarr_add(sarr *a, char *s, size_t l){
    return -1;
}

int sarr_remove(sarr *a, size_t at){
    return -1;
}

int sarr_insert(sarr *a, char *s, size_t l, size_t at){
    return -1;
}

char* sarr_getstr(sarr *a, size_t at, size_t *outlen) {
    if (at >= a->count) { return NULL; }
    size_t pos = a->offsets[at];
    char *r = &a->strs[pos];
    if (outlen) {
        *outlen = (at < a->count ? a->offsets[at + 1] : a->size) - pos;
    }
    return r;
}
