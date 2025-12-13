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
    size_t new_size = sarr->size + str->size + 1;
    char *new = malloc(new_size + 1);
    if (!new) { return 1; }
    memcpy(new, sarr->data, sarr->size);
    new[sarr->size] = '\n';
    memcpy(new + sarr->size + 1, str->data, str->size);
    new[new_size] = '\0';
    free(sarr->data);
    sarr->data = new;
    sarr->size = new_size;
    return 0;
}
