#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESTRDUP
#include "estrdup.h"
#include "e1l.h"

int main(void) {
    size_t len, jjlen;
    char *text, *pre, *jj, *ii;
    puts("=== e1_str test ===");
    printf("Type something: ");
    text = readstr(&len);
    pre = estrdup(text);
    reverse(text, len);
    jj = join(text, len, pre, len, ", ", 2, &jjlen);
    ii = insert(jj, jjlen, ", UwU", 5, len, NULL);
    printf("%s\n%s\n", jj, ii);
    free(text);
    free(pre);
    free(jj);
    free(ii);
    return 0;
}
