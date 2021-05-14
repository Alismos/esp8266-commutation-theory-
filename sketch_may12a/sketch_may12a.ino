#include <ESP8266WiFi.h>
const char* ssid = "Carolina 1";
const char* password = "1020724058";
const char* host = "192.168.0.25";
const int port = 80;
const int watchdog = 5000;
unsigned long previousMillis = millis();
void setup(void)
{ 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.begin(9600);
  Serial.println("Humedad y Temperatura\n\n");
  delay(700);

}

void loop() {
    float h = random(1,100);
    float t = random(1,100);         
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

    String url = "/TutorialESP8266/index.php?temp=";
    url += t;
    url += "&hum=";
    url += h;

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
}
}
