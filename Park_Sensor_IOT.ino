#include <ESP8266WiFi.h>
#include <WiFiClient.h>;
#include <ThingSpeak.h>;  //ThingSpeak connections parts are taken from https://iotdesignpro.com/projects/smart-inventory-management-system-using-iot

const char * myWriteAPIKey = "M9JF6G02LSQNULPP";

const char* ssid = "TURKSAT-KABLONET-37F9-2.4G"; //Ağımızın adını buraya yazıyoruz.
const char* pass = "9e6764d1"; //Ağımızın şifresini buraya yazıyoruz.

unsigned long myChannelNumber = 1415223;
WiFiClient client;

const int led = D7;
const int buzzer = D6;

const int trig_pin = D5;
const int echo_pin= D2;

long duration; 
float distance_cm;


void setup() {

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  
  Serial.begin(115200);
  ThingSpeak.begin(client);  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

}

void loop() {

  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);

  //v=340m/sn
  //v=0,034cm/ms
  
  //time = distance/speed => distance=time*speed
  distance_cm= duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance_cm);

  ThingSpeak.writeField(myChannelNumber, 1,distance_cm, myWriteAPIKey);
  
  if (distance_cm <= 10)
  {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(30);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(30);
  }

  else if (distance_cm <= 30)
  { 
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(100);
  }

  else if (distance_cm > 30)
  {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);
  }

}
