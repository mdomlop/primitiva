#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  /* isdigit() */
#include <time.h>  /* time() */

#define NBOLAS 49  /* El número de bolas. */
#define MARCAS 6  /* El número de casillas marcadas. */


#define DEBUG 0  /* Si no es 0 muestra información adicional. */

/*
int lasbolas[NBOLAS] = {1,  8,  15, 22, 29, 36, 43,
                        2,  9,  16, 23, 30, 37, 44,
                        3,  10, 17, 24, 31, 38, 45,
                        4,  11, 18, 25, 32, 39, 46,
                        5,  12, 19, 26, 33, 40, 47,
                        6,  13, 20, 27, 34, 41, 48,
                        7,  14, 21, 28, 35, 42, 49};

                        */
#define N 100000
int a[N];

void shuffle(int list[], int size)
{
    int i;
    int k;
    int num;
    int aux[size];

    for (i = 0; i < size; i++)
    {
        num = rand() % (size - i);
        aux[i] = list[num];

        for ( k = num; k < size - 1 ; k++ )
        {
            list[k] = list[k+1];
        }

    }
    for (i = 0; i < size; i++) list[i] = aux[i];
}

int main(void)
{
    srand(time(NULL));
    size_t i;
    for (i=0; i<N; i++)
        a[i] = i;
    printf("%d\n", a[N-1]);
    shuffle(a, N);
    printf("%d\n", a[N-1]);
    return 0;
}
