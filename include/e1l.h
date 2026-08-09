/*
Copyright (c) 2026 etar125 Admanse

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef E1L_H
#define E1L_H

#include <stddef.h>

/* str */

/* s1 - main string */

char* readstr(size_t *outlen);
void reverse(char *s, size_t l);
char* join(const char *s1, size_t l1, const char *s2, size_t l2, char *with, size_t wl,
           size_t *outlen);
char* insert(const char *s1, size_t l1, const char *s2, size_t l2, size_t at, size_t *outlen);

/* dynamic str */

/* asize - actual size
 * bsize - buffer size */

int d_append(char **ds, size_t *asize, size_t *bsize, const char *s, size_t l);
char* d_shrink(const char *ds, size_t asize, size_t bsize);

/* zarr */

typedef struct {
    char *strs;
    size_t size;
    size_t *offsets;
    size_t count;
} zarr;

zarr zarr_empty();
zarr zarr_init(const char *s, size_t l);
int zarr_update(zarr *a);
int zarr_add(zarr *a, const char *s, size_t l);
int zarr_remove(zarr *a, size_t at);
int zarr_insert(zarr *a, const char *s, size_t l, size_t at);
char* zarr_getstr(zarr *a, size_t at, size_t *outlen);

/* sarr */

size_t sarr_count(char *sarr, size_t sarrlen);
int sarr_add(char **sarr, size_t *sarrlen, char *str, size_t len);
int sarr_remove(char **sarr, size_t *sarrlen, size_t at);
char* sarr_getdup(char *sarr, size_t sarrlen, size_t at, size_t *outlen);
int sarr_insert(char **sarr, size_t *sarrlen, size_t at, char *str, size_t len);
int sarr_normalize(char **sarr, size_t *sarrlen);

#endif
