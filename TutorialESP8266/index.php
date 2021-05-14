<?php

$temperatura = $_GET['temp'];
$humedad = $_GET['hum'];

echo "La temperatura es: " .$temperatura. "<br>la humedad es: " .$humedad;

$usuario = "root";
$contrasena = "root";
$servidor = "localhost";
$basededatos = "tutorial";

$conexion = mysqli_connect( $servidor, $usuario, $contrasena ) or die("No se ha podido conectar con la Base de datos");

$db = mysqli_select_db($conexion, $basededatos) or die ("No se ha podido seleccionar la base de datos");

$fecha = time();
$consulta = "INSERT INTO datos (fecha, temperatura, humedad) VALUES (".$fecha.", " .$temperatura.", " .$humedad.")";

$resultado = mysqli_query($conexion, $consulta);

?>