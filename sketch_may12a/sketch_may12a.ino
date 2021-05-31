#include <dummy.h>
#include <Arduino.h>

#include <HTTPClient.h>
#include <WiFi.h>

//Información de conexión WiFi
const char* ssid = "Amobladosdh711";
const char* password = "A30E8B7AC43477EB";
const char* host = "192.168.0.16";
const int port = 80;
const int watchdog = 5000;
unsigned long previousMillis = millis();

//Pin donde esta conectado el led
int led = 2;

WiFiServer server(80);

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

  server.begin();
  Serial.println("Server started");

  Serial.println("IP address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

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
    WiFiClient client = server.available();

    /*if (!client.connect(host, port)) {
      Serial.println("Fallo al conectar");
      return;
      }*/

    if (!client) {
      return;
    }

    // Wait until the client sends some data
    Serial.println("new client");
    while (!client.available()) {
      delay(1);
    }
/*
    String url = "/TutorialESP8266/info.php?temp=";
    url += t;
    url += "&hum=";
    url += h;

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    delay(500);

*/
    // Leemos la primer línea de la solicitud y la guardamos en la variable string request
    String request = client.readStringUntil('\r');
    Serial.println(request); //Imprimimos la solicitud
    client.flush(); //Descartamos los datos que se han escrito en el cliente y no se han leído

    // Relacionamos la solicitud
    int value = LOW;
    if (request.indexOf("/LED=OFF") != -1) {
      Serial.println("1");
      value = HIGH;
    }
    if (request.indexOf("/LED=ON") != -1) {
      value = LOW;
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");

    client.print("Led pin is now: ");

      if (value == HIGH) {
      client.print("On");
    } else {
      client.print("Off");
    }
    client.println("<br><br>");
    client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
    client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
    client.println("</html>");

    delay(1);
    Serial.println("Client disonnected");
    Serial.println("");

  }
}
