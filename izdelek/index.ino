const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>

  <style>
    html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
    .button {background-color: #4CAF50;border: none;color: white;padding: 15px 32px;
      text-align: center;text-decoration: none;display: inline-block;font-size: 16px;
      margin: 4px 2px;cursor: pointer;}
</style>
<body>
    <div class="card">
        <h4>Vodna zalivalka</h4><br>
        <h1>Vlažnost:<span id="humidityvalue">0</span></h1><br>
        <h1>Razdalja:<span id="distancevalue">0</span></h1><br>
        <!--
        <h1>Nastavljena meja vlažnosti:<span id="MejaState">1400</span></h1><br>
        <button type="button" onclick="Povecaj();">Povecaj</button>
        <button type="button" onclick="Zmanjsaj();">Zmanjsaj</button>
        <h1>nova:<span id="nova">0</span></h1><br>-->
    </div>


    <form>
      <span>Vlažnost</span> <input type="number" id="MejaState" value="1400"/> </br>
      <input type="button" onclick="Povecaj()" value="Povecaj za 50" />
      <input type="button" onclick="Zmanjsaj()" value="Zmanjsaj za 50" />
   </form>
    
    <script>
function Povecaj(){
    var value = parseInt(document.getElementById('MejaState').value,10);
    //value = isNaN(value)? 0 : value;
    value += 50;
    document.getElementById('MejaState').value = value;
/*
    var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("MejaState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setMeja?Mejastate="+value, true);
  xhttp.send();*/
}
function Zmanjsaj(){
  var value = parseInt(document.getElementById('MejaState').value,10);
    //value = isNaN(value)? 0 : value;
    value -= 50;
    document.getElementById('MejaState').value = value;

  /*var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("MejaState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setMeja?Mejastate="+value, true);
  xhttp.send();*/
}

  



setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData_02();
  getData();
  getData_01();
}, 10); //2000mSeconds update rate


function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidityvalue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readHumidity", true);
  xhttp.send();
}
function getData_01() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("distancevalue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readDistance", true);
  xhttp.send();
}
function getData_02(){
  var value = parseInt(document.getElementById('MejaState').value,10);
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //document.getElementById("MejaState").innerHTML =
      //this.responseText;
    }
  };
  xhttp.open("GET", "setMeja?MoistState="+value, true);
  xhttp.send();
  
}


</script>
</body>
</html>
)=====";
