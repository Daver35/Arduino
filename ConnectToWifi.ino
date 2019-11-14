#include "ESP8266WiFi.h"

char c_ssid[50], c_pwd[50];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.println("Setup start");
  wifiNetworkSelection();
  connectToWiFi();
  Serial.println("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  long rssi = WiFi.RSSI();
  Serial.print("RSSI > ");
  Serial.println(rssi);
  delay(1000);
}

void connectToWiFi(void){
  int contador = 0;
  if (WiFi.status() != WL_CONNECTED){
    //WiFi.begin(c_ssid, c_pwd);
    WiFi.begin("DAVER", "delapaxx");
    while (WiFi.status() != WL_CONNECTED){
      delay(1000);
      Serial.println("Connecting...");
      contador++;
      if (contador >= 20){ 
        Serial.println("Error in connection");
        break; 
        }
    }
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());
  }  
}

void wifiNetworkSelection(void){
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("SSID? >");
    while(!Serial.available());
    String ssid = Serial.readString();
    ssid.toCharArray(c_ssid, 50);
    Serial.print("SSID selected > ");
    Serial.print(ssid);
    delay(1000);
    Serial.print("Password? > ");
    while(!Serial.available());
    String password = Serial.readString();
    password.toCharArray(c_pwd, 50);
    Serial.println("PWD > ");
    Serial.println(password);
    delay(1000);
  }  
}
