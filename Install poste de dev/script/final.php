<?php

    if(sizeof($argv) < 1) {
        echo "Error: arguments manquant";
        exit();
    }

    $text = $argv[1];
    $url = $argv[2];
    $code = $argv[3];

    // exec("egrep -i code=fr-[a-z]{3} < ./Ressources_client_Textes-20221212/{$text} | cut -d'=' -f2 ", $res);

    exec("php ./script/tmp.php {$argv[1]}");

    // exec("php ./script/scriptQRCode {$res[0]} {$url}");

    exec("php ./script/script1.php ./résultatTexte/texte.dat ./résultatTexte/tableau.dat ./résultatTexte/comm.dat ./regions.conf {$code}", $html);

    print_r($html);

?>