#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estrdup.h"
#include "e1l.h"

#define EC(x) if (x != 0) { printf("\033[31merror! %d\n\033[0m", callcount); return 1; } callcount += 1;
#define ECN(x) if (!x) { printf("\033[31merror! %d\n\033[0m", callcount); return 1; } callcount += 1;

int main(void) {
    int callcount = 1;
    size_t l = 0, tl = 0;
    char *s = estrdupl("Hello 1\n\
Hello 2\n\
Hello 3\n\
Hello 4\n\
Hello 5\n", &l),
         *t = NULL;
    
    puts("\033[36m=== e1_sarr test ===\033[0m");

    printf("Source:\n%s\nEnd of source\n", s);
    EC(sarr_normalize(&s, &l));
    printf("New source:\n%s\nEnd of new source\n", s);

    tl = sarr_getpos(s, l, 1);
    if (tl != 8) { printf("\033[31merror! %d\n\033[0m", callcount); return 1; } callcount += 1;
    tl = 0;
    
    t = sarr_getdup(s, l, 2, &tl);
    ECN(t);
    printf("3: %lu %s\n", tl, t);
    free(t);
    t = NULL;

    t = sarr_getdup(s, l, 4, &tl);
    ECN(t);
    printf("5: %lu %s\n", tl, t);
    free(t);
    t = NULL;

    EC(sarr_add(&s, &l, "Hello 6", 7));
    t = sarr_getdup(s, l, 5, &tl);
    ECN(t);
    printf("6: %lu %s\n", tl, t);
    free(t);
    t = NULL;

    EC(sarr_remove(&s, &l, 1));
    t = sarr_getdup(s, l, 1, &tl);
    ECN(t);
    printf("2: %lu %s\n", tl, t);
    free(t);
    t = NULL;

    EC(sarr_insert(&s, &l, 1, "Hello 2 (again!!)", 17));
    t = sarr_getdup(s, l, 1, &tl);
    ECN(t);
    printf("2: %lu %s\n", tl, t);
    free(t);
    t = NULL;

    tl = sarr_getpos(s, l, 2);
    if (tl != 26) { printf("\033[31merror! %d\n\033[0m", callcount); return 1; } callcount += 1;

    printf("Result:\n%s\nEnd of result\n", s);

    free(s);
    return 0;
}
