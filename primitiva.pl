#!/usr/bin/perl
# primitiva: Jugar a la lotería primitiva.

sub juega {
	@bombo		= (1..49); # Entran los números del 1 al 49.
	@mibombo	= @bombo; # Entran los números del 1 al 49.
	$acierto	= 0;

	$reintegro	= int(rand(9)); # Reintegro de 0 al 9.
	$mireintegro	= int(rand(9)); # Me lo da la máquina.

	$r=" + el reintegro: ($mireintegro)" if ($mireintegro == $reintegro);


	for(0..6) {
		$num		= int(rand($#bombo));
		$premio[$_]	= splice(@bombo, $num, 1);
	}

	$complementario=pop(@premio);

	sub juego_maquina {
		for(0..5) {
			$num		= int(rand($#mibombo));
			$mipremio[$_]	= splice(@mibombo, $num, 1);
		}
	}

# Para probar mi propia combinación:
	if ($#ARGV == 5) { @mipremio = @ARGV } else { juego_maquina }

	for my $apuesta (@mipremio) { # Para cada número que he jugado...
		for(@premio) { # Comprobar si está en la combinación ganadora.
			if ($apuesta == $_) {
				$aciertos[$acierto] = $apuesta;
				$acierto++; # Y sumar los aciertos.
			}
		}

		$c=" + el complementario: ($complementario)" if ($complementario == $apuesta);
	}

	@aciertos	= sort @aciertos;
	@premio		= sort @premio;
	@mipremio	= sort @mipremio;

}


sub all {
	juega;
	print "$acierto aciertos\t\t(@aciertos)$c$r.\n";
	print "Combinación ganadora:\t@premio ($complementario) [$reintegro].\n";
	print "Apuestas:\t\t@mipremio [$mireintegro].\n";
}

sub proba {
	my $req = $ARGV[0];
	my $tries = $ARGV[1];
	my $c = 0;

	print "Mostrando resultados con $req aciertos o más...\n\n";

	for (0..$tries) {
		juega;
		if ($acierto >= $req ) {
			print "$acierto aciertos\t(@aciertos)$c$r.\n";
			$c++;
		}
	}

	print "\n$tries intentos. $c resultados satisfactorios.\n";
}

if ($#ARGV == 1) {
	proba;
} else {
	all;
}
