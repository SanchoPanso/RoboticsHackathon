/*
Робот должен при нажатии на кнопку на модуле кнопки начать мигать двумямодулями светодиодов. 
При повороте ручки потенциометра робот должен сжимать или разжимать схват. 
Выполнять программу пока снова не будет нажата кнопка на модуле кнопки.
*/

#include <Servo.h>
#define LED_1 9
#define LED_2 10
Servo servo1;
const int ButtonPin = 11;
const int pinServo = 8;
const int POT = 3;
int valpot = 0;
int angleServo = 0;
int val = 0;
byte state = 0;
unsigned long timing;
void setup()
{
servo1.attach(pinServo);
pinMode(LED_1, OUTPUT);
pinMode(LED_2, OUTPUT);
Serial.begin(9600);
pinMode(ButtonPin, INPUT_PULLUP);
}
void loop()
{
val = digitalRead(ButtonPin);
if(val == HIGH)
  {
   state = !state;
   if(state == HIGH)
    {
      while(state == HIGH)
      {
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_1, LOW);
      if(millis() - timing > 700){
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_1, HIGH);
      if(millis() - timing > 1400){
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_1, LOW);
      timing = millis();}
      }
      valpot = analogRead(POT);
      angleServo=map(valpot, 0, 1023, 0, 180);
      servo1.write(angleServo);
      delay(5);
      }
    }
   else
    {
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_1, LOW);
    }
    delay(300); 
  } 
}
