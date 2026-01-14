#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "e1_str.h"

#define JOIN(a, b) join(&part1, &part2, a, b)

int main(void) {
    printf("--- e1_str test ---\n");
    str_t hw = cstr_to_str("Hello, World", true);
    addch(&hw, '!');
    printf("'%s' 'Hello, World!'\n", hw.data);
    reverse(&hw);
    printf("'%s' '!dlroW ,olleH'\n", hw.data);
    str_t n1, n2, n3, n4, n5;
    n1 = itoa(-125, 10);
    n2 = itoa(125125125, 10);
    n3 = utoa(4000000000, 10);
    n4 = ltoa(4000000000 * 2, 10),
    n5 = ultoa((unsigned long long)-1, 10);
    printf("'%s' -125\n'%s' 125125125\n'%s' 4000000000\n'%s' %ld\n'%s' %llu\n",
            n1.data, n2.data, n3.data, n4.data, 4000000000 * 2, n5.data, (unsigned long long)-1);
    str_t part1 = cstr_to_str("QWE", true),
          part2 = cstr_to_str("RTY", true);
    str_t j1 = JOIN(0, false),
          j2 = JOIN('\n', false),
          j3 = JOIN('-', true);
    printf("1. %s\n2. %s\n3. %s\n-.\n", j1.data, j2.data, j3.data);
    str_t input = readstr();
    printf("'%s'\n", input.data);
    free(n1.data);
    free(n2.data);
    free(n3.data);
    free(n4.data);
    free(n5.data);
    free(j1.data);
    free(j2.data);
    free(j3.data);
    free(input.data);
    free(hw.data);
    return 0;
}
