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
    size_t ac = 8, s = 0, c = 0, i, *ofs = NULL, *nfs = NULL;

    if (!a || !a->strs) { return 1; }

    ofs = malloc(sizeof(size_t) * 8);
    if (!ofs) { return 2; }
    
    for (i = 0; i < a->size; i++) {
        if (a->strs[i] == '\n' || a->strs[i] == '\0') {
            a->strs[i] = '\0';
            ofs[c++] = s;
            if (c == ac) {
                ac += ac / 2;
                nfs = realloc(ofs, sizeof(size_t) * ac);
                if (!nfs) { free(ofs); return 3; }
                ofs = nfs;
                nfs = NULL;
            }
            s = i + 1;
        }
    }
    if (i != 0) { ofs[c++] = s; }
    if (c < ac) {
        nfs = realloc(ofs, sizeof(size_t) * c);
        if (!nfs) { free(ofs); return 4; }
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

int zarr_init(const char *s, size_t l, zarr *out) {
    zarr ret;

    if (!s || !out) { return 1; }
    
    if (l > 0 && s[l - 1] == '\n') {
        ret.strs = estrndupl(s, l - 1, &ret.size);
    } else {
        ret.strs = estrndupl(s, l, &ret.size);
    }
    if (!ret.strs) { return 2; }
    
    ret.offsets = NULL;
    ret.count = 0;
    if (zarr_update(&ret) != 0) { return 3; }
    *out = ret;
    return 0;
}

int zarr_add(zarr *a, const char *s, size_t l) {
    int ret;
    size_t size;
    char *nar;

    if (!a || !s) { return 1; }

    if (!a->strs || a->size == 0) {
        ret = zarr_init(s, l, a);
        return ret == 0 ? 0 : ret + 10;
    } else {
        nar = join(a->strs, a->size, s, l, "\0", 1, &size);
        if (!nar) { return 2; }
        free(a->strs);
        a->strs = nar;
        a->size = size;
        ret = zarr_update(a);
        return ret == 0 ? 0 : ret + 20;
    }
}

int zarr_remove(zarr *a, size_t at) {
    int ret;
    char *strs, *nstrs;
    size_t size, start, end, nsize;

    if (!a || !a->strs || !a->offsets || at >= a->count) { return 1; }
    strs = a->strs;
    size = a->size;

    start = a->offsets[at];
    if (start) { start--; }
    end = size;
    if (at + 1 < a->count) {
        end = a->offsets[at + 1];
    }

    nstrs = join(strs, start, &strs[end], size - end, "\0", 1, &nsize);
    if (!nstrs) { return 2; }
    free(strs);
    a->strs = nstrs;
    a->size = nsize;
    ret = zarr_update(a);
    return ret == 0 ? 0 : ret + 10;
}

int zarr_insert(zarr *a, const char *s, size_t l, size_t at) {
    int ret;
    char *strs, *nstrs;
    size_t size, nsize, pos;

    if (!a || !a->strs || !a->offsets || !s || at >= a->count) { return 1; }
    if (l == 0) { return 0; }
    strs = a->strs;
    size = a->size;
    
    pos = a->offsets[at];
    nsize = size + l + 1;
    nstrs = malloc(nsize + 1);
    /* memset(nstrs, 0, nsize + 1); */
    if (!nstrs) { return 2; }
    memcpy(nstrs, strs, pos);
    memcpy(&nstrs[pos], s, l);
    nstrs[pos + l] = '\0';
    memcpy(&nstrs[pos + l + 1], &strs[pos], size - pos);
    nstrs[nsize] = '\0';
    free(strs);
    a->strs = nstrs;
    a->size = nsize;
    ret = zarr_update(a);
    return ret == 0 ? 0 : ret + 10;
}

char* zarr_getstr(zarr *a, size_t at, size_t *outlen) {
    size_t pos;
    char *r;

    if (!a || !a->strs || !a->offsets || at >= a->count) { return NULL; }
    pos = a->offsets[at];
    r = &a->strs[pos];
    if (outlen) {
        *outlen = (at + 1 < a->count ? a->offsets[at + 1] - 1 : a->size) - pos;
    }
    return r;
}
