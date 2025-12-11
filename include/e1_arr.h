/*
Copyright (c) 2025 etar125

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef E1_ARR_H
#define E1_ARR_H

#include <stddef.h>

typedef struct {
    void **elems;
    size_t count;
} arr_t;

int arr_init(arr_t *a);
int arr_add(arr_t *a, void *ptr);
int arr_insert(arr_t *a, size_t at, void *ptr);
int arr_remove(arr_t *a, size_t at);
void arr_free(arr_t *a);

#endif
