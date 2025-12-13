#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "e1_sarr.h"
#include "e1_str.h"

int main(void) {
    printf("--- e1_sarr test ---\n");
    str_t sarr = cstr_to_str("123\n456\n789", true);
    printf("count %s 3\n", sarr_count(&sarr) != 3 ? "!=" : "==");
    str_t to_add = cstr_to_str("012", true);
    sarr_add(&sarr, &to_add);
    printf("count %s 4\n", sarr_count(&sarr) != 4 ? "!=" : "==");
    printf("Added %s\n%s\n", to_add.data, sarr.data);
    free(to_add.data);
    free(sarr.data);
    return 0;
}
