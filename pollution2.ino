#include "ESP8266WiFi.h"
#include "UbidotsMicroESP8266.h"

#define TOKEN  "pjuIkTHq17yA4JrCWJkHTOjavpSTDc"  // Put here your Ubidots TOKEN
#define WIFISSID "Nets"
#define PASSWORD "jio123456"


Ubidots client(TOKEN);

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){

     float V=0.0;
    float value = analogRead(A0);
    
    V= value * 3.3/ 4095;
     float PPM = 3.027*exp(1.0698*V);
  
    client.add("Pollution2", PPM);
    client.sendAll(true);
}
