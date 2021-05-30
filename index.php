<?php

$usuario = "root";
$contrasena = "root";
$servidor = "localhost";
$basededatos = "teoriacomp";

$conexion = mysqli_connect($servidor, $usuario, $contrasena) or die("No se ha podido conectar al servidor de Base de datos");

$db = mysqli_select_db($conexion, $basededatos) or die("No se ha podido seleccionar la base de datos");


?>

<!DOCTYPE html>
<html>

<head>
  <title> Datos</title>
</head>

<style>
  * {
    font-family: sans-serif;
  }

  .btn-two {
    margin: 9px;
  }

  .btn-two.green {
    background-color: #009879;
  }

  .btn-two.red {
    background-color: #fa5a5a;
  }

  .btn-two {
    color: white;
    padding: 15px 25px;
    display: inline-block;
    border: 1px solid rgba(0, 0, 0, 0.21);
    border-bottom-color: rgba(0, 0, 0, 0.34);
    text-shadow: 0 1px 0 rgba(0, 0, 0, 0.15);
    box-shadow: 0 1px 0 rgba(255, 255, 255, 0.34) inset,
      0 2px 0 -1px rgba(0, 0, 0, 0.13),
      0 3px 0 -1px rgba(0, 0, 0, 0.08),
      0 3px 13px -1px rgba(0, 0, 0, 0.21);
  }

  .btn-two:active {
    top: 1px;
    border-color: rgba(0, 0, 0, 0.34) rgba(0, 0, 0, 0.21) rgba(0, 0, 0, 0.21);
    box-shadow: 0 1px 0 rgba(255, 255, 255, 0.89), 0 1px rgba(0, 0, 0, 0.05) inset;
    position: relative;
  }

  .content-table {
    border-collapse: collapse;
    margin: 25px 0;
    font-size: 0.9em;
    min-width: 250px;
    border-radius: 5px 5px 0 0;
    overflow: hidden;
    box-shadow: 0 0 20px rgba(0, 0, 0, 0.15);
  }

  .content-table thead tr {
    background-color: #009879;
    color: #ffffff;
    text-align: left;
    font-weight: bold;
  }

  .content-table th,
  .content-table td {
    padding: 12px 15px;
  }

  .content-table tbody tr {
    border-bottom: 1px solid #dddddd;
  }

  .content-table tbody tr:nth-of-type(even) {
    background-color: #f3f3f3;
  }

  .content-table tbody:last-of-type {
    border-bottom: 2px solid #009879;
  }

  .content-table tbody tr.active-row {
    font-weight: bold;
    color: #009879;
  }
</style>


<body>
  <a onclick=location.href="/LED=ON" class="btn-two green">Encender</a>
  <a onclick=location.href="/LED=OFF" class="btn-two red">Apagar</a>
  <table class="content-table">
    <thead>
      <tr>
        <td> Fecha </td>
        <td> Temperatura </td>
        <td> Humedad </td>
      </tr>
    </thead>
    <tbody>
      <?php
      $sql = "SELECT * from datos";
      $result = mysqli_query($conexion, $sql);
      while ($mostrar = mysqli_fetch_array($result)) {
      ?>
        <tr class="active-row">
          <td> <?php echo $mostrar['fecha'] ?> </td>
          <td> <?php echo $mostrar['temperatura'] ?></td>
          <td> <?php echo $mostrar['humedad'] ?></td>
        </tr>
      <?php
      }
      ?>
    </tbody>
  </table>
</body>

</html>