#include <stdio.h>
#include <time.h>  /* time() */
#include <stdlib.h> /* rand() */
#include "bigarray.h"


int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;

    return rand() % 2 ? +1 : -1;
}

int main(void)
{
    srand(time(NULL));

    printf("%d\n", a[N-1]);

    qsort(a, N, sizeof(int), rand_comparison);
    printf("%d\n", a[N-1]);

    return 0;
}
