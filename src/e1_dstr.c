/*
Copyright (c) 2026 etar125

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "e1_dstr.h"

dstr_t emptydstr() {
    dstr_t ret;
    ret.data = NULL;
    ret.buffsize = ret.pointer = 0;
    return ret;
}

str_t dstr_to_str(dstr_t *str, bool free) {
    str_t ret;
    ret.data = NULL;
    ret.size = 0;
    if (!str) { return ret; }
    char *from = str->data;
    size_t size = str->pointer;
    if (!from || size == 0) { return ret; }
    char *data = malloc(size + 1);
    if (!data) { return ret; }
    memcpy(data, from, size);
    data[size] = '\0';
    ret.data = data;
    ret.size = size;
    if (free) {
        free(from);
        str->data = NULL;
        str->buffsize = str->pointer = 0;
    }
    return ret;
}

int d_addch(dstr_t *str, char ch) {
    if (!str) { return 1; }
    char *buf = str->data;
    size_t size = str->size;
    size_t i = str->pointer;
    if (!buf || i > size) { return 1; }
    if (i == size) {
        size_t old = size;
        char *obuf = buf;
        size *= 2;
        if (size == 0) { size = 1; }
        buf = malloc(size + 1);
        if (!buf) { return 1; }
        memcpy(buf, obuf, old);
        buf[size] = '\0';
    }
    buf[i++] = ch;
    buf[i] = '\0';
    return 0;
}
