Primitiva
=========

El juego de la primitiva implementado en varios lenguajes.

Esto no es más que una ejercicio que me propuse para probar la eficiencia de
varios lenguajes.

Ninguno de los archivos son un programa serio ni siquiera remotamente.
Posiblemente tienen muchos fallos y no están mantenidos en modo alguno.

Solo los tengo aquí porque en algún sitio tengo que guardarlos :-)

No obstante pueden resultar entretenidos para probar lo difícil que es que te
pueda tocar la lotería.

Uso de programa
---------------

Uso del programa:

	$ primitiva [n1 n2 n3 n4 n5 n6] [-m mínimo] [-i intentos] [-vVh]

Donde:

- **`n1 .. n6`**

	Son los seis números con los que se desea probar suerte.

- **`-m`** **_mínimo_**:

	Es el número mínimo de aciertos requerido par mostrar resultados.

- **`-i`** **_intentos_**:

	Número de intentos para obtener resultados.

- **`-v`**:

	Activa el modo verborrea.

- **`-V`**:

	Muestra la versión del programa y sale del programa.

- **`-h`**:

	Muestra la ayuda y sale del programa.

### Ejemplos

Si no se proporciona ningún argumento el programa apostará 6 números aleatorios
una sola vez y mostrará todos los resultados:

	$ primitiva
	0 aciertos: [] [2, 4, 7, 21, 39, 42]
	Resultados con al menos 0 aciertos: 1


El resultado muestra el número de aciertos, luego los números acertados entre
corchetes y luego los números premiados del sorteo entre corchetes también.

Finalmente muestra una línea donde se resume las veces que se ha cumplido el
número de aciertos requerido, el cual es cero si no se especifica otro (con la
opción -m).


Si se proporcionan los seis números para apostar la máquina los apostará en lugar
de generarlos pseudoaleatoriamente:

	$ primitiva 1 2 3 4 5 6
	0 aciertos: [] [8, 9, 14, 19, 33, 43]
	Resultados con al menos 0 aciertos: 1


Si se usa la opción `-m`, sólo se contabilizarán los resultados que tengan al
menos el número de aciertos indicado. Por ejemplo para mostrar resultados con al menos tres aciertos:

	$ primitiva -m 3
	Resultados con al menos 3 aciertos: 0

O:

	$ primitiva 1 2 3 4 5 6 -m 3
	Resultados con al menos 3 aciertos: 0


Si se usa la opción `-i` se jugarán tantos sorteos como intentos especificados.
Por ejemplo:

	$ primitiva -m 3 -i 100
	3 aciertos: [7, 28, 48] [1, 7, 20, 25, 28, 48]
	3 aciertos: [16, 28, 48] [8, 16, 28, 38, 39, 48]
	Resultados con al menos 3 aciertos: 2

Aquí se han jugado 100 sorteos con números pseudoaleatorios distintos cada vez
y sólo se muestran los resultados con tres o más aciertos, que en este caso
no han sido nada más que dos.

Si quisiera elegir los números, simplemente habría que especificarlos y las cien
veces se jugarían dichos números, pero en cien sorteos distintos:

	$ primitiva 1 2 3 4 5 6 -m 3 -i 100
	3 aciertos: [3, 4, 6] [3, 4, 6, 16, 27, 38]
	3 aciertos: [3, 5, 6] [3, 5, 6, 10, 22, 35]
	3 aciertos: [2, 4, 6] [2, 4, 6, 31, 46, 48]
	Resultados con al menos 3 aciertos: 3



Con la opción `-v` se imprime una salida mucho más prolija donde se muestran
mucha más información de cómo se ha desarrollado el sorteo:

	$ primitiva 1 2 3 4 5 6 -m 3 -i 3 -v

	Premiados: [12, 28, 41, 44, 46, 47] El complementario: 27 El reintegro: 9
	Mis apuestas: [1, 2, 3, 4, 5, 6] Mi reintegro: 4
	Aciertos: []

	Premiados: [2, 13, 17, 26, 47, 48] El complementario: 5 El reintegro: 2
	Mis apuestas: [1, 2, 3, 4, 5, 6] Mi reintegro: 4
	Aciertos: [2]

	Premiados: [10, 20, 26, 28, 31, 40] El complementario: 2 El reintegro: 2
	Mis apuestas: [1, 2, 3, 4, 5, 6] Mi reintegro: 4
	Aciertos: []
	
	Resultados con al menos 3 aciertos: 0
	
	
