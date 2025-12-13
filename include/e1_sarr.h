/*
Copyright (c) 2025 etar125

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef E1_SARR_H
#define E1_SARR_H

#include "e1_str.h"
#include <stddef.h>

size_t sarr_count(str_t *sarr);
int sarr_add(str_t *sarr, str_t *str);
int sarr_remove(str_t *sarr, size_t at);
str_t sarr_getdup(str_t *sarr, size_t at);
int sarr_insert(str_t *sarr, size_t at, str_t *str);
int sarr_join(str_t *sarr1, str_t *sarr2);

#endif
