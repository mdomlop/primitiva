#!/usr/bin/python3
# primitiva: Jugar a la lotería primitiva.
"""
TODO: Que emule un sorteo real con millones de participantes, registre los
premiados en cada una de las categorías y asigne un premio en euros a cada uno
de ellos en función del número de participantes.
"""

import random
import argparse

participantes = 1000  # 13014001
precio_boleto = 1.00
moneda = '€'
semanas = 1 / 2  # 2 sorteos por semana

defverbosidad = 0
defintentos = 1
defminimo = 0


class bombo:
    """ Genera los 6 números del combinacion, el complementario
    y el reintegro. """
    def sortear(self):
        self.numeros = list(range(1, 50))  # Entran los números del 1 al 49.
        self.combinacion = []
        self.complementario = ''  # Imposible 6 aciertos + complementario
        self.reintegro = ''  # Premio máx. 6 aciertos + reintegro
        random.shuffle(self.numeros)
        for i in range(6):
            # Los números premiados (posiciones 0..5)
            self.combinacion.append(self.numeros[i])
        self.combinacion.sort()
        # Y el complementario (posición 6):
        self.complementario = self.numeros[6]
        # El reintegro es un número aleatorio del 0 al 9. Lo elige la máquina.
        # Sale de un bombo aparte del del combinacion.
        self.reintegro = random.choice(list(range(10)))


class resultados:
    def evaluar(self):
        self.aciertos = []
        self.naciertos = 0
        self.complementario = False
        self.reintegro = False
        if jugador.reintegro == maquina.reintegro:
            self.reintegro = True
        for numero in jugador.combinacion:  # Para cada número que he jugado...
            if numero in maquina.combinacion:
                # Mete las apuestas que coinciden con los resultados.
                self.aciertos.append(numero)
            if maquina.complementario in jugador.combinacion:
                self.complementario = True
        # Ordenamos las listas de resultados:
        self.aciertos.sort()
        self.naciertos = len(self.aciertos)


class idpremio:
    ''' Identifica el premio obtenido según el resultado. '''
    # El numero de acertantes de esta categoría:
    nreintegro = 0
    nespecial = 0
    nc1 = 0
    nc2 = 0
    nc3 = 0
    nc4 = 0
    nc5 = 0

    def comprobar(self):
        self.reintegro = False
        self.especial = False
        self.c1 = False
        self.c2 = False
        self.c3 = False
        self.c4 = False
        self.c5 = False
        if(
                (resultado.naciertos == 0 or
                    resultado.naciertos == 1 or
                    resultado.naciertos == 2) and
                resultado.reintegro):
            self.reintegro = True
            self.nreintegro += 1
        elif(resultado.naciertos == 3):
            self.c5 = True
            self.nc5 += 1
        elif(resultado.naciertos == 4):
            self.c4 = True
            self.nc4 += 1
        elif(resultado.naciertos == 5 and resultado.complementario):
            self.c2 = True
            self.nc2 += 1
        elif(resultado.naciertos == 5):
            self.c3 = True
            self.nc3 += 1
        elif(resultado.naciertos == 6 and resultado.reintegro):
            self.especial = True
            self.nespecial += 1
        elif(resultado.naciertos == 6):
            self.c1 = True
            self.nc1 += 1


def estadistica():
    recaudacion = participantes * precio_boleto
    # Se destina a premios el 55 % de la recaudación:
    destino_premios = 55 * recaudacion / 100
    # Un 10 por 100 se asigna al fondo de premios para reintegro:
    fondos_reintegro = 10 * destino_premios / 100
    # Del otro 45 por ciento se deduce el importe destinado a la 5ª categoría,
    # resultado de multiplicar el número de apuestas acertadas de esa categoría
    # por su premio fijo de 8 euros:
    fondos_5a = premio.nc5 * 8
    # El resto se reparte entre las cuatro primeras categorías, usando los
    # porcentajes 52, 8, 16, y 24, respectivamente
    fondos_especial = 20 * (
            destino_premios - fondos_reintegro - fondos_5a) / 100
    fondos_1a = 40 * (destino_premios - fondos_reintegro - fondos_5a) / 100
    fondos_2a = 6 * (destino_premios - fondos_reintegro - fondos_5a) / 100
    fondos_3a = 13 * (destino_premios - fondos_reintegro - fondos_5a) / 100
    fondos_4a = 21 * (destino_premios - fondos_reintegro - fondos_5a) / 100
    if(premio.nespecial == 0):  # Previene división por 0
        individual_especial = 0
    else:
        individual_especial = fondos_especial / premio.nespecial
    if(premio.nc1 == 0):
        individual_1a = 0
    else:
        individual_1a = fondos_1a / premio.nc1
    if(premio.nc2 == 0):
        individual_2a = 0
    else:
        individual_2a = fondos_2a / premio.nc2
    if(premio.nc3 == 0):
        individual_3a = 0
    else:
        individual_3a = fondos_3a / premio.nc3
    if(premio.nc4 == 0):
        individual_4a = 0
    else:
        individual_4a = fondos_4a / premio.nc4
    individual_5a = 8
    individual_reintegro = precio_boleto
    print(
            'Premiados categoría especial: ', premio.nespecial,
            round(fondos_especial, 2), round(individual_especial, 2))
    print(
            'Premiados 1º categoría: ', premio.nc1,
            round(fondos_1a, 2), round(individual_1a, 2))
    print(
            'Premiados 2º categoría: ', premio.nc2,
            round(fondos_2a, 2), round(individual_2a, 2))
    print(
            'Premiados 3º categoría: ', premio.nc3,
            round(fondos_3a, 2), round(individual_3a, 2))
    print(
            'Premiados 4º categoría: ', premio.nc4,
            round(fondos_4a, 2), round(individual_4a, 2))
    print(
            'Premiados 5º categoría: ', premio.nc5,
            round(fondos_5a, 2), round(individual_5a, 2))
    print(
            'Premiados reintegro: ', premio.nreintegro,
            round(fondos_reintegro, 2), round(individual_reintegro, 2))


def valida_intentos(x):
    try:
        ix = int(x)
    except:
        raise argparse.ArgumentTypeError('Argumento inválido: “%s”\n\
(El número de repeticiones ha de ser un entero mayor que 0)' % x)
    if ix < defintentos:
        raise argparse.ArgumentTypeError('Argumento inválido: “%s”\n\
(El número de repeticiones ha de ser mayor que 0)' % x)
    return ix


def text_out(verbose, intento):
    if(args.minimo > resultado.naciertos):
        return(0)
    if(args.intentos > 1):
        print('Intento ' + str(intento) + '/' + str(args.intentos) + ':')
    if(verbose == 0):
        print(resultado.naciertos, end='')
        if(resultado.complementario):
            print('C', end='')
        if(resultado.reintegro):
            print('R', end='')
    elif(verbose > 0):
        if(resultado.naciertos == 1):
            plural = ': '
        else:
            plural = 's: '
        print('Combinación ganadora: ' + str(
            maquina.combinacion) +
            ' Complementario: ' + str(maquina.complementario) +
            ' Reintegro: ' + str(maquina.reintegro))
        print('Apuesta: ' + str(
            jugador.combinacion) + ' Reintegro: ' + str(jugador.reintegro))

        print(str(
            resultado.naciertos) +
            ' acierto' + plural + str(resultado.aciertos), end='')
        if(resultado.complementario):
            print(' + Complementario: ' + str(maquina.complementario), end='')
        if(resultado.reintegro):
            print(' + Reintegro: ' + str(maquina.reintegro), end='')
        print()
    print()
    if(premio.reintegro):
        print('Premio reintegro.')
    elif(premio.c5):
        print('Premio categoría 5ª.')
    elif(premio.c4):
        print('Premio categoría 4ª.')
    elif(premio.c3):
        print('Premio categoría 3ª.')
    elif(premio.c2):
        print('Premio categoría 2ª.')
    elif(premio.c1):
        print('Premio categoría 1ª.')
    elif(premio.especial):
        print('Premio categoría especial.')
    else:
        print('Nada')


def jugar_simple():
    intento = 1
    while(intento <= args.intentos):
        maquina.sortear()
        jugador.sortear()
        if(args.ganadora):
            maquina.combinacion = args.ganadora
        if(args.complementario):
            maquina.complementario = args.complementario
        if(args.Reintegro or args.Reintegro == 0):  # 0 equivaldría a False
            maquina.reintegro = args.Reintegro
        if(args.reintegro or args.reintegro == 0):
            jugador.reintegro = args.reintegro
        if(args.apuesta):
            jugador.combinacion = args.apuesta
        resultado.evaluar()
        premio.comprobar()
        text_out(args.verbosidad, intento)
        intento += 1


def jugar_real():
    global participantes
    intento = 1
    maquina.sortear()
    if(args.ganadora):
        maquina.combinacion = args.ganadora
    if(args.complementario):
        maquina.complementario = args.complementario
    if(args.Reintegro or args.Reintegro == 0):  # 0 equivaldría a False
        maquina.reintegro = args.Reintegro
    while(participantes > 0):
        jugador.sortear()
        resultado.evaluar()
        premio.comprobar()
        participantes -= 1
    text_out(args.verbosidad, intento)


parser = argparse.ArgumentParser()
parser.add_argument(
        '-v', '--verbosidad',
        default=defverbosidad, type=int, choices=range(10),
        help='El nivel de verbosidad. (def:' + str(defverbosidad) + ')')
parser.add_argument(
        '-i', '--intentos', default=defintentos, type=valida_intentos,
        help='Las veces que se jugará. (def:' + str(defintentos) + ')')
parser.add_argument(
        '-m', '--minimo', default=defminimo, type=int, choices=range(7),
        help='El número mínimo de aciertos necesarios para que se imprima \
        el resultado. (def:' + str(defminimo) + ')')
parser.add_argument(
        '-a', '--apuesta', type=int, choices=range(1, 50), nargs=6,
        help='La apuesta que hace el jugador. \
                Si no se indica será automática.')
parser.add_argument(
        '-g', '--ganadora', type=int, choices=range(1, 50), nargs=6,
        help='Elige la combinación ganadora.')
parser.add_argument(
        '-J', '--real', required=False, action='store_true',
        help='Description for foo argument')

''' La definición del complementario y los reintegros por parte del usuario se
incluyen únicamente para propósitos de depuración y análisis. No forman parte
de un juego real y no sirven para calcular estadísticas reales. Podría ocurrir
que se especificase un complementario que estuviese dentro de la combinación
ganadora, sea ésta definida manualmente o de forma aleatoria.'''

parser.add_argument(
        '-c', '--complementario', type=int, choices=range(1, 50),
        help='Elige el complementario.')
parser.add_argument(
        '-R', '--Reintegro', type=int, choices=range(0, 10),
        help='Elige el reintegro premiado.')
parser.add_argument(
        '-r', '--reintegro', type=int, choices=range(0, 10),
        help='Elige el reintegro en la apuesta del jugador.')


args = parser.parse_args()
maquina = bombo()
jugador = bombo()
resultado = resultados()
premio = idpremio()

if args.real:
    jugar_real()
else:
    jugar_simple()

estadistica()
