<?php

   if(sizeof($argv) < 5) {
      echo "Error: arguments manquant";
      exit();
   }

   $text = file($argv[1]);
   $stat = file($argv[2]);
   $nom = file($argv[3]);
   $regions = file($argv[4]);
   $codeRegion = $argv[5];

   date_default_timezone_set('Europe/Paris');
?>

<!DOCTYPE html>
<html lang="en">
<head>
   <meta charset="UTF-8">
   <meta http-equiv="X-UA-Compatible" content="IE=edge">
   <meta name="viewport" content="width=device-width, initial-scale=1.0">
   <title>PDF</title>
   <link rel="stylesheet" href="../Web/htmlStatic.css">
</head>
<body>
   <section>
      <?php
      foreach($regions as $region) {
         $line_array = explode(";", $region);
         if($line_array[0] == $codeRegion) {
            $code = $line_array[0];
            $nom = $line_array[1];
            $pop = $line_array[2];
            $superficie = $line_array[3];
            $nb_dep = $line_array[4];
         };        
      }

      ?>
      <div class="content">
         <?php
            echo '
            <h1>'.$nom.'</h1>
            <h2>'.$pop.'</h2>
            <h2>'.$superficie.'</h2>
            <h2>'.$nb_dep.'</h2>
            <img src="./'.$code.'.png">
            '
         ?>
      </div>
      <div class="bottom"><?php echo date("d-m-Y H:i"); ?></div>
   </section>
   <section>
      <div class="content">
         <h1>Résultat Trimestriel <?php echo date("m-Y") ?></h1>
         <?php 
            foreach($text as $texte){
               echo $texte;
         }?>
         <table>
            <tr>
               <th>Produit</th>
               <th>Ventes</th>
               <th>Chiffre d'affaires</th>
               <th>Ventes année précédente</th>
               <th>CA année précédente</th>
               <th>Évolution</th>
            </tr>
            <?php 
            foreach($stat as $produits){
               $line_array1 = explode(',', $produits);
               $nom_prod = $line_array1[0];
               $vente = $line_array1[1];
               $CA = $line_array1[2];
               $vente_an = $line_array1[3];
               $CA_an = $line_array1[4];
               $evolution = (($CA / $CA_an) * 100) - 100;number_format($nombre, 2, '.', '');
               $evolution = number_format($evolution, 2, '.', '');

               echo '
               <tr>
                  <td>'.$nom_prod.'</td>
                  <td>'.$vente.'</td>
                  <td>'.$CA.'</td>
                  <td>'.$vente_an.'</td>
                  <td>'.$CA_an.'</td>'
                  .($evolution < 0 ? '<td class ="down">'.abs($evolution).'%'.'</td>' : '<td class ="up">'.abs($evolution).'%'.'</td>');
               '<tr>';
            }
            ?>
         </table> 
      </div>
      <div class="bottom"><?php echo date("d-m-Y H:i"); ?></div>
   </section>
   <section>
      <div class="content">
         <h1>Nos meilleurs vendeurs du trimestre</h1>
         <div class="best">
            <div class="bestSeller">
            <?php
               $tableau = array();

               $nom = file($argv[3]);

               foreach ($nom as $line) {
                  list($nomPrenom, $chiffreAffaires) = explode(";", $line);
                  $tableau[$nomPrenom] = $chiffreAffaires;
               }
               arsort($tableau);
               $i = 0;
               foreach($tableau as $key => $money) {
                  if ($i < 3){
                     $nomFamille = explode(" ", $key);
                     $PrenomLettre = strtoupper(substr($key, 0, 2));
                     $NomLettre = strtoupper(substr($nomFamille[1], 0, 1));
                     $PrenomLettre = strtolower($PrenomLettre);
                     $NomLettre = strtolower($NomLettre);     
                      
                     echo '
                     <img src="../Ressources_client_Photos-20221212/'.$NomLettre.$PrenomLettre.'.png">'.
                     '<div class="name">
                        <a>'.$key.'</a>
                     </div>
                     <div class="ca">
                        <a>'.$money.'</a>
                     </div>
                     ';
                  }
                  $i++;
               }
               ?>
            </div>
         </div>
      </div>
      <div class="bottom"><?php echo date("d-m-Y H:i"); ?></div>
   </section>
   <section>

      <div class="content">
         <h1>Le lien vers BigBrain</h1>
         <a href="https://bigbrain.biz/<?php echo $codeRegion ?>">https://bigbrain.biz/<?php echo $codeRegion ?></a>
         <img src="./code.png">
      </div>
      <div class="bottom"><?php echo date("d-m-Y H:i"); ?></div>
   </section>
</body>
</html>

