#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "	MEGACABLE-049F";
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

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

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
}
