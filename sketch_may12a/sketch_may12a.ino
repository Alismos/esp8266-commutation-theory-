#include <WiFi.h>

//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------Credenciales de WiFi-----------------------

const char* ssid     = "Amobladosdh711";
const char* password = "A30E8B7AC43477EB";

//---------------------VARIABLES GLOBALES-------------------------
const int LED1 = 13;
const int LED2 = 12;

char linebuf[80];
int charcount = 80;




//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.printf("Conectando a: %s\n", ssid);
  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando... ");
    delay(2000);
  }

  Serial.println("Conectado. ");
  Serial.print("Dirección IP del estado: ");
  Serial.print(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) { // If a new client connects,
    Serial.println("Nuevo Cliente"); // print a message out in the serial port
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    boolean currentLineIsBlank=true;
    
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c); // print it out the serial monitor
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++; // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          
          if (c == '\n' && currentLineIsBlank) {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML><html><head>"); 
          client.println("<body style=\"background-color:#0066aa:\">");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1><style=\"width:500px;height:20px;color:#ffffff;\"> Tutorial Web Server ESP32 </h1>");
          client.println("<p style=\"color:#ffffff\"> LED #1 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button><a/></p>");
          client.println("<p style=\"color:#ffffff\"> LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button><a/></p>");
          client.println("</html>");
          break;
          }
          
          // turns the GPIOs on and off
          if (c == '\n') {
            currentLineIsBlank = true;
          if(strstr(linebuf,"GET /on1")>0){
            Serial.println("LED 1 ON");
            digitalWrite(LED1, HIGH);
          }
          else if(strstr(linebuf,"GET /off1")>0){
            Serial.println("LED 1 OFF");
            digitalWrite(LED1, LOW);
          }
          else if(strstr(linebuf,"GET /on2")>0){
            Serial.println("LED 2 ON");
            digitalWrite(LED2, HIGH);
          } 
          else if(strstr(linebuf,"GET /off2")>0){
            Serial.println("LED 2 OFF");
            digitalWrite(LED2, LOW);
          }
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        } else if (c != '\r'){
            currentLineIsBlank = false;
          }
        }
    }
    delay(1);
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
