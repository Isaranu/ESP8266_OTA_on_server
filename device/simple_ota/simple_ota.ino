#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#define USE_SERIAL Serial

#ifndef APSSID
#define APSSID "your-wifi-ssid"
#define APPSK  "your-wifi-password"
#endif

String otaversion = "1.0";
int cnt=0;

ESP8266WiFiMulti WiFiMulti;

void ota(String vers){

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

    t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://35.234.200.103:5000/ota/" + vers);
    
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        USE_SERIAL.println("HTTP_UPDATE_OK");
        break;
    }
  }
}

void setup() {

  USE_SERIAL.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(APSSID, APPSK);
  
  Serial.println("WiFi connecting..");
  while(WiFiMulti.run() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("connected !");

}

void loop() {
  Serial.println("cnt = " + String(cnt));
  if(cnt == 5){
    ota("special");
    cnt = 0;
  }
  cnt++;
  delay(1000);
}
