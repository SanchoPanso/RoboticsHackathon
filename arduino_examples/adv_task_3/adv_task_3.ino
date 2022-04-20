/*
Омегабот должен при нажатии на кнопку на плате расширения ехать вперед 2 секунды, остановится на 1 секунду, схватить банку, 
используя модуль схвата, и поднять ее вверх. После чего робот должен остановиться.
*/

#include <Servo.h>
Servo servo_pin_10;
Servo servo_pin_9;                
#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6
void ServoMove(Servo S1, int Angle)
{
  if(Angle > 180) Angle = 180;
  if(Angle < 0) Angle = 0;

  S1.write(Angle);
}

int ButtonRead(int ButtonPin)
{
  int Data = digitalRead(ButtonPin);
  if(ButtonPin == 12) Data = !Data;
  return Data;
}

void InitMotors()
{
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
}

void Motors(int Speed1, int Speed2)
{
  if(Speed1 > 255) Speed1 = 255;
  if(Speed1 < -255) Speed1 = -255;
  if(Speed2 > 255) Speed2 = 255;
  if(Speed2 < -255) Speed2 = -255;

  if(Speed1 > 0)
  {
    digitalWrite(M1_DIR, 1);
    analogWrite(M1_PWM, Speed1);
  }
  else
  {
    digitalWrite(M1_DIR, 0);
    analogWrite(M1_PWM, -Speed1);
  }

  if(Speed2 > 0)
  {
    digitalWrite(M2_DIR, 1);
    analogWrite(M2_PWM, Speed2);
  }
  else
  {
    digitalWrite(M2_DIR, 0);
    analogWrite(M2_PWM, -Speed2);
  }
}

//Ехать вперед
void MoveForward(int Speed)
{
  Motors(Speed, Speed);
}

void Stop()
{
  Motors(0, 0);
}

void MoveForwardByDelay(int Speed, int Time)
{
  MoveForward(Speed);
  delay(Time);
  Stop();
}


void setup()
{
  servo_pin_10.attach(10);
  servo_pin_9.attach(9);
  pinMode(12, INPUT_PULLUP);
  InitMotors();
  ServoMove(servo_pin_10,0);
  ServoMove(servo_pin_9,180);
}

void loop()
{
  if (ButtonRead(12))
  {
    ServoMove(servo_pin_10,0);
    ServoMove(servo_pin_9,180);  
    delay( 700 );
    MoveForwardByDelay(100, 2000 ); 
    delay( 1000 );
    ServoMove(servo_pin_9,70);  
    delay( 1000 );
    ServoMove(servo_pin_10,70);
  }
}
