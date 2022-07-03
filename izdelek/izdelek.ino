/* ESP32 AJAX Demo
   Updates and Gets data from webpage without page refresh
   https://circuits4you.com
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

//#include <ESPAsyncWebServer.h>
//#include <SPIFFS.h>

#include "index.h"  //Web page header file

//AsyncWebServer server(80);
WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "Puntar2G";
//const char* ssid = "Klavdij's iPhone";
const char* password = "11111111";

//Imena pinov
const int trigPin = 14;
const int echoPin = 25;
const int Motorcek = 19;

//Imena spremenljivk
long duration;
int distance;

const int mejarezervoarja = 13;


unsigned long previousMillis = 0;
const long interval = 5000;


int vlaznost;
int razdalja;
int mejavlaznosti;
float casovnik = millis();

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================


void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handleADC() {
  int a = analogRead(34);
  String adcValue = String(a);

  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}



void VzgiMotorcek() {
  //if(casovnik < 21000){
  if (digitalRead(Motorcek) != HIGH) {
    digitalWrite(Motorcek, HIGH);
    //Serial.println("pali11");
  //}
  }
}
void UgasniMotorcek() {
  /*
  if (digitalRead(Motorcek) != LOW) {
    digitalWrite(Motorcek, LOW);
  }
  */
  digitalWrite(Motorcek, LOW);
  //delay(10000);
}


int readMejaVlaznosti() {
  String preberi = server.arg("MoistState");
  //Serial.println(preberi);
  server.send(200, "text/plane", preberi);
  int i;
  
  mejavlaznosti = preberi.toInt();

 //mejavlaznosti = i;
//Serial.println("1");
  //server.send(200,"text/plane", preberi);
  return i;
  
}

void readMoistureSensor() {
  int humidityRaw = analogRead(34);
  String humidityValue = String(humidityRaw);
  server.send(200, "text/plane", humidityValue);


  vlaznost = humidityRaw;
  Serial.println(vlaznost);
}

void readUltrasonicSensor() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = ((duration * 0.034 / 2));

  String distanceValue = String(distance);
  server.send(200, "text/plane", distanceValue);

  razdalja = distance;
    //Serial.println("3");
}



//===============================================================
// Setup
//===============================================================

void setup(void) {
  Serial.begin(115200);

  int mejavlaznosti = 1400;

  pinMode(Motorcek, OUTPUT); //PUMPA
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.println();
  Serial.println("Booting Sketch...");

  /*
    //ESP32 As access point
    WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(ssid, password);
  */

  //ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  //----------------------------------------------------------------

  //server.on("/humidity", readMoistureSensor);

  server.on("/", handleRoot);      //This is display page
  server.on("/setMeja", readMejaVlaznosti);
  server.on("/readHumidity", readMoistureSensor);//To get update of ADC Value only
  server.on("/readDistance", readUltrasonicSensor);
  //server.on("/setMeja", readMejaVlaznosti);



  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void) {
  server.handleClient();
  delay(1);
  unsigned long currentMillis = millis();


if (currentMillis - previousMillis >= interval) {
  Serial.println("sedaj gledam");
  previousMillis = currentMillis;

  if(distance < mejarezervoarja-4)
  {
    mejavlaznosti = 1500;
    if(vlaznost > mejavlaznosti){
          VzgiMotorcek();
          delay(1000);
          UgasniMotorcek();
        }
        else{
          UgasniMotorcek();
        }
  }
  else {
    UgasniMotorcek();
  }
  
}
  //Serial.println(analogRead(34));
}
