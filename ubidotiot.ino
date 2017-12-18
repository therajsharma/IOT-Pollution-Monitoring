#include "ESP8266WiFi.h"
#include "UbidotsMicroESP8266.h"
#include "MQ135.h"

#define MQ135_DEFAULTPPM 399 //default ppm of CO2 for calibration
#define MQ135_DEFAULTRO 90550 //default Ro for MQ135_DEFAULTPPM ppm of CO2
#define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
#define MQ135_EXPONENT -2.769034857 //CO2 gas value
#define MQ135_MAXRSRO 2.428 //for CO2
#define MQ135_MINRSRO 0.358 //for CO2

unsigned long SLEEP_TIME = 30000; // Sleep time between reads (in seconds)
//VARIABLES
float mq135_ro = 10000.0;    // this has to be tuned 10K Ohm
int val = 0;                 // variable to store the value coming from the sensor
float valAIQ =0.0;
float lastAIQ =0.0;
#define TOKEN  "WCHVyMinYydGOSo7XUhaZW8dXbltcS"  // Put here your Ubidots TOKEN
#define WIFISSID "Nets"
#define PASSWORD "jio123456"
MQ135 gasSensor = MQ135(A0);


Ubidots client(TOKEN);

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
double mq135_getppm(long resvalue, long ro) 
{

float ret=0.0;
ret = (double)MQ135_SCALINGFACTOR * pow( ((double)resvalue/ro), MQ135_EXPONENT);
return ret;
}

void loop(){
  float valr = analogRead(A0);
  float val =  ((float)10000*(1024-valr)/valr); 
double ppm = mq135_getppm(val, MQ135_DEFAULTRO);
    client.add("AirPollution", ppm);
    client.sendAll(true);
}
