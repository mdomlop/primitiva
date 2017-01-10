#!/usr/bin/python
# -*- coding: utf-8 -*-
# primitiva: Jugar a la lotería primitiva.
#TODO: 

import sys
import random
import os.path


def informa():
	"""Muestra información, ayuda y forma de uso del programa."""
	print('\nUso del programa:\n\
' + os.path.basename(sys.argv[0]) + ' [n1 n2 n3 n4 n5 n6] [min int]\n\
\n\
Donde:\n\
min: Es el número mínimo de aciertos.\n\
int: Número de intentos para obtener resultados\n\
n1 .. n6: Los seis números con los que se desea probar suerte.')


def esentero(x):
	"""Comprueba que el valor proporcionado sea entero."""
	try:
		x == int( x )
	except:
		sys.exit( x + ' no es un número entero.' )


def vapuesta(lista):
	"""Comprueba que la apuesta sea válida
	( 6 números enteros diferentes entre 1 y 49)."""
	for x in lista:
		# Si está entre 1 y 49:
		if x < 1 or x > 49:
			sys.exit( str(x) + ' no es un número del 1 al 49.' )

		# Si hay alguno repetido:
		c = 0 # Contador de repeticiones.
		for r in lista:
			if x == r:
				c = c + 1
				if c > 1:
					sys.exit( 'El número ' + str(x) + ' está repetido.' )


def vminimo(x):
	"""Comprueba que el número mínimo de aciertos sea válido
	(un entero entre 0 y 6)"""
	if x < 0 or x > 6:
		sys.exit( 'El número proporcionado como valor mínimo de aciertos a \
mostrar no es válido.\n' + str(x) + ' no es un número del 0 al 6.' )


def vintentos(x):
	"""Comprueba que el número de intentos solicitado sea válido
	(un entero mayor que 0)"""
	if x < 0:
		sys.exit( 'El valor proporcionado como número de intentos \
no es válido.\n' + str(x) + ' no es un número mayor que 0.' )


def sorteo():
	"""Saca la combinación ganadora."""
	#No funciona: bombo = random.shuffle( list( range( 1, 50 ) ) )
	bombo = list( range( 1, 50 ) ) # Entran los números del 1 al 49.
	random.shuffle( bombo ) # Ya están desordenados.
	premio = [] # Definimos la lista. Esto parece necesario en python.

	for i in range(6):
		premio.append(bombo[i])

	# El reintegro es un número aleatorio del 0 al 9. Lo elige la máquina.
	#Sale de un bombo aparte del del premio.
	reintegro = random.choice( list( range( 10 ) ) )
	# Y el complementario:
	complementario = bombo[6]

	return (premio, reintegro, complementario)


def jmaq():
	"""Devuelve una lista con los números a jugar elegidos por la máquina."""
	mibombo = list( range( 1, 50 ) ) # Empezamos con una lista ordenada. Para no desordenarla 2 veces.
	random.shuffle( mibombo ) # Y la desordenamos.
	mireintegro = random.choice( list( range( 10 ) ) ) # El mío también me lo da la máquina.
	# Sacamos la combinación ganadora. Índices del 0 al 6: 7 números.
	mipremio = [] # Definimos la lista. Esto parece necesario en python.

	for i in range(6):
		mipremio.append(mibombo[i])

	return (mipremio, mireintegro)


def jusu():
	"""Devuelve una lista con los números a jugar elegidos por el usuario."""
	mireintegro = random.choice( list( range( 10 ) ) ) # El mío también me lo da la máquina.
	mipremio = [] # Definimos la lista. Esto parece necesario en python.

	for i in range(1,7):
		esentero(sys.argv[i])
		mipremio.append(int(sys.argv[i]))

	vapuesta(mipremio)

	return (mipremio, mireintegro)


def earg():
	"""Evalúa la línea de comandos"""
	if len( sys.argv ) == 1: # 0 argumentos: Juega la máquina automáticamente.
		minimo = 0
		intentos = 1
		return (sorteo(), jmaq(), minimo, intentos)
	elif len( sys.argv ) == 2: # 1 argumento: intentos. Jugando la máquina
		minimo = 0
		esentero(sys.argv[1]) # Comprobar si es entero.
		intentos = int(sys.argv[1])
		vintentos(intentos)
		return (sorteo(), jmaq(), minimo, intentos)
	elif len( sys.argv ) == 3: # 2 argumentos: mini e intentos. Jugando la máquina
		esentero(sys.argv[1]) # Comprobar si es entero.
		esentero(sys.argv[2]) # Comprobar si es entero.
		minimo = int(sys.argv[1])
		intentos = int(sys.argv[2])
		vminimo(minimo)
		vintentos(intentos)
		return (sorteo(), jmaq(), minimo, intentos)
	elif len( sys.argv ) == 7: # 6 argumentos: mis 6 números.
		minimo = 0
		intentos = 1
		return (sorteo(), jusu(), minimo, intentos)
	elif len( sys.argv ) == 8: # 7 argumentos: mis 6 números y los intentos. Imprime todo.
		minimo = 0
		esentero(sys.argv[7]) # Comprobar si es entero.
		intentos = int(sys.argv[7])
		vintentos(intentos)
		return (sorteo(), jusu(), minimo, intentos)
	elif len( sys.argv ) == 9: # 8 argumentos: mis 6 números y mini e intentos.
		esentero(sys.argv[7]) # Comprobar si es entero.
		esentero(sys.argv[8]) # Comprobar si es entero.
		minimo = int(sys.argv[7])
		intentos = int(sys.argv[8])
		vminimo(minimo)
		vintentos(intentos)
		return (sorteo(), jusu(), minimo, intentos)
	else:
		informa()
		exit(1)


def jugar():
	"""Compara las combinaciones. Imprime resultados."""
	resultados = earg() # Parece necesario para que coja los valores minimo e intentos. INEFICIENTE.
	minimo = resultados[2]
	intentos = resultados[3]
	intentosc = intentos # Este valor será usado como contador y será modificado.
	satisfaccion = 0 # Este valor se usa para contar el número de resultados satisfactorios.

	while intentosc > 0:
		c = ''
		r = ''
		resultados = earg()
		premio = resultados[0][0]
		reintegro = resultados[0][1]
		complementario = resultados[0][2]
		mipremio = resultados[1][0]
		mireintegro = resultados[1][1]
		aciertos = [] # Definimos la lista. Esto parece necesario en python.

		if mireintegro == reintegro:
			r = ' Reintegro: ' + str( mireintegro )

		for apuesta in mipremio: # Para cada número que he jugado...
			for resultado in premio: # Comprobar si está en la combinación ganadora.
				if apuesta == resultado:
					aciertos.append(apuesta) # Nueva lista aciertos mete las apuestas que coinciden con los resultados.
			if complementario == apuesta:
				c = ' Complementario: ' + str( complementario )

		# Ordenamos las listas de resultados:
		aciertos.sort()
		premio.sort()
		mipremio.sort()

		# Imprimir:
		if len(aciertos) == 1:
			a = str(len(aciertos)) + ' acierto: '
		else:
			a = str(len(aciertos)) + ' aciertos: '

		if len(aciertos) >= minimo:
			print ( a + str(aciertos) + c + r )
			satisfaccion = satisfaccion + 1
		intentosc = intentosc - 1
	print (str(satisfaccion) + '/' + str(intentos))


jugar()
