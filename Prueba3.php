<!DOCTYPE html>
<html lang="es">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" type="text/css" href="dist/bootstrap-clockpicker.min.css">
    <script type="text/javascript" src="dist/bootstrap-clockpicker.min.js"></script>
    <meta charset="utf-8">
    <script src="https://code.jquery.com/jquery-3.2.1.min.js" type="text/javascript"></script>
    <script type="text/javascript">
        $(function() { //document.ready es obsoleto desde jQuery 3
            $('#tck').on('submit', function(e) {
                e.preventDefault();
                var data = $(this).serialize();
                var request = $.ajax({
                    url: $(this).prop("action"),
                    method: $(this).prop('method'),
                    data: data,
                    dataType: "html"
                });

                request.done(function(response) {
                    console.log(response);
                        $('.response').html(response);
                });
                request.fail(function(jqXHR, textStatus) {
                    alert('Hubo un error: ' + textStatus);
                });
            });
        });
    </script>
  </head>
  <body>
    <div class="container">
      <CENTER>
        <div class="page-header">
          <h1>Horarios Invernaderos</h1>
        </div>
      </CENTER>
      <div class="row">
        <div class="col-sm-2"></div>
        <div class="col-sm-8">
          <CENTER>
            <form id="tck" method="POST" action="Prueba2.php">
            <input type="text" name="selectInver">
            <button type="submit">Ingresar</button>
        </form>
        <div class='response' id='respuesta'></div>
          </CENTER>
        </div>
        <div class="col-sm-2"></div>
      </div>
    </div>
  </body>
</html>
