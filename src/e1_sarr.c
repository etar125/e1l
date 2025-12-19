/*
Copyright (c) 2025 etar125

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "e1_sarr.h"
#include "e1_str.h"

size_t sarr_count(str_t *sarr) {
    char *a = sarr->data;
    if (sarr->size == 0) { return 0; }
    size_t count = 1;
    while (*a) {
        if (*a++ == '\n') { count++; }
    } return count;
}

int sarr_add(str_t *sarr, str_t *str) {
    if (sarr->size == 0) {
        sarr->data = strdup(str->data);
        if (!sarr->data) { return 1; }
        sarr->size = str->size;
        return 0;
    }
    str_t new = join(sarr, str, '\n', false);
    if (!new.data) { return 1; }
    free(sarr->data);
    sarr->data = new.data;
    sarr->size = new.size;
    return 0;
}

static void printstr(str_t str) {
    putchar('X');
    for (size_t i = 0; i < str.size; i++) {
        putchar(str.data[i] == '\n' ? 'A' : str.data[i]);
    } printf("X\n");
}   

int sarr_remove(str_t *sarr, size_t at) {
    size_t count = sarr_count(sarr);
    if (count == 0 || at >= count) { return 1; }
    char *str = sarr->data;
    size_t size = sarr->size;
    str_t s1, s2;
    size_t i = 0, end, start2 = 0;
    size_t current = 0;
    while (i < size && current != at) {
        while (i < size && str[i] != '\n' && str[i] != '\0') {
            i++;
        }
        if (i < size && str[i] == '\n') {
            i++;
        }
        current++;
    }
    if (i == size || current != at) { return 1; }
    end = i > 0 ? i - 1 : i;
    while (i < size && str[i] != '\n' && str[i] != '\0') {
        i++;
    }
    if (i < size && str[i] == '\n') {
        i++;
    }
    start2 = i;
    s1.data = str;
    s1.size = end;
    s2.data = &str[start2];
    s2.size = size - start2;
    str_t new;
    if (s1.size == 0) {
        new.data = malloc(s2.size + 1);
        if (!new.data) { return 1; }
        new.size = s2.size;
        memcpy(new.data, s2.data, s2.size);
        new.data[new.size] = '\0';
    } else if (s2.size == 0) {
        new.data = malloc(s1.size + 1);
        if (!new.data) { return 1; }
        new.size = s1.size;
        memcpy(new.data, s1.data, s1.size);
        new.data[new.size] = '\0';
    } else {
        new = join(&s1, &s2, '\n', false);
        if (!new.data) { return 1; }
    }
    free(str);
    sarr->data = new.data;
    sarr->size = new.size;
    return 0;
}
