#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

int main(void) {
    puts("=== e1_str test ===");
    printf("Type something: ");
    size_t len;
    char *text = readstr(&len);
    char *pre = strdup(text);
    reverse(text, len);
    char *jj = join(text, len, pre, len, ", ", 2, NULL);
    printf("%s\n", jj);
    free(text);
    free(pre);
    return 0;
}
