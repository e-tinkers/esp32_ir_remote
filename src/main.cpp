#include <Arduino.h>
#include <IRremote.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <SHT21.h>

// replace the ssid and password
const char* ssid     = "your_WiFi_SSID";
const char* password = "your_WiFi_password";
const int port = 80;

// replace staticIP and gateway address based on your home router settings
IPAddress staticIP(192, 168, 0, 200);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

SHT21 SHT21;

String request;
DynamicJsonDocument doc(200);
AsyncWebServer server(port);
static char sensorStatus[50];

byte SEND_PIN = 5;
IRsend irsend(SEND_PIN);
unsigned long infraRedCode[] = {
  0xE0E040BF, //tv on-off
  0xE0E0807f, //tv source
  0x807F827D, //set-top volume up
  0x807FE817, //set-top channel up
  0x807F48B7, //set-top mute
  0x807F42BD, //set-top volume down
  0x807F58A7, //set-top channel down
  0x807F807F  //set-top on-off
};


void connectToWiFi() {
    Serial.begin(115200);
    Serial.printf("Connecting to WiFi %s\n", ssid);
    WiFi.config(staticIP, gateway, subnet);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
}


void onTemperature(AsyncWebServerRequest *request) {
    JsonObject object = doc.to<JsonObject>();
    object["temperature"] = SHT21.getTemperature();
    object["humidity"] = SHT21.getHumidity();
    serializeJson(doc, sensorStatus);
    Serial.println(sensorStatus);
    request->send(200, "application/json", sensorStatus);
}


void onRequest(AsyncWebServerRequest *request) {
    // dummy callback function for handling params, etc.
}


void onFileUpload(AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {
    // dummy callback function signature, not in used in our code
}


void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    DeserializationError error = deserializeJson(doc, (char*)data);
    if (!error) {
      const char* command = doc["command"];
      uint8_t code = atoi(doc["code"]);
      int codeType = infraRedCode[code] >> 16;
      Serial.printf("command=%s, code=0x%lx, protocol=", command, infraRedCode[code]);
      switch (codeType) {
        case 0xE0E0:
          irsend.sendSAMSUNG(infraRedCode[code], 32);
          Serial.println("Samsung");
          break;
        case 0x807F:
          irsend.sendNEC(infraRedCode[code], 32);
          Serial.println("NEC");
          break;
      }
      request->send(200, "text/plain", "Ok");
    }
}


void setup() {

    // Connect to WiFi
    connectToWiFi();

    SHT21.begin();

    // Initialize SPIFFS (SPI Flash File System)
    SPIFFS.begin(true);

    // serving static content for GET requests on '/' from SPIFFS directory '/'
    server.serveStatic("/", SPIFFS, "/")
          .setDefaultFile("index.html")
          .setCacheControl("max-age=86400");

    server.on("/temperature", HTTP_GET, onTemperature);

    server.on("/api", HTTP_POST, onRequest, onFileUpload, onBody);

    server.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
    });

    server.begin();

}


void loop(){

}
