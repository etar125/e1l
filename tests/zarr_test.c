#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

#define EC(x) if (x != 0) { printf("error! %d\n", callcount); } callcount += 1;

int main(void) {
    int callcount = 1;
    char *basa = "Hello 1\n\
Hello 2\n\
Hello 3\n\
Hello 4\n\
Hello 5";
    zarr a = zarr_empty();
    puts("=== e1_zarr test ===");
    EC(zarr_init(basa, strlen(basa), &a));
    printf("3: %s\n", zarr_getstr(&a, 2, NULL));
    printf("5: %s\n", zarr_getstr(&a, 4, NULL));
    EC(zarr_add(&a, "Hello 6", strlen("Hello 6")))
    printf("6: %s\n", zarr_getstr(&a, 5, NULL));
    EC(zarr_remove(&a, 1))
    printf("2: %s\n", zarr_getstr(&a, 1, NULL));
    EC(zarr_insert(&a, "Hello 2 (again!!)", strlen("Hello 2 (again!!)"), 1))
    printf("2: %s\n", zarr_getstr(&a, 1, NULL));
    free(a.strs);
    free(a.offsets);
    return 0;
}
