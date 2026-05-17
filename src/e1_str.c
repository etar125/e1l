/*
str
Copyright (c) 2026 etar125 Admanse
Licensed under ISC (see LICENSE)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "e1l.h"

char* readstr(size_t *outlen) {
    struct termios old_settings, settings;
    char c, *str;
    size_t i = 0, size = 32;

    tcgetattr(0, &old_settings);
    settings = old_settings;
    settings.c_lflag &= ~(ICANON);
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &settings);
    str = malloc(32);
    while (1) {
        scanf("%c", &c);
        if (c == '\n') {
            if (i == size) {
                size += 1;
                str = realloc(str, size);
            }
            str[i] = '\0';
            break;
        }
        if (i == size) {
            size += size / 2;
            str = realloc(str, size);
        }
        str[i++] = c;
    }
    tcsetattr(0, TCSANOW, &old_settings);
    if (i + 1 < size) {
        str = realloc(str, i + 1);
        str[i] = '\0';
    }
    if (outlen) { *outlen = i; }
    return str;
}

void reverse(char *s, size_t l) {
    size_t start = 0;
    size_t end = (l == 0) ? 0 : l - 1;
    char t;

    while (start < end) {
        t = s[start];
        s[start] = s[end];
        s[end] = t;
        end--, start++;
    } return;
}

char* join(const char *s1, size_t l1, const char *s2, size_t l2, char *with, size_t wl,
           size_t *outlen) {
    char *ret = NULL;
    size_t len = l1 + l2 + (with ? wl : 0);
    ret = malloc(len + 1);
    if (!ret) { return NULL; }
    memcpy(ret, s1, l1);
    if (with) {
        memcpy(ret + l1, with, wl);
    }
    memcpy(ret + l1 + (with ? wl : 0), s2, l2);
    ret[len] = '\0';
    if (outlen) { *outlen = len; }
    return ret;
}

char* insert(const char *s1, size_t l1, const char *s2, size_t l2, size_t at, size_t *outlen) {
    size_t size;
    char *ret;

    if (!s1 || !s2 || at > l1) { return NULL; }
    size = l1 + l2;
    ret = malloc(size + 1);
    if (!ret) { return NULL; }
    memcpy(ret, s1, at);
    memcpy(&ret[at], s2, l2);
    memcpy(&ret[at + l2], &s1[at], l1 - at);
    ret[size] = '\0';
    if (outlen) { *outlen = size; }
    return ret;
}
