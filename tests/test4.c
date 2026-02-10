#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "e1_arr.h"

int* new(int val) {
    int *ret = malloc(sizeof(int));
    if (!ret) { return NULL; }
    *ret = val;
    return ret;
}

#define PRINT_ARR printf("count: %zu\n", a.count);\
    for (size_t i = 0; i < a.count; i++) {\
        printf("%d\n", *((int*)a.elems[i]));\
    }

int main(void) {
    printf("--- e1_arr test ---\n");
    arr_t a;
    arr_init(&a);
    arr_add(&a, new(1));
    arr_add(&a, new(2));
    arr_add(&a, new(5));
    arr_add(&a, new(-125));
    PRINT_ARR
    free(a.elems[1]);
    arr_remove(&a, 1);
    PRINT_ARR
    free(a.elems[0]);
    arr_remove(&a, 0);
    PRINT_ARR
    free(a.elems[1]);
    arr_remove(&a, 1);
    arr_add(&a, new(135));
    PRINT_ARR
    for (size_t i = 0; i < a.count; i++) {
        free(a.elems[i]);
    }
    arr_free(&a);
}
