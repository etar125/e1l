#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "e1_sarr.h"
#include "e1_str.h"

#define CHECK(x) if (x != 0) { printf("Fail:"); }

int main(void) {
    printf("--- e1_sarr test ---\n");
    str_t sarr = cstr_to_str("123\n456\n789", true);
    printf("count %s 3\n", sarr_count(&sarr) != 3 ? "!=" : "==");
    str_t to_add = cstr_to_str("012", true);
    str_t to_add2 = cstr_to_str("345", true);
    str_t to_add3 = cstr_to_str("999", true);
    str_t to_add4 = cstr_to_str("888", true);
    str_t to_add5 = cstr_to_str("777", true);
    CHECK(sarr_add(&sarr, &to_add))
    printf("count %s 4\n", sarr_count(&sarr) != 4 ? "!=" : "==");
    printf("Added %s\n%s\n", to_add.data, sarr.data);
    printf("size %zu %s 15\n", sarr.size, sarr.size == 15 ? "==" : "!=");
    CHECK(sarr_remove(&sarr, 0))
    printf("Removed first element\n%s\n", sarr.data);
    CHECK(sarr_remove(&sarr, 1))
    printf("Removed second element\n%s\n", sarr.data);
    CHECK(sarr_add(&sarr, &to_add2))
    printf("Added %s\n%s\n", to_add2.data, sarr.data);
    printf("count %s 3\n", sarr_count(&sarr) != 3 ? "!=" : "==");
    CHECK(sarr_remove(&sarr, sarr_count(&sarr) - 1))
    printf("Removed latest element\n%s\n", sarr.data);
    CHECK(sarr_insert(&sarr, 0, &to_add3))
    printf("Inserted %s at %d\n%s\n", to_add3.data, 0, sarr.data);
    CHECK(sarr_insert(&sarr, 2, &to_add4))
    printf("Inserted %s at %d\n%s\n", to_add4.data, 2, sarr.data);
    CHECK(sarr_insert(&sarr, 1, &to_add5))
    printf("Inserted %s at %d\n%s\n", to_add5.data, 1, sarr.data);
    str_t second = sarr_getdup(&sarr, 1);
    printf("Second str: '%s'\n", second.data);
    free(to_add.data);
    free(to_add2.data);
    free(to_add3.data);
    free(to_add4.data);
    free(to_add5.data);
    free(second.data);
    free(sarr.data);
    return 0;
}
