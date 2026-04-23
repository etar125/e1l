/*
sarr
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include "e1l.h"

sarr sarr_init(char *s, size_t l) {
    sarr ret;
    ret.strs = NULL;
    ret.offsets = NULL;
    ret.count = 0;
    return ret;
}

int sarr_update(sarr *a) {
    return -1;
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

char* sarr_getstr(sarr *a, size_t at){
    return NULL;
}
