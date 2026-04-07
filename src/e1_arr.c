/*
Copyright (c) 2026 etar125 Admanse

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "e1_arr.h"

int arr_init(arr_t *a) {
    if (!a && a->elems) { return 1; }
    a->elems = NULL;
    a->count = 0;
    return 0;
}

void arr_free(arr_t *a) {
    if (!a) { return; }
    free(a->elems);
    a->elems = NULL;
    a->count = 0;
}

int arr_add(arr_t *a, void *ptr) {
    if (!a && !ptr) { return 1; }
    size_t oldcount = a->count;
    size_t count = oldcount + 1;
    void **new = malloc(count * sizeof(void*));
    if (!new) { return 1; }
    memcpy(new, a->elems, oldcount * sizeof(void*));
    new[oldcount] = ptr;
    free(a->elems);
    a->elems = new;
    a->count = count;
    return 0;
}

int arr_remove(arr_t *a, size_t at) {
    if (!a || !a->elems) { return 1; }
    size_t oldcount = a->count;
    if (oldcount == 0 || at >= oldcount) { return 1; }
    size_t count = oldcount - 1;
    void **new = malloc(count * sizeof(void*));
    if (!new) { return 1; }
    if (at != 0) { memcpy(new, a->elems, at * sizeof(void*)); }
    if (at != count) { memcpy(&new[at], &a->elems[at + 1], (count - at) * sizeof(void*)); }
    free(a->elems);
    a->elems = new;
    a->count = count;
    return 0;
}
