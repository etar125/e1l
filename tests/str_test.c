#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

int main(void) {
    puts("=== e1_str test ===");
    printf("Type something: ");
    char *text = readstr(NULL);
    printf("%s\n", text);
    reverse(text, strlen(text));
    printf("%s\n", text);

    free(text);
    return 0;
}
