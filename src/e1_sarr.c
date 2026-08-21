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
    if (!sarr || sarrlen == 0) { return 0; }
    for (i = 0; i < sarrlen; i++) {
        if (sarr[i] == '\n') { count++; }
    } return count;
}

int sarr_add(char **sarr, size_t *sarrlen, char *str, size_t len) {
    char *new = NULL, old = NULL;
    size_t newlen = 0, oldlen = 0;

    if (!str || len == 0) { return 0; }
    if (!sarr || !sarrlen) { return 1; }

    old = *sarr, oldlen = *sarrlen;
    
    if (!old || old == 0) {
        old = estrndupl(str, len, sarrlen);
        if (!old) { return 2; }
        *sarr = old;
        return 0;
    }
    new = join(old, oldlen, str, len, "\n", 1, &newlen);
    if (!new) { return 3; }
    free(old);
    *sarr = new;
    *sarrlen = newlen;
    return 0;
}

int sarr_remove(char **sarr, size_t *sarrlen, size_t at) {
    char *oa = NULL, *na = NULL, *p2 = NULL;
    size_t ol = NULL, nl = 0, l1 = 0, l2 = 0,
        cur = 0, i;

    if (!sarr || !sarrlen) { return 1; }
    oa = *sarr, ol = *sarrlen;
    if (!oa || ol == 0) { return 2; }

    for (i = 0; i < ol && cur != at; i++) {
        if (oa[i] == '\n') { cur++; }
    }
    if (i == ol || cur != at) { return 3; }
    l1 = i != 0 ? i - 1 : i;
    for (; i < ol && oa[i] != '\n'; i++);
    i++;
    if (i >= ol) {
        if (l1 == 0) {
            *sarr = NULL;
            *sarrlen = 0;
        } else {
            na = malloc(l1 + 1);
            if (!na) { return 4; }
            memcpy(na, oa, l1);
            na[l1] = '\0';
            free(oa);
            *sarr = na;
            *sarrlen = l1;
        } return 0;
    }
    p2 = oa + i;
    l2 = ol - i;
    na = join(oa, l1, p2, l2, "\n", 1, &nl);
    if (!na) { return 5; }
    free(oa);
    *sarr = na;
    *sarrlen = nl;
    return 0;
}

char* sarr_getdup(char *sarr, size_t sarrlen, size_t at, size_t *outlen) {
    char *s = NULL;
    size_t l = 0, cur = 0, i, start;

    if (!sarr || sarrlen == 0) { return NULL; }

    for (i = 0; i < sarrlen && cur != at; i++) {
        if (sarr[i] == '\n') { cur++; }
    }
    if (i >= sarrlen || cur != at) { return NULL; }
    start = i;
    for (; i < sarrlen && sarr[i] != '\n'; i++);
    l = i - start;
    s = malloc(l + 1);
    if (!s) { return NULL; }
    memcpy(s, sarr + start, l);
    s[l] = '\0';
    if (outlen) { *outlen = l; }
    return s;
}

int sarr_insert(char **sarr, size_t *sarrlen, size_t at, char *str, size_t len) {
    char *oa = NULL, *na = NULL, *ka;
    size_t ol = NULL, nl = 0, i, cur = 0;

    if (!sarr || !sarrlen || !str || len == 0) { return 1; }
    oa = *sarr, ol = *sarrlen;
    if (!oa || ol == 0) { return 2; }

    for (i = 0; i < ol && cur != at; i++) {
        if (oa[i] == '\n') { cur++; }
    }
    if (i >= ol || cur != at) { return 3; }
    nl = ol + len + 1;
    na = malloc(nl + 1);
    if (!na) { return 4; }
    ka = na;
    memcpy(ka, oa, i);
    ka += i;
    memcpy(ka, str, len);
    ka += len;
    ka[0] = '\n';
    memcpy(ka + 1, oa + i, ol - i);
    na[nl] = '\0';

    free(oa);
    *sarr = na;
    *sarrlen = nl;
    return 0;
}

int sarr_normalize(char **sarr, size_t *sarrlen) {
    char *oa = *sarr, *na = NULL;
    size_t ol = *sarrlen, i, j;

    if (!oa || ol == 0) { return 1; }

    for (i = 0, j = 0; i < ol; i++, j++) {
        if (oa[i] == '\n') {
            for (; i < ol && oa[i] == '\n'; i++);
            if (i == ol) { break; }
            oa[j] = '\n';
            i--;
        } else if (i != j) { oa[j] = oa[i]; }
    }

    na = malloc(j + 1);
    if (!na) { return 1; }
    memcpy(na, oa, j);
    na[j] = '\0';
    free(oa);

    *sarr = na;
    *sarrlen = j;

    return 0;
}

size_t sarr_getpos(char *sarr, size_t sarrlen, size_t at) {
    size_t cur = 0, i;

    if (!sarr || sarrlen == 0) { return 0; }

    for (i = 0; i < sarrlen && cur != at; i++) {
        if (sarr[i] == '\n') { cur++; }
    }
    return i;
}
