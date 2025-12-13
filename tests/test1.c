#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "e1_str.h"

int main(void) {
    printf("--- e1_str test ---\n");
    str_t hw = cstr_to_str("Hello, World!", true);
    printf("'%s' 'Hello, World!'\n", hw.data);
    reverse(&hw);
    printf("'%s' '!dlroW ,olleH'\n", hw.data);
    str_t n1, n2, n3, n4, n5;
    n1 = itoa(-125, 10);
    n2 = itoa(125125125, 10);
    n3 = utoa(4000000000, 10);
    n4 = ltoa(4000000000 * 2, 10),
    n5 = ultoa((unsigned long long)-1, 10);
    printf("'%s' -125\n'%s' 125125125\n'%s' 4000000000\n'%s' %lld\n'%s' %llu\n",
            n1.data, n2.data, n3.data, n4.data, 4000000000 * 2, n5.data, (unsigned long long)-1);
    str_t input = readstr();
    printf("'%s'\n", input.data);
    free(n1.data);
    free(n2.data);
    free(input.data);
    free(hw.data);
    return 0;
}
