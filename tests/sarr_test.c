#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

#define EC(x) if (x != 0) { printf("error! %d\n", callcount); } callcount += 1;

int main(void) {
    int callcount = 1;
    puts("=== e1_sarr test ===");
    char *basa = "Hello 1\n\
Hello 2\n\
Hello 3\n\
Hello 4\n\
Hello 5";
    sarr a = sarr_init(basa, strlen(basa));
    printf("3: %s\n", sarr_getstr(&a, 2, NULL));
    printf("5: %s\n", sarr_getstr(&a, 4, NULL));
    EC(sarr_add(&a, "Hello 6", strlen("Hello 6")))
    printf("6: %s\n", sarr_getstr(&a, 5, NULL));
    EC(sarr_remove(&a, 1))
    printf("2: %s\n", sarr_getstr(&a, 1, NULL));

    free(a.strs);
    free(a.offsets);
    return 0;
}
