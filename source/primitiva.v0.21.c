/* primitiva

    primitiva - Jugar a la lotería primitiva.
    Copyright (C) 2012 Manuel Domínguez López

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    Version 0.2

    Changelog:
    2012.10.17:7.43 version 0.2:
        +Mejorado código. Basado en una versión en python.
        +Comprobación que la entrada sean enteros dentro del rango especificado.
        * TODO:
        -Que reconozca 5 aciertos + reintegro (es premio).
        -Que muestre el intento en el que se consigue cierto resultado.
        -Identifique los premios: 1ª categoría, 2ª...
        -Algunas otras cosas...
    2011.12.15 version 0.1:
        +Funcionalidad básica. Imprime resultados.
        * TODO:
        -Mejorar el código.
        -Comprobación que la entrada sean enteros dentro del rango especificado.
        -Que reconozca 5 aciertos + reintegro (es premio).
        -Que muestre el intento en el que se consigue cierto resultado.
        -Identifique los premios: 1ª categoría, 2ª...
        -Algunas otras cosas...
*/


#define PROGRAM     "Primitiva"
#define EXECUTABLE  "primitiva"
#define DESCRIPTION "Spanish Primitiva game emulator."
#define VERSION     "0.20"
#define URL         "https://github.com/mdomlop/primitiva"
#define LICENSE     "GPLv3+"
#define AUTHOR      "Manuel Domínguez López"
#define NICK        "mdomlop"
#define MAIL        "zqbzybc@tznvy.pbz"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  /* isdigit() */
#include <time.h>  /* time() */
#include <unistd.h> /* getpid() */
#include <getopt.h>

#define BOLAS 49
#define JUGADAS 6
#define randomize ( srand(time(NULL) + getpid()) )
#define random(limit) ( rand() % (limit) )

#define DEBUG 0 /* Si no es 0 muestra información adicional. */

int bombo[BOLAS];
int mibombo[BOLAS];

int premio[JUGADAS];
int mipremio[JUGADAS];

int complementario, reintegro, mireintegro;
int minimo, intentos;

int resultado[18]; /* 'resultado' contendrá: premio, reintegro,
                      complementario; mipremio, mireintegro; minimo; intentos */

void version(void)
{
	puts("Esto es la función version()");
}

void mk_array(int array[], int arrayc)
{
    int i;
    for (i = 0; i < arrayc; i++) array[i] = i + 1;
}


void print_array(int array[], int arrayc)
{
    short i;
    printf("[");
    for (i = 0; i < arrayc; i++)
    {
        printf("%d", array[i]);
        if ( i < arrayc -1) printf(", ");
    }
    printf("]");
}


void unsort_array(int array[])
{
    int i;
    int k;
    int num;
    int aux[BOLAS];


    for (i = 0; i < BOLAS; i++)
    {
        num = rand() % (BOLAS - i); /* El número que se saca (índice de array) */
        aux[i] = array[num];

        for ( k = num; k < BOLAS - 1 ; k++ )
        {
            array[k] = array[k+1];
        }

    }
    for (i = 0; i < BOLAS; i++) array[i] = aux[i];
}


void sort_insert_array (int a[], int n)
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


void get_array(int new_array[], int array[], int limit)
{
	/* Copia parte de un array. */
    int i;
    for (i = 0; i < limit; i++) new_array[i] = array[i];
}


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


int esentero (char * s)
/* Determina si la cadena pasada es un número entero positivo */
{
    short c;
    short sc = strlen(s);
    for ( c = 0; c < sc; c ++ )
    {
        if ( (c == 0) && (s[c] == '-') )
        /* Para dar una respuesta correcta a números negativos.
           Si no podría decir: -4 no es un número entero. */
        {
            continue;
        }
        else if ( isdigit( s[c] ) )
        {
            continue;
        }
        else
        {
            fprintf (stderr, "%s no es un número entero.\n", s);
            exit(1);
        }
    }

    return 0;
}


void vapuesta(int array[], int arrayc)
{
/*  Comprueba que la apuesta sea válida
    ( 6 números enteros diferentes entre 1 y 49). */
    short x;
    short c = 0; /* Contador de repeticiones. */
    short r;

    for (x = 0 ; x < arrayc; x++)
    {
        /* Si está entre 1 y 49: */
        if ( (array[x] < 1) || (array[x] > 49) )
        {
            fprintf(stderr, "%d no es un número del 1 al 49.\n", array[x]);
            exit(1);
        }

        /* Si hay alguno repetido: */
        for (r = 0; r < arrayc; r++)
        {
            if (array[x] == array[r])
            {
                c = c + 1;
                if (c > 1)
                {
                    fprintf(stderr, "El número %d está repetido.\n", array[x]);
                    exit(1);
                }
            }
        }
    }
}


void vminimo( int x)
{
    /* Comprueba que el número mínimo de aciertos sea válido
       (un entero entre 0 y 6) */
    if ( (x < 0) || (x > 6) )
    {
        fprintf(stderr, "El número proporcionado como valor mínimo de aciertos a mostrar no es válido.\n%d no es un número del 0 al 6.\n", x );
        exit(1);
    }
}


void vintentos(int x)
{
    /* Comprueba que el número de intentos solicitado sea válido
       (un entero mayor que 0) */
    if (x < 0)
    {
        fprintf(stderr, "El valor proporcionado como número de intentos no es válido.\n%d no es un número mayor que 0.\n", x );
        exit (1);
    }
}


void sorteo(void)
{
    /* Saca la combinación ganadora.
       No funciona: bombo = random.shuffle( list( range( 1, 50 ) ) ) */
    mk_array(bombo, BOLAS); /* Entran los números del 1 al 49. */
    unsort_array(bombo); /* Ya están desordenados. */
    get_array(premio, bombo, JUGADAS); /* Extraemos el premio. */

    /* El reintegro es un número aleatorio del 0 al 9. Lo elige la máquina.
       Sale de un bombo aparte del del premio. */
    reintegro = random(10);
    /* Y el complementario: */
    complementario = bombo[JUGADAS];
}


void jmaq(void)
{
    /*  Devuelve una lista con los números a jugar elegidos por la máquina.
		*
		* Empezamos con una lista ordenada. Para no desordenarla 2 veces. */
    mk_array(mibombo, BOLAS);
    unsort_array(mibombo); /* Y la desordenamos. */
    mireintegro = random(10); /* El mío también me lo da la máquina. */

    /* Sacamos la combinación ganadora. Índices del 0 al 6: 7 números. */
    get_array(mipremio, mibombo, JUGADAS);
}


void jusu(char * apuestas[])
{
    /* Devuelve una lista con los números a jugar elegidos por el usuario. */
    short i;
    reintegro = random(10); /* El mío también me lo da la máquina. */

    for (i = 0; i < JUGADAS; i++)
    {
        esentero(apuestas[i]);  /* exit(1) si no es entero. */
        mipremio[i - 1] = atoi(apuestas[i]);
    }

    vapuesta(mipremio, JUGADAS);
}


void earg(int argc, char * argv[])
{
    /* Evalúa la línea de comandos */
    if ( argc  == 1 ) /* 0 argumentos: Juega la máquina automáticamente. */
    {
        minimo = 0; /* mínimo */
        intentos = 1; /* intentos */

        sorteo();
        jmaq();
    }
    else if ( argc  == 2 ) /* 1 argumento: intentos. Jugando la máquina */
    {
        minimo = 0; /* mínimo */

        esentero(argv[1]); /* Comprobar si es entero. */
        intentos = atoi(argv[1]);

        vintentos(intentos);

        sorteo();
        jmaq();
    }
    else if ( argc == 3 ) /* 2 argumentos: mini e intentos. Jugando la máquina */
    {
        esentero(argv[1]); /* Comprobar si es entero. */
        esentero(argv[2]); /* Comprobar si es entero. */

        minimo= atoi(argv[1]);
        intentos = atoi(argv[2]);

        vminimo(minimo);
        vintentos(intentos);

        sorteo();
        jmaq();
    }
    else if ( argc == 7) /* 6 argumentos: mis 6 números. */
    {
        minimo = 0;
        intentos = 1;

        sorteo();
        jusu(argv);
    }
    else if ( argc == 8) /* 7 argumentos: mis 6 números y los intentos. Imprime todo. */
    {
        minimo = 0;

        esentero(argv[7]); /* Comprobar si es entero. */
        intentos = atoi(argv[7]);

        vintentos(intentos);

        sorteo();
        jusu(argv);
    }
    else if ( argc == 9 ) /* 8 argumentos: mis 6 números y mini e intentos. */
    {
        esentero(argv[7]); /* Comprobar si es entero. */
        esentero(argv[8]); /* Comprobar si es entero. */

        minimo = atoi(argv[7]);
        intentos = atoi(argv[8]);

        vminimo(minimo);
        vintentos(intentos);

        sorteo();
        jusu(argv);
    }
    else
    {
        help();
        exit(1);
    }
}


void jugar(int argc, char * argv[])
{
    /* Compara las combinaciones. Imprime resultados. */

    int intentosc = intentos; /* Este valor será usado como contador y será modificado. */
    int resultadosok = 0; /* Este valor se usa para contar el número de resultados satisfactorios. */

    int aciertos[JUGADAS];
    int aciertosc;


    char ccad[20];
    char rcad[20];
    char acad[20];
    char caux[20];
    char raux[20];

    earg(argc, argv); /* Parece necesario para que coja los valores minimo e intentos. INEFICIENTE. */

    while (intentosc > 0)
    {
        short apuesta;

        strcpy(ccad, "");
        strcpy(rcad, "");
        strcpy(acad, "");
        strcpy(caux, "");
        strcpy(raux, "");
        aciertosc = 0;

        earg(argc, argv);
        for (apuesta = 0; apuesta < JUGADAS; apuesta++) /* Para cada número que he jugado... */
        {
            short resultado;
            for (resultado = 0; resultado < JUGADAS; resultado++) /* Comprobar si está en la combinación ganadora. */
            {
                if (mipremio[apuesta] == premio[resultado])
                {
                    aciertos[aciertosc] = mipremio[apuesta]; /* Nueva lista aciertos mete las apuestas que coinciden con los resultados. */
                    aciertosc++;
                }
            }
            if (complementario == apuesta)
            {
                strcpy(ccad, " Complementario: ");
                sprintf(caux, "%d", complementario);
                strcat(ccad, caux);
            }
        }

        if (mireintegro == reintegro)
        {
            strcpy(rcad, " Reintegro: ");
            sprintf(raux, "%d", mireintegro);
            strcat(rcad, raux);
        }

        /* Ordenamos las listas de resultados: */
        sort_insert_array(aciertos, aciertosc);
        sort_insert_array(premio, JUGADAS);
        sort_insert_array(mipremio, JUGADAS);

        if (DEBUG) /* Si es 0 muestra información adicional. */
        {
            printf("\nPremio: ");
            print_array(premio, JUGADAS);
            printf(" Complementario: %d Reintegro: %d",complementario, reintegro);
            printf("\nMi premio: ");
            print_array(mipremio, JUGADAS);
            printf(" Mi reintegro: %d",mireintegro);
            printf("\nAciertos: ");
            print_array(aciertos, aciertosc);
            printf("\n\n");
        }

        /* Imprimir, evaluando si el número de aciertos es plural: */
        if (aciertosc == 1)
        {
            strcpy(acad, "acierto:");
        }
        else
        {
            strcpy(acad, "aciertos:");
        }

        if (aciertosc >= minimo)
        {
            printf ("%d %s ", aciertosc, acad);
            print_array(aciertos, aciertosc);
            printf ("%s %s\n",ccad ,rcad);
            resultadosok = resultadosok + 1;
        }
        intentosc = intentosc - 1;
    }
    printf ("%d/%d\n", resultadosok, intentos);
}


int main(int argc, char *argv[])
{
    int iflag, aflag, nflag, hflag, vflag;
	iflag = aflag = nflag = hflag = vflag = 0;

	char *ivalue = NULL;
	char *avalue = NULL;
	int nvalue[JUGADAS];

	int c;

	while ((c = getopt (argc, argv, "i:a:n:hv")) != -1)
		switch (c)
		{
			case 'i':  /* Intentos */
				iflag = 1;
				ivalue = optarg;
				break;
			case 'a':  /* Aciertos (mínimo de aciertos) */
				aflag = 1;
				avalue = optarg;
				break;
			case 'n':  /* Los seis números que se juegan */
				nflag = 1;
				sscanf(optarg, "%d %d %d %d %d %d",
						&nvalue[0], &nvalue[1], &nvalue[2],
						&nvalue[3], &nvalue[4], &nvalue[5]);
                misapuestas = nvalue;
				break;
			case 'h':  /* Show help */
				hflag = 1;
				break;
			case 'v':  /* Show program version */
				vflag = 1;
				break;
			case '?':
                if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n",
							optopt);
                return 1;
			default:
				help();
				abort ();
		}

	if (argc - optind > 3)  // Max non-option argumets are 3
	{
		fprintf (stderr, "Sorry. Too much arguments.\n");
		return 1;
	}

    if(hflag)
	{
		help();
	}
	else if (vflag)
	{
		version();
	}

    randomize;
    jugar(argc, argv);
    return 0;
}
