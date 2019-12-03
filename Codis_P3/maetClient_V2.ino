#include "ESP8266WiFi.h"
#include <ArduinoJson.h>
WiFiClient client;

StaticJsonDocument<200> doc_out;
StaticJsonDocument<200> doc_in;
const byte initialState = 0;
const byte mainState = 1;
const byte guess_lower = 0;
const byte guess_higher = 1;
const byte guess_correct = 2;

void setup() {
      // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WiFi access point test");
  WiFi.mode(WIFI_STA);
    Serial.println("WiFi ON");
  connectToWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  doc.clear();
  waitForStream();
  deserializeJson(doc_in, client);
  byte state = doc_in["state"];
  Serial.println("State: "+state);
  if(state == initialState){
    Serial.println("Server connected!" 
    Serial.println("Guess a number: ");
    byte guess = Serial.read();
    doc_out["guess"] = guess;
    serializeJson(doc_out, client);
  }
  else if(state == mainState){
    byte guess_feed = doc["guess_feed"];
    if(guess_feed==guess_lower){
      Serial.println("Wrong number. Guess lower");
    }else if(guess_feed==guess_higher){
      Serial.println("Wrong number. Guess higher");
    }else{
      Serial.println("Correct number");
      continue;
    }
    byte guess = Serial.read();
    doc_out["guess"] = guess;
    serializeJson(doc_out, client);
  }
}

/**
 * function that
 */
void connectToWiFi(void){
  int contador = 0;
  if (WiFi.status() != WL_CONNECTED){ // if WiFi not connected
    WiFi.begin("Maet_Server", "guillemRIP"); // connect to WiFi using the ssid and password provided
    while (WiFi.status() != WL_CONNECTED){ // while WiFi not connected
      // wait until we're connected
      delay(1000);
      Serial.println("Connecting...");
      contador++;
      if (contador >= 20){  // if we wait more than 20s, print error
        Serial.println("Error in connection");
        break; 
        }
    }
    if (WiFi.status() == WL_CONNECTED){ // if connected, print local IP
      Serial.println("Connected!");
      Serial.println(WiFi.localIP());
    }
  }  
}

void waitForStream(void){
  while(!client.available());
}
