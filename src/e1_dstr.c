/*
Copyright (c) 2026 etar125 Admanse

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "e1_str.h"
#include "e1_dstr.h"

dstr_t emptydstr() {
    dstr_t ret;
    ret.data = NULL;
    ret.buffsize = ret.pointer = 0;
    return ret;
}

str_t dstr_to_str(dstr_t *str, bool free_dstr) {
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
    if (free_dstr) {
        free(from);
        str->data = NULL;
        str->buffsize = str->pointer = 0;
    }
    return ret;
}

int d_addch(dstr_t *str, char ch) {
    if (!str) { return 1; }
    char *buf = str->data;
    size_t size = str->buffsize;
    size_t i = str->pointer;
    if (i > size) { return 1; }
    if (i == size) {
        size_t old = size;
        char *obuf = buf;
        size *= 2;
        if (size == 0) { size = 1; }
        buf = malloc(size + 1);
        if (!buf) { return 1; }
        memcpy(buf, obuf, old);
        buf[size] = '\0';
        free(obuf);
    }
    buf[i++] = ch;
    buf[i] = '\0';
    str->data = buf;
    str->buffsize = size;
    str->pointer = i;
    return 0;
}

int d_addstr(dstr_t *str, str_t *add) {
    if (!str || !add) { return 1; }
    str_t a;
    a.data = str->data;
    a.size = str->pointer;
    str_t res = join(&a, add, 0, false);
    if (!res.data) { return 1; }
    free(str->data);
    size_t newsize = str->buffsize + 1;
    while (newsize <= res.size) { newsize *= 2; }
    str->buffsize = newsize;
    str->pointer = res.size;
    str->data = malloc(newsize + 1);
    if (!str->data) { free(res.data); return 1; }
    memcpy(str->data, res.data, res.size);
    str->data[res.size] = '\0';
    str->data[newsize] = '\0';
    return 0;
}

int d_addcstr(dstr_t *str, char *add) {
    if (!str || !add) { return 1; }
    str_t a;
    a.data = add;
    a.size = strlen(add);
    return d_addstr(str, &a);
}
