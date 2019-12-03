#include "ESP8266WiFi.h"
WiFiClient client;

char c_ssid[50], c_pwd[50]; // create char vectors for ssid and password
char buff[4];
byte number;
byte guess;
const int postingInterval = 1 * 1000; // post data every 20s
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WiFi access point test");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Maet_Server", "guillemRIP");
  Serial.println("WiFi ON");

}

int state = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(state == 0){//Send
    number = 5;
    client.println("Guess a number in [0,10]");
    state = 1;    
  }else if(state == 1){
    guess = client.read();
    if (guess == number){
      state = 0;
      client.println("Correct. Congratulations. :)");
      client.read();
    }else{
      if (guess < number){
        client.println("Psych wrong number. Try Higher");
      }else{
        client.println("Psych wrong number. Try lower");
      }
    }
  }
  delay(postingInterval);
}
