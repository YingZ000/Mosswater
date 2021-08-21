#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

unsigned long previous=0;
unsigned long period=30*1000;

int pinInterrupt = 2;
int fanPin = 6; //pvm
int pumpPin = 7; 

boolean drink=false;

void (*zero)(void)=0;

void setup()
 {
    pinMode(pinInterrupt,INPUT);
    pinMode(fanPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);

    mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module
    mp3_set_volume (35);  //音量
    
   // attachInterrupt( digitalPinToInterrupt(pinInterrupt), onChange, CHANGE);
    Serial.begin(9600);
}
 
void loop() //30min的行为
{

   if ( digitalRead(pinInterrupt) == 0 ){
       digitalWrite(pumpPin,HIGH);
       delay(3*1000); //浇水的时间
       digitalWrite(pumpPin,LOW);
       delay(5*1000);
       zero();
    }
    
    analogWrite(fanPin,100);//风扇一直打开 确定干燥需要的风力大小

    unsigned long current = millis(); // store the current time

    Serial.println(current);
    
    if(current-previous>=30*60*1000)      //下一次喝水超过了30min
      {
        previous=current;
        mp3_play (5);
      }

}
