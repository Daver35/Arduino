#include "ESP8266WiFi.h"

char c_ssid[50], c_pwd[50]; // create char vectors for ssid and password

void setup() {
  Serial.begin(9600); // open the serial port 9600 b/s
  WiFi.mode(WIFI_STA); // configure STA mode
  WiFi.disconnect(); // disconnect WiFi shield from current network

  Serial.println("Setup start");
  wifiNetworkSelection(); // call wifiNetworkSelection() function
  connectToWiFi(); // call connectToWiFi() function
  Serial.println("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  long rssi = WiFi.RSSI();
  Serial.print("RSSI > ");
  Serial.println(rssi);
  delay(1000);
}

/**
 * function that
 */
void connectToWiFi(void){
  int contador = 0;
  if (WiFi.status() != WL_CONNECTED){ // if WiFi not connected
    WiFi.begin(c_ssid, c_pwd); // connect to WiFi using the ssid and password provided
    //WiFi.begin("DAVER", "delapaxx"); <- Hardcoded version, write ssid and password manually
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

/**
 * function that selects an ssid and password for a network provided by console
 */
void wifiNetworkSelection(void){
  if(WiFi.status() != WL_CONNECTED){ // if WiFi not connected
    Serial.println("SSID? >");
    while(!Serial.available()); // wait for text input
    String ssid = Serial.readString(); // read ssid from console
    ssid[ssid.length()-1] = '\0'; // modify last char to '\0'
    ssid.toCharArray(c_ssid, 50); // save ssid to char array
    Serial.print("SSID selected > ");
    Serial.println(ssid);
    delay(1000); // wait 1s
    Serial.print("Password? > ");
    while(!Serial.available()); // wait for text input
    String password = Serial.readString(); // read password from console
    password[password.length()-1] = '\0'; // modify last char to '\0'
    password.toCharArray(c_pwd, 50); // save password to char array
    Serial.print("PWD > ");
    Serial.println(password);
    delay(1000); // wait 1s
  }  
}
