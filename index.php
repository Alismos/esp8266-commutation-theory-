<?php

$usuario = "root";
$contrasena = "root";
$servidor = "localhost";
$basededatos = "tutorial";

$conexion = mysqli_connect( $servidor, $usuario, "" ) or die ("No se ha podido conectar al servidor de Base de datos");

$db = mysqli_select_db( $conexion, $basededatos ) or die ( "No se ha podido seleccionar la base de datos" );


?>

<!DOCTYPE html>
<html>
<head>
 <title> Datos</title>
</head>
<body>
<br>
<table border="1">
 <tr>
  <td> Fecha </td>
  <td> Temperatura </td>
  <td> Humedad </td>
 </tr>
 <?php
 $sql="SELECT * from datos";
 $result=mysqli_query($conexion, $sql);
  while($mostrar=mysqli_fetch_array($result)){
    ?>
    <tr>
    <td> <?php echo $mostrar['fecha']?> </td>
    <td> <?php echo $mostrar['temperatura']?></td>
    <td> <?php echo $mostrar['humedad']?></td>
   </tr>

  <?php
  }
 ?>
</table>
</body>
</html>