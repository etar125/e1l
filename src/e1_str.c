/*
Copyright (c) 2025 etar125

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>
#include "e1_str.h"

str_t readstr() {
    struct termios old_settings, settings;
    tcgetattr(0, &old_settings);
    settings = old_settings;
    settings.c_lflag &= ~(ICANON);
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &settings);
    char c;
    size_t i = 0, size = 32;
    char *str = malloc(32);
    while (1) {
        scanf("%c", &c);
        if (c == '\n') {
            if (i == size) {
                size += 1;
                str = realloc(str, size);
            }
            str[i] = '\0';
            i++;
            break;
        }
        if (i == size) {
            size += size / 2;
            str = realloc(str, size);
        }
        str[i++] = c;
    }
    tcsetattr(0, TCSANOW, &old_settings);
    if (i < size) {
        size = i + 1;
        str = realloc(str, size);
    }
    str_t ret;
    ret.data = str;
    ret.size = size;
    return ret;
}

void reverse(str_t *str) {
    size_t start = 0;
    size_t end = (str->size == 0) ? 0 : str->size - 1;
    while (start < end) {
        char t = str->data[start];
        str->data[start] = str->data[end];
        str->data[end] = t;
        end--, start++;
    } return;
}

#define DEFINE_ITOA(NAME, TYPE, BUFSIZE) \
str_t NAME(TYPE num, int base) { \
    str_t ret; \
    char *str = malloc(BUFSIZE); \
    ret.size = BUFSIZE; \
    int i = 0; \
    bool negative = false; \
    if (num == 0) { \
        str = realloc(str, 2); \
        str[i++] = '0'; \
        str[i] = '\0'; \
        ret.data = str; \
        ret.size = 2; \
        return ret; \
    } \
    if (num < 0 && base == 10) { \
        negative = true; \
        num = -num; \
    } \
    while (num != 0) { \
        TYPE rem = num % base; \
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0'; \
        num = num / base; \
    } \
    if (negative) { str[i++] = '-'; } \
    str[i] = '\0'; \
    size_t actual_size = strlen(str); \
    if (actual_size != 12) { \
        str = realloc(str, actual_size + 1); \
        ret.size = actual_size; \
    } \
    ret.data = str; \
    reverse(&ret); \
    return ret; \
}

DEFINE_ITOA(itoa, int, 33)
DEFINE_ITOA(utoa, unsigned int, 33)
DEFINE_ITOA(ltoa, long long, 65)
DEFINE_ITOA(ultoa, unsigned long long, 65)

str_t cstr_to_str(char *str, bool dup) {
    str_t ret;
    ret.data = NULL;
    if (!str) { return ret; }
    ret.size = strlen(str);
    if (dup) { ret.data = strdup(str); }
    else { ret.data = str; }
    return ret;
}

str_t join(str_t *str1, str_t *str2, char with, bool free_strs) {
    str_t ret;
    ret.data = NULL;
    ret.size = 0;
    char  *data1 = str1->data,
          *data2 = str2->data;
    size_t size1 = str1->size,
           size2 = str2->size;
    size_t size_new = size1 + size2;
    char *data_new = malloc(with ? size_new + 2 : size_new + 1);
    if (!data_new) { return ret; }
    memcpy(data_new, data1, size1);
    if (with) data_new[size1] = with;
    memcpy(data_new + size1 + (with ? 1 : 0), data2, size2);
    data_new[with ? size_new + 1 : size_new] = '\0';
    ret.data = data_new;
    ret.size = size_new;
    if (free_strs) {
        free(data1);
        free(data2);
        str1->data = NULL,
        str2->data = NULL,
        str1->size = 0,
        str2->size = 0;
    } return ret;
}
