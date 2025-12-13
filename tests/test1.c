#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e1_str.h"

int main(void) {
    printf("--- e1_str test ---\n");
    str_t hw;
    hw.data = strdup("Hello, World!");
    hw.size = strlen(hw.data);
    printf("'%s' 'Hello, World!'\n", hw.data);
    reverse(&hw);
    printf("'%s' '!dlroW ,olleH'\n", hw.data);
    str_t n1, n2;
    n1 = itoa(-125, 10);
    n2 = itoa(125125125, 10);
    printf("'%s' -125\n'%s' 125125125\n", n1.data, n2.data);
    str_t input = readstr();
    printf("'%s'\n", input.data);
    free(n1.data);
    free(n2.data);
    free(input.data);
    free(hw.data);
    return 0;
}
