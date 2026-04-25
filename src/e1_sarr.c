/*
sarr
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESTRDUP
#define ESTRNDUPL
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
    if (a->offsets) { free(a->offsets); }
    a->offsets = ofs;
    a->count = ac;
    return 0;
}

sarr sarr_empty() {
    sarr ret;
    ret.strs = NULL;
    ret.size = 0;
    ret.offsets = NULL;
    ret.count = 0;
    return ret;
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
    ret.offsets = NULL;
    ret.count = 0;
    sarr_update(&ret);
    return ret;
}

int sarr_add(sarr *a, char *s, size_t l) {
    size_t size;
    if (!a->strs || a->size == 0) {
        a->strs = estrndupl(s, l, &size);
        if (!a->strs) { return 1; }
        a->size = size;
    } else {
        char *nar = join(a->strs, a->size, s, l, "\0", 1, &size);
        if (!nar) { return 1; }
        free(a->strs);
        a->strs = nar;
        a->size = size;
    }
    return sarr_update(a);
}

int sarr_remove(sarr *a, size_t at) {
    if (at > a->count) { return 1; }
    char *strs = a->strs;
    size_t size = a->size;

    size_t start = a->offsets[at];
    if (start) { start--; }
    size_t end = size;
    if (at + 1 < a->count) {
        end = a->offsets[at + 1];
    }
    
    size_t nsize;
    char *nstrs = join(strs, start, &strs[end], size - end, "\0", 1, &nsize);
    if (!nstrs) { return 1; }
    free(strs);
    a->strs = nstrs;
    a->size = nsize;
    return sarr_update(a);
}

int sarr_insert(sarr *a, char *s, size_t l, size_t at){
    if (!s || l == 0) { return 0; } /* не прям чтобы ошибка */
    if (at > a->count) { return 1; }
    char *strs = a->strs;
    size_t size = a->size;
    
    size_t pos = a->offsets[at];
    size_t nsize = size + l + 1;
    char *nstrs = malloc(nsize + 1);
    //memset(nstrs, 0, nsize + 1);
    if (!nstrs) { return 1; }
    memcpy(nstrs, strs, pos);
    memcpy(&nstrs[pos], s, l);
    nstrs[pos + l] = '\0';
    memcpy(&nstrs[pos + l + 1], &strs[pos], size - pos);
    nstrs[nsize] = '\0';
    free(strs);
    a->strs = nstrs;
    a->size = nsize;
    return sarr_update(a);
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
