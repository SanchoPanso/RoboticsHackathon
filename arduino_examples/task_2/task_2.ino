
/*
Омегабот должен при нажатии на кнопку на плате расширения проехать 
прямо до момента срабатывания датчика касания (до препятствия), 
затем 1 секунду ехать назад. После чего робот должен остановиться.
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

int ObjectSensorRead(int SensorPin)
{
  int Data = digitalRead(SensorPin);
  return !Data;
}

void MoveBack(int Speed)
{
  Motors(-Speed, -Speed);
}

void Stop()
{
  Motors(0, 0);
}

void MoveBackByDelay(int Speed, int Time)
{
  MoveBack(Speed);
  delay(Time);
  Stop();
}


void setup()
{
  pinMode(12, INPUT_PULLUP);
  InitMotors();
}

void loop()
{
  while ( ButtonRead(12) )
  {
    do
    {
      MoveForward(80);
    }
    while(!( ObjectSensorRead(10) ));
    MoveBackByDelay(100, 1000 );  
  }

  Stop();
}
