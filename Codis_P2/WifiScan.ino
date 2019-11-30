#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(9600); // open the serial port 9600 b/s
  WiFi.mode(WIFI_STA); // configure STA mode
  WiFi.disconnect(); // disconnect WiFi shield from current network
  delay(2000); // wait 2s
  Serial.println("Setup done");
}

void loop() {
  Serial.println("Scan start");

  int n = WiFi.scanNetworks(); // detect number of networks available
  Serial.println("Scan done");
  if(n==0) // if no networks found, print message
    Serial.println("No networks found");
  else{
    for(int i = 0; i<n; i++){ // for each network found
      //print SSID, RSSI and encryption type of each network
      Serial.print(i+1);
      Serial.print(WiFi.SSID(i));
      Serial.print("(");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10); 
    }
  }
  Serial.println("********************");
  //Wait before scanning again
  delay(5000);
}
