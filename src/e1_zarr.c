/*
zarr
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estrdup.h"
#include "e1l.h"

int zarr_update(zarr *a) {
    size_t ac = 8, s = 0, c = 0, i = 0, *ofs;

    ofs = malloc(sizeof(size_t) * 8);
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
        ofs = realloc(ofs, sizeof(size_t) * c);
    }
    if (a->offsets) { free(a->offsets); }
    a->offsets = ofs;
    a->count = c;
    return 0;
}

zarr zarr_empty() {
    zarr ret;
    ret.strs = NULL;
    ret.size = 0;
    ret.offsets = NULL;
    ret.count = 0;
    return ret;
}

zarr zarr_init(const char *s, size_t l) {
    zarr ret;
    if (l > 0 && s[l - 1] == '\n') {
        ret.strs = estrndupl(s, l - 1, &ret.size);
    } else {
        ret.strs = estrndupl(s, l, &ret.size);
    }
    ret.offsets = NULL;
    ret.count = 0;
    zarr_update(&ret);
    return ret;
}

int zarr_add(zarr *a, const char *s, size_t l) {
    size_t size;
    char *nar;

    if (!a->strs || a->size == 0) {
        *a = zarr_init(s, l);
        return 0;
    } else {
        nar = join(a->strs, a->size, s, l, "\0", 1, &size);
        if (!nar) { return 1; }
        free(a->strs);
        a->strs = nar;
        a->size = size;
        return zarr_update(a);
    }
}

int zarr_remove(zarr *a, size_t at) {
    char *strs, *nstrs;
    size_t size, start, end, nsize;

    if (at > a->count) { return 1; }
    strs = a->strs;
    size = a->size;

    start = a->offsets[at];
    if (start) { start--; }
    end = size;
    if (at + 1 < a->count) {
        end = a->offsets[at + 1];
    }

    nstrs = join(strs, start, &strs[end], size - end, "\0", 1, &nsize);
    if (!nstrs) { return 1; }
    free(strs);
    a->strs = nstrs;
    a->size = nsize;
    return zarr_update(a);
}

int zarr_insert(zarr *a, const char *s, size_t l, size_t at){
    char *strs, *nstrs;
    size_t size, nsize, pos;

    if (!s || l == 0) { return 0; } /* не прям чтобы ошибка */
    if (at > a->count) { return 1; }
    strs = a->strs;
    size = a->size;
    
    pos = a->offsets[at];
    nsize = size + l + 1;
    nstrs = malloc(nsize + 1);
    /* memset(nstrs, 0, nsize + 1); */
    if (!nstrs) { return 1; }
    memcpy(nstrs, strs, pos);
    memcpy(&nstrs[pos], s, l);
    nstrs[pos + l] = '\0';
    memcpy(&nstrs[pos + l + 1], &strs[pos], size - pos);
    nstrs[nsize] = '\0';
    free(strs);
    a->strs = nstrs;
    a->size = nsize;
    return zarr_update(a);
}

char* zarr_getstr(zarr *a, size_t at, size_t *outlen) {
    size_t pos;
    char *r;

    if (at >= a->count) { return NULL; }
    pos = a->offsets[at];
    r = &a->strs[pos];
    if (outlen) {
        *outlen = (at + 1 < a->count ? a->offsets[at + 1] - 1 : a->size) - pos;
    }
    return r;
}
