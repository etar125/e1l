/* SPDX-License-Identifier: FSFAP */
/*
 * Copyright (c) 2026 etar125 Admanse
 *
 * Copying and distribution of this file, with or without modification, are permitted in any medium without royalty, provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.
 */

#ifndef ESTRDUP_H
#define ESTRDUP_H

#include <stddef.h>

char* estrdup(const char *s);
char* estrdupl(const char *s, size_t *outlen);
char* estrndup(const char *s, size_t n);
char* estrndupl(const char *s, size_t n, size_t *outlen);

#endif
