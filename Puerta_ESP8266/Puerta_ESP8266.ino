#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

String textoSerial = "";
const char* ssid = "MEGACABLE-049F";
const char* password = "hw722qVC";

ESP8266WebServer server(80);

const int ledPin = 2; // Pin donde está conectado el LED
Servo myservo;
int servoPin = D1; // Pin D1 del ESP8266

void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin); // Adjunta el servo al pin correspondiente
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   delay(1000);
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); 
  Serial.println("conectado");

  server.on("/encender", []() {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000); // Esperar un segundo
    server.send(200, "text/plain", "LED encendido");
    Serial.println("Encendido");
  });

  server.on("/apagar", []() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // Esperar un segundo
    server.send(200, "text/plain", "LED apagado");
    Serial.println("Apagado");
  });

      server.on("/abrir", []() {
    myservo.write(0);
    delay(1000); // Esperar un segundo
    server.send(200, "text/plain", "Puerta abierta");
    Serial.println("Encendido");
  });

  server.on("/cerrar", []() {
    myservo.write(180);
    delay(1000); // Esperar un segundo
    server.send(200, "text/plain", "Puerta cerrada");
    Serial.println("Apagado");
  });


  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
if (Serial.available() > 0) {
  textoSerial = Serial.readString();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi is unavailable");
    return;
  }
}}
