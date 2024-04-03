/* primitiva

    primitiva - Jugar a la lotería primitiva.
    Copyright (C) 2024 Manuel Domínguez López
*/

#define PROGRAM     "Primitiva"
#define EXECUTABLE  "primitiva"
#define DESCRIPTION "Spanish Primitiva game emulator."
#define VERSION     "0.30"
#define URL         "https://github.com/mdomlop/primitiva"
#define LICENSE     "GPLv3+"
#define AUTHOR      "Manuel Domínguez López"
#define NICK        "mdomlop"
#define MAIL        "zqbzybc@tznvy.pbz"
#define VERSIONYEAR "2024"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  /* isdigit() */
#include <time.h>  /* time() */
#include <getopt.h>

#define BOLAS 49
#define NAPUESTAS 6
#define randomize ( srand(time(NULL)) )
#define random(limit) ( rand() % (limit) )

#define DEBUG 0 /* Si no es 0 muestra información adicional. */


int elbombo[BOLAS];
int mibombo[BOLAS];

int premiados[NAPUESTAS];
int misapuestas[NAPUESTAS];

int elreintegro, mireintegro;

int elcomplementario;

int intentos = 1;
int minimo = 0;
int verbose = 0;

int okresultados = 0; /* Los resultados satisfactorios. */
int okcomplementario, okreintegro;

void help(void)
{
/*  Muestra información, ayuda y forma de uso del programa. */

    printf("\n");
    printf("Uso del programa:\n");
    printf("primitiva [-n n1 n2 n3 n4 n5 n6] [-i int] [-a int]\n");
    printf("\n");
    printf("Donde:\n");
    printf("-i int: Es el número mínimo de aciertos.\n");
    printf("-a int: Número de intentos para obtener resultados\n");
    printf("-n n1 .. n6: Los seis números con los que se desea probar suerte.\n");
}

void version(void)
{
    puts("Versión");
}

void unsort_array(int array[], int arrayc)
{
    int i;
    int k;
    int num;
    int aux[arrayc];


    for (i = 0; i < arrayc; i++)
    {
        /* El número que se saca (índice de array) */
        num = rand() % (arrayc - i);
        aux[i] = array[num];

        for ( k = num; k < arrayc - 1 ; k++ )
        {
            array[k] = array[k+1];
        }

    }
    for (i = 0; i < arrayc; i++) array[i] = aux[i];
}

void copy_array(int new_array[], int array[], int limit)
{
	/* Copia parte de un array. */
    int i;
    for (i = 0; i < limit; i++) new_array[i] = array[i];
}

void print_int_array(int array[], int arrayc)
{
    short i;
    printf("[");
    for (i = 0; i < arrayc; i++)
    {
        printf("%d", array[i]);
        if ( i < arrayc - 1) printf(", ");
    }
    printf("]");
}


void sort_array (int a[], int n)
{
    int i, k, aux;
    for (i = 1; i < n; i++)
    {
        k = i;
        aux = a[i];
        while (k > 0 && aux < a[k-1])
        {
            a[k] = a[k-1];
            k--;
        }
        a[k] = aux;
    }
}


int esentero (char * s)
/* Determina si la cadena pasada es un número entero positivo */
{
    short c;
    short sc = strlen(s);
    for (c = 0; c < sc; c ++)
    {
        /* Si el primer carácter es - */
        if ((c == 0) && (s[c] == '-')) continue;
        else if (isdigit( s[c])) continue;
        else
        {
            fprintf(stderr, "%s no es un número entero.\n", s);
            exit(1);
        }
    }

    return 0;
}

void vapuesta(void)
{
/*  Comprueba que la apuesta sea válida
    (6 números enteros diferentes entre 1 y 49). */
    short x;
    short c; /* Contador de repeticiones. */
    short r;

    for (x = 0 ; x < NAPUESTAS; x++)
    {
        /* Si está entre 1 y 49: */
        if ( (misapuestas[x] < 1) || (misapuestas[x] > 49) )
        {
            fprintf(stderr, "%d no es un número del 1 al 49.\n", misapuestas[x]);
            exit(1);
        }

        /* Si hay alguno repetido: */
        c = 0;
        for (r = 0; r < NAPUESTAS; r++)
        {
            if (misapuestas[x] == misapuestas[r])
            {
                c++;
                if (c > 1)
                {
                    fprintf(stderr, "El número %d está repetido.\n",
                            misapuestas[x]);
                    exit(1);
                }
            }
        }
    }
}


void vminimo(void)
{
    /* Comprueba que el número mínimo de aciertos sea válido
       (un entero entre 0 y 6) */
    if ( (minimo < 0) || (minimo > 6) )
    {
        fprintf(stderr, "El número mínimo de aciertos a mostrar es 0"
        " y el máximo es 6. Has solicitado: %d\n", minimo);
        exit(1);
    }
}

void vintentos(void)
{
    /* Comprueba que el número de intentos solicitado sea válido
       (un entero mayor que 0) */
    if (intentos < 1)
    {
        fprintf(stderr, "El número mínimo de intentos es 1."
        " Has proporcionado: %d\n", intentos);
        exit (1);
    }
}

void mk_bombo(int array[])
{
    /* Rellena el bombo con los números del 1 hasta BOLAS */
    int i;
    for (i = 0; i < BOLAS; i++) array[i] = i + 1;
}

void sortear(void)
{
    /* Saca la combinación ganadora. */
    mk_bombo(elbombo);
    unsort_array(elbombo, BOLAS);
    /* Extraemos el premio. */
    copy_array(premiados, elbombo, NAPUESTAS);

    /* El reintegro es un número aleatorio del 0 al 9. Lo elige la máquina.
       Sale de un bombo aparte del del premio. */
    elreintegro = random(10);
    /* Y el complementario, que sale de cualquiera de los números del premio. */
    elcomplementario = elbombo[NAPUESTAS];
}

void apostar(int automatic)
{
    /* Esablece misapuestas[] y mireintegro */
    if (automatic)
    {
        /* Juega la máquina por nosotros. */
        mk_bombo(mibombo);
        unsort_array(mibombo, BOLAS); /* Y la desordenamos. */
        mireintegro = random(10); /* El mío también me lo da la máquina. */

        /* Sacamos la apuesta. Índices del 0 al 6: 7 números. */
        copy_array(misapuestas, mibombo, NAPUESTAS);
    }
    else
    {
        puts("");
    }

    mireintegro = random(10);  /* El reintegro no se elige */
}

void jugar(int verbose)
{
    /* Compara las combinaciones. Imprime resultados. */
    int aciertos[NAPUESTAS];  /* No puede haber más aciertos que jugadas */
    int aciertosc = 0; /* Contador de aciertos. */

    short i;
    short j;
    /* Comprobar si cada número apostado está entre los premiados */
    okcomplementario = 0;
    okreintegro = 0;
    for (i = 0; i < NAPUESTAS; i++)
    {
        for (j = 0; j < NAPUESTAS; j++)
        {
            if (misapuestas[i] == premiados[j])
            {
                aciertos[aciertosc] = misapuestas[i]; /* Los aciertos */
                aciertosc++; /* Número de aciertos */
            }
        }
        if (elcomplementario == i) okcomplementario = 1;
    }

    if (mireintegro == elreintegro) okreintegro = 1;

    /* Ordenamos las listas de resultados: */
    sort_array(aciertos, aciertosc);
    sort_array(premiados, NAPUESTAS);
    sort_array(misapuestas, NAPUESTAS);

    if (verbose) /* Si es 0 muestra información adicional. */
    {
        printf("\nPremiados: ");
        print_int_array(premiados, NAPUESTAS);
        printf(" El complementario: %d El reintegro: %d",elcomplementario, elreintegro);
        printf("\nMis apuestas: ");
        print_int_array(misapuestas, NAPUESTAS);
        printf(" Mi reintegro: %d",mireintegro);
        printf("\nAciertos: ");
        print_int_array(aciertos, aciertosc);
        printf("\n\n");
    }


    if (aciertosc >= minimo)
    {
        printf("%d %s", aciertosc, (aciertosc == 1)?"acierto: ":"aciertos: ");
        print_int_array(aciertos, aciertosc);
        printf(" ");
        print_int_array(premiados, NAPUESTAS);
        puts("");
        okresultados = okresultados + 1;
    }
}

int main(int argc, char *argv[])
{
	int c;

    randomize;

	while ((c = getopt(argc, argv, "i:m:hvV")) != -1)
		switch (c)
		{
			case 'i':  /* Intentos */
                esentero(optarg);
				intentos = atoi(optarg);
                vintentos();
				break;
			case 'm':  /* Mínimo de aciertos */
                esentero(optarg);
				minimo = atoi(optarg);
                vminimo();
				break;
			case 'h':  /* Show help */
				help();
				break;
            case 'v':
                verbose = 1;
                break;
			case 'V':  /* Show program version */
				version();
				break;
			case '?':
                if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n",
							optopt);
                return 1;
			default:
                fprintf(stderr, "Error desconocido\n");
				help();
				abort();
		}

    int nonopt = argc - optind;
	if ((nonopt < 0) || (nonopt > 6))  // Max non-option argumets are 0
	{
		fprintf (stderr, "Sorry. Too much arguments: %d\n", (argc - optind));
		return 1;
	}
	else if (nonopt)
    {
        short idx;
        for (int i=0; i<NAPUESTAS; i++)
        {
            idx = optind + i;
            esentero(argv[idx]);
            misapuestas[i] =  atoi(argv[idx]);
        }
        vapuesta();
        apostar(0);
    }
    else apostar(1);  /* Automático */


    for (int i=0; i<intentos; i++)
    {
        sortear();
        jugar(verbose); /* aflag ya estableció las apuestas */
    }

    printf ("\nResultados con al menos %d %s: %d\n",
            minimo,(minimo == 1)?"acierto":"aciertos", okresultados);

    return 0;
}
