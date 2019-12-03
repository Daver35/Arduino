#include "ESP8266WiFi.h"
WiFiClient client;

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
  String feedback = client.readString();
  Serial.println(feedback);
  byte output = Serial.read();
  client.write(output);
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
