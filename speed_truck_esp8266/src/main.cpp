#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#define MOTOR_PIN D5

//Commands definitions (for switch...Case clarity)
#define SLOW_START 'a' 
#define SLOW_STOP 'b'
#define SPEED_MAX 'c'
#define SPEED_MID 'd'
#define STOP 'e'
#define START 'f'

#define UDP_PORT 4210

#define ENABLE 12
#define PHASE 13

//AP Credentials
const char* ssid = "SPEEDTRUCKS";
const char* pwd = "speedtrucks";

int speed = 0;

//UDP Configuration
WiFiUDP UDP;

// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char cmd;

void setup()
{  
pinMode(ENABLE, OUTPUT);
pinMode(PHASE, OUTPUT);

  Serial.begin(9600);
  Serial.println();

  WiFi.begin(ssid, pwd);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);

}

void loop() {
  digitalWrite(PHASE, HIGH); //Sens du moteur
// Receive packet
  UDP.parsePacket();
  if(UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE)) {
    cmd = packetBuffer[0];
    Serial.println(cmd);
    switch (cmd)
    {    
    case SLOW_START :
      /* code */
      for(int i = 1 ; i<127 ; i++) {
        analogWrite(ENABLE, i);
        speed = i;
        delay(10);
      }
      break;

    case SLOW_STOP :
      if(speed != 0) {
      for(int i = speed ; i>0 ; i--) {
        analogWrite(ENABLE, i);
        speed = i;
        delay(10);
      }
      digitalWrite(ENABLE, LOW);
      }
      break;

    case SPEED_MAX :
      for(int i = speed ; i<256 ; i++) {
        analogWrite(ENABLE, i);
        speed = i;
        delay(10);
      }
      break;

    case SPEED_MID :
      if(speed > 127) {
        for(int i = speed ; i > 126 ; i--) {
        analogWrite(ENABLE, i);
        speed = i;
        delay(10);
      }
      }
      else {
        for(int i = speed ; i<128 ; i++) {
        analogWrite(ENABLE, i);
        speed = i;
        delay(10);
      }
      }
      break;

    case STOP :
      digitalWrite(ENABLE, LOW);
      speed = 0;
      break;

    case START :
      digitalWrite(ENABLE, HIGH);
      speed=255;
      break;

    default:
      digitalWrite(12, LOW);
      speed = 0;
      break;
    }
  }
}