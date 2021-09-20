<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <title>Traitement du formulaire en PHP</title>
    </head>

    <body>
        <h2>Résultat</h2>
<?php
// on vérifie que la variable existe et que c'est bien un nombre
if (isset($_GET["Nombre"]) && is_numeric($_GET["Nombre"]))
{
    //print_r($_SERVER["QUERY_STRING"]);
    $nombre = $_GET["Nombre"];
    //$nombre = 2;
    $resultat = $nombre*$nombre;
    print "<p>Le carré de <strong>$nombre</strong> est <strong>$resultat</strong></p>";
}
 else
{
    print "<p>Valeur invalide !</p>";
}
?>
    </body>
</html>