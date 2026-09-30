#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estrdup.h"
#include "e1l.h"

int main(void) {
    char *input = NULL, *dup = NULL, *joined = NULL, *inserted = NULL, **splitted = NULL;
    size_t inputlen, joinedlen, insertedlen, splittedcount, i;
    puts("=== e1_str test ===");
    printf("Type something: ");
    input = readstr(&inputlen);
    dup = estrdup(input);
    reverse(input, inputlen);
    joined = join(input, inputlen, dup, inputlen, ", ", 2, &joinedlen);
    inserted = insert(joined, joinedlen, ", UwU", 5, inputlen, &insertedlen);
    if (split(inserted, insertedlen, ", ", 2, &splitted, &splittedcount) != 0) {
        perror("split failed");
        return 1;
    }
    printf("%s\n%s\ncount: %lu\n", joined, inserted, splittedcount);
    for (i = 0; i < splittedcount; i++) {
        printf("%s\n", splitted[i]);
    }
    free(input);
    free(dup);
    free(joined);
    free(inserted);
    free(splitted);
    return 0;
}
