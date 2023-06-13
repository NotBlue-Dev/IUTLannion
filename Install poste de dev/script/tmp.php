<?php 
    $fic_in = fopen($argv[1], 'r');
    $fic_out_text = fopen('./résultatTexte/texte.dat', 'w');
    $fic_out_stat = fopen('./résultatTexte/tableau.dat', 'w');
    $fic_out_nom = fopen('./résultatTexte/comm.dat', 'w');
    $fic_out_cred = fopen('./résultatTexte/cred.dat', 'w');
    $ligne = '';

    
    $ligne = fgets($fic_in);
    while (!feof($fic_in)) {
        if ((strpos($ligne, 'SOUS_TITRE') !== false) || (strpos($ligne, 'Sous_titre') !== false)) {
            fwrite($fic_out_text, substr($ligne,11));
            $ligne = fgets($fic_in);
        }
        if ((strpos($ligne, 'TITRE') !== false) || (strpos($ligne, 'Titre') !== false)) {
            fwrite($fic_out_text, substr($ligne,6));
            $ligne = fgets($fic_in);
        }
        if ((strpos($ligne, 'DEBUT_TEXTE') !== false) || (strpos($ligne, 'Début_texte') !== false)) {
            $ligne = fgets($fic_in);
            while ((strpos($ligne, 'FIN_TEXTE') === false) && (strpos($ligne, 'Fin_texte') === false)) {
                fwrite($fic_out_text, $ligne);
                $ligne = fgets($fic_in);
            }
            fwrite($fic_out_text, "\n");
        }

        if ((strpos($ligne, 'DEBUT_STATS') !== false) || (strpos($ligne, 'Début_stats') !== false)) {
            $ligne = fgets($fic_in);
            while ((strpos($ligne, 'FIN_STATS') === false) && (strpos($ligne, 'Fin_stats') === false)) {
                fwrite($fic_out_stat, $ligne);
                $ligne = fgets($fic_in);
            }
        }

    if ((strpos($ligne, 'MEILLEURS') !== false) || (strpos($ligne, 'Meilleurs') !== false)) {
	$persons = explode(',', $ligne);
	foreach ($persons as $person) {
	    $name_surname = explode('/', $person);
	    $money = explode('=', $name_surname[1]);
	    $name = $money[0];
	    fwrite($fic_out_nom, $name.";".$money[1] . "\n");
	    }
	}

        if ((strpos($ligne, 'DEBUT_CREDITS') !== false) || (strpos($ligne, 'Début_crédits') !== false)) {
            $ligne = fgets($fic_in);
            while ((strpos($ligne, 'FIN_CREDITS') === false) && (strpos($ligne, 'Fin_crédits') === false)) {
                fwrite($fic_out_cred, $ligne);
                $ligne = fgets($fic_in);
            }
        }
        $ligne = fgets($fic_in);
    }   
    fclose($fic_in);
    fclose($fic_out_text);
    fclose($fic_out_stat);
    fclose($fic_out_nom);
    fclose($fic_out_cred);
?>

docker container run -ti --rm -v C:\Users\enzod\Desktop\IUT\systeme\SAE\SAE:/work bigpapoo/sae103-php php -f ./script/final.php Bourgogne-Franche-Comté.txt C:\Users\enzod\Desktop\IUT\systeme\SAE\SAE