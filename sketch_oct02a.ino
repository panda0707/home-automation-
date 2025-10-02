#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "Pranav";
const char* password = "1234567890";

ESP8266WebServer server(80);

// LED pins
int ledPins[] = {D1, D2, D3, D4, D5};
bool ledState[] = {LOW, LOW, LOW, LOW, LOW};

// Function to send HTML page
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'><title>ESP8266 5 LED Control</title></head><body style='text-align:center;font-family:Arial'>";
  html += "<h1>ESP8266 5 Lights Control</h1>";
  html += "<h1>0707</h1>";
  for (int i = 0; i < 5; i++) {
    html += "<p>LED " + String(i+1) + ": ";
    html += "<a href='/led" + String(i) + "on'><button>ON</button></a> ";
    html += "<a href='/led" + String(i) + "off'><button>OFF</button></a></p>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Separate handler functions for each LED
void led0On() { digitalWrite(ledPins[0], HIGH); ledState[0]=HIGH; handleRoot(); }
void led0Off() { digitalWrite(ledPins[0], LOW); ledState[0]=LOW; handleRoot(); }

void led1On() { digitalWrite(ledPins[1], HIGH); ledState[1]=HIGH; handleRoot(); }
void led1Off() { digitalWrite(ledPins[1], LOW); ledState[1]=LOW; handleRoot(); }

void led2On() { digitalWrite(ledPins[2], HIGH); ledState[2]=HIGH; handleRoot(); }
void led2Off() { digitalWrite(ledPins[2], LOW); ledState[2]=LOW; handleRoot(); }

void led3On() { digitalWrite(ledPins[3], HIGH); ledState[3]=HIGH; handleRoot(); }
void led3Off() { digitalWrite(ledPins[3], LOW); ledState[3]=LOW; handleRoot(); }

void led4On() { digitalWrite(ledPins[4], HIGH); ledState[4]=HIGH; handleRoot(); }
void led4Off() { digitalWrite(ledPins[4], LOW); ledState[4]=LOW; handleRoot(); }

void setup() {
  Serial.begin(115200);

  // Set LED pins as output
  for (int i = 0; i < 5; i++) pinMode(ledPins[i], OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Setup routes
  server.on("/", handleRoot);

  server.on("/led0on", led0On);
  server.on("/led0off", led0Off);

  server.on("/led1on", led1On);
  server.on("/led1off", led1Off);

  server.on("/led2on", led2On);
  server.on("/led2off", led2Off);

  server.on("/led3on", led3On);
  server.on("/led3off", led3Off);

  server.on("/led4on", led4On);
  server.on("/led4off", led4Off);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
