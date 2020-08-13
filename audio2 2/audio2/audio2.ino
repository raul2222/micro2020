

#define SONI 2
#define SONI2 5

#include "SoundData.h";

int tiempo = ((1/6000)*1000000) - 7;


void setup() {
  // put your setup code here, to run once:
  pinMode(SONI,OUTPUT);
  digitalWrite(SONI,HIGH);
  pinMode(SONI2,OUTPUT);
  digitalWrite(SONI2,LOW);
  delay(2000);
}

void loop() {
  digitalWrite(SONI,HIGH);
  digitalWrite(SONI2,LOW);
  delay(2000);
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 104960; ++i){
    dacWrite(25, rawData[i]);
    //16000
    //delayMicroseconds(110); // ((1/22050)*1000000) - 7
    //delayMicroseconds(((1/16000)*1000000) - 7);
    delayMicroseconds(158);
  }
  digitalWrite(SONI,LOW);
  digitalWrite(SONI2,HIGH);
  delay(6000);
}
