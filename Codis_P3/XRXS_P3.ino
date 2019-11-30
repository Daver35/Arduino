#include "ESP8266WiFi.h"

//Wi-Fi Settings
char c_ssid[50], c_pwd[50]; // create char vectors for ssid and password

WiFiClient client; // initiallize the client library

//ThingSpeak Settings
const int channelID = 912115;
String writeAPIKey = "9YFVIOD1IQWBAE76";
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // post data every 20s

void setup() {

    Serial.begin(9600);
    WiFi.mode(WIFI_STA); // configure STA mode
    WiFi.disconnect(); // disconnect WiFi shield from current network
    delay(2000); // wait 2s
    wifiScan(); // scan for availabrle networks
    wifiNetworkSelection(); // input ssid and password
    connectToWiFi(); // connect to network given the ssid and password
    Serial.println("Setup done");
}

void loop() {
    if (client.connect(server, 80)) { 

    // Measure Signal Strenght (RSSI) of WiFi connection
    long rssi = WiFi.RSSI();

     // Construct API request body
    String body = "field1=";
    body += String(rssi);

    Serial.print("RSSI: "); // print RSSI
    Serial.println(rssi);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Lenght: " + String(body.length()));
    client.println("");
    client.print(body);
    }
    client.stop();
    delay(postingInterval);
}

/**
 * function that scans and prints all the different networks available
 */
void wifiScan(){
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

/**
 * function that uses the given ssid and password to try to connect to a network
 */
void connectToWiFi(void){
  int contador = 0;
  if (WiFi.status() != WL_CONNECTED){ // if WiFi not connected
    WiFi.begin(c_ssid, c_pwd); // connect to WiFi using the ssid and password provided
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
