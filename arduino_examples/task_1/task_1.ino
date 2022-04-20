
/*
Омегабот должен при нажатии на кнопку (на модуле кнопки) 2 секунды проехать прямо, 
затем 2 секунды поворачивать по часовой стрелке, затем 2 секунды ехать назад. 
Между действиями перерыв полсекунды. После чего робот должен остановиться.
*/
#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6
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

void MoveRight(int Speed)
{
  Motors(-Speed, Speed);
}

void MoveRightByDelay(int Speed, int Time)
{
  MoveRight(Speed);
  delay(Time);
  Stop();
}

void MoveBack(int Speed)
{
  Motors(-Speed, -Speed);
}

void MoveBackByDelay(int Speed, int Time)
{
  MoveBack(Speed);
  delay(Time);
  Stop();
}


void setup()
{
  InitMotors();
}

void loop()
{
  while ( ButtonRead(8) )
  {
    MoveForwardByDelay(100, 1000 );    
    delay( 500 );
    MoveRightByDelay(100, 1000);    
    delay( 500 );
    MoveBackByDelay(100, 1000 );  
  }

  Stop();
}
