#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "e1l.h"

#define EC(x) if (x != 0) { printf("error! %d\n", callcount); } callcount += 1;

int main(void) {
    int callcount = 1;
    char *ds = NULL, *s = NULL;
    size_t asize = 0, bsize = 0;
    puts("=== e1_dstr test ===");
    EC(d_append(&ds, &asize, &bsize, "Hello", 5))
    printf("%s\n", ds);
    EC(d_append(&ds, &asize, &bsize, ", World!", 8))
    s = d_shrink(ds, asize, bsize);
    printf("%s\n%s\n", ds, s);
    free(ds);
    free(s);
    return 0;
}
