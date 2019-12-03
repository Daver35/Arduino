#include "ESP8266WiFi.h"
#include <ArduinoJson.h>

WiFiClient client;
WiFiServer server(80);

const int postingInterval = 1 * 1000; // post data every 20s

StaticJsonDocument<200> doc;
const byte initialState = 0;
const byte mainState = 1;
const byte guess_lower = 0;
const byte guess_higher = 1;
const byte guess_correct = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WiFi access point test");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Maet_Server", "guillemRIP");
  Serial.println("WiFi ON");
  server.begin();
}

int state = 0;
byte number;

void loop() {
  // put your main code here, to run repeatedly:
  /*client = */
  WiFiClient client = server.available();
  if(client && client.connected()){
    doc.clear();
    Serial.print("State: ");
    Serial.println(state);
    if(state == initialState){//Send
      number = 5;
      doc["state"] = state;
      serializeJson(doc, client);
      state = mainState;    
    }else if(state == mainState){
      //waitForStream();
      Serial.print("-->");
      deserializeJson(doc, client);
      byte guess = doc["guess"];
      if (guess < number){
        doc["state"] = state;
        doc["guess_feed"] = guess_higher;
      }else if(guess > number){
        doc["state"] = state;
        doc["guess_feed"] = guess_lower;
      }else{
          doc["state"] = state;
        doc["guess_feed"] = guess_correct;
        state = initialState;
      }
      serializeJson(doc, client);
    }
  }
  delay(postingInterval);
}

void waitForStream(void){
  while(client.available()==0);
}
