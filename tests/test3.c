#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "e1_str.h"
#include "e1_dstr.h"

int main(void) {
    printf("--- e1_dstr test ---\n");
    str_t hw = cstr_to_str("Hello, World!", true);
    dstr_t dhw = emptydstr();
    for (size_t i = 0; i < hw.size; i++) {
        d_addch(&dhw, hw.data[i]);
    }
    printf("buffsize=%zu pointer=%zu\n", dhw.buffsize, dhw.pointer);
    str_t test = dstr_to_str(&dhw, true);
    printf("dhw.data is %s\n", dhw.data ? "not null" : "null");
    printf("'%s'\n", test.data);
    free(hw.data);
    free(test.data);
    return 0;
}
