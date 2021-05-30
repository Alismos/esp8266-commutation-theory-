#include <dummy.h>
#include <Arduino.h>

#include <HTTPClient.h>
#include <WiFi.h>

//Información de conexión WiFi
const char* ssid = "NCESCOBAR";
const char* password = "NoracanoM43602553";
const char* host = "192.168.1.5";
const int port = 80;
const int watchdog = 5000;
unsigned long previousMillis = millis();

//Pin donde esta conectado el led
int led = 2;


void setup()
{
  delay(10);
  Serial.begin(115200);

  pinMode(led, OUTPUT); //Declaramos el pin del led como saldia
  digitalWrite(led, LOW); //Iniciamos con el led apagado

  //Iniciamos la conexión WiFi

  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  Serial.println("Humedad y Temperatura\n\n");

}

void loop() {
  float h = random(1, 100);
  float t = random(1, 100);
  Serial.print("Humedad = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("Temperatura = ");
  Serial.print(t);
  Serial.println("°C  ");
  delay(800);

  unsigned long currentMillis = millis();

  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
    }

    String url = "/TutorialESP8266/info.php?temp=";
    url += t;
    url += "&hum=";
    url += h;

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    delay(500);

    if (client.available()) {
      // Leemos la primer línea de la solicitud y la guardamos en la variable string request
      String request = client.readStringUntil('\r');
      Serial.println(request); //Imprimimos la solicitud
      client.flush(); //Descartamos los datos que se han escrito en el cliente y no se han leído

      // Relacionamos la solicitud
      if (request.indexOf("/LED=OFF") != -1) {
        digitalWrite(ledPin, LOW);
      }
      if (request.indexOf("/LED=ON") != -1) {
        digitalWrite(ledPin, HIGH);
      }
    }
    
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

  }
}
