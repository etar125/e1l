#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESTRDUP
#include "estrdup.h"
#include "e1l.h"

int main(void) {
    puts("=== e1_str test ===");
    printf("Type something: ");
    size_t len;
    char *text = readstr(&len);
    char *pre = estrdup(text);
    reverse(text, len);
    size_t jjlen;
    char *jj = join(text, len, pre, len, ", ", 2, &jjlen);
    char *ii = insert(jj, jjlen, ", UwU", 5, len, NULL);
    printf("%s\n%s\n", jj, ii);
    free(text);
    free(pre);
    free(jj);
    free(ii);
    return 0;
}
