#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

int main(void) {
    puts("=== e1_sarr test ===");
    char *basa = "Hello 1\n\
Hello 2\n\
Hello 3\n\
Hello 4\n\
Hello 5";
    sarr a = sarr_init(basa, strlen(basa));
    printf("3: %s\n", sarr_getstr(&a, 2, NULL));
    printf("5: %s\n", sarr_getstr(&a, 4, NULL));

    free(a.strs);
    free(a.offsets);
    return 0;
}
