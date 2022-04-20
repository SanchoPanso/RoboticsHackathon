/*
Омегабот должен при нажатии на кнопку на плате расширения начать движение вперед или назад в зависимости от того, где расположен источник света. 
Робот должен максимально приблизиться к источнику света. После чего робот должен остановиться.
*/

#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6
int LightSensorRead(int SensorPin)
{
  if(SensorPin < A0 || SensorPin > A3)
    return -1;

  int Data = analogRead(SensorPin);
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
  Serial.begin(9600);
}

void loop()
{
  if (( ( 500 ) > ( LightSensorRead(A2) ) ))
  {
    MoveForwardByDelay(100, 500 );
  }
  if (( ( 150 ) > ( LightSensorRead(A3) ) ))
  {
    MoveBackByDelay(100, 500 );
  }
  Serial.print("A2");
  Serial.print(LightSensorRead(A2));
  Serial.println();
  Serial.print("A3");
  Serial.print(LightSensorRead(A3));
  Serial.println();
}
