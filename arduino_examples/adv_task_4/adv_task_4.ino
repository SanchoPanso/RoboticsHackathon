/*
Омегабот должен при нажатии на кнопку на плате расширения начать движение вперед на 50 сантиметров, 
затем повернуться на 90 градусов вправо и продолжить движение вперед на 50 сантиметров. 
Робот будет продолжать движение, пока не повторит действие 4 раза (пока не проедет по траектории квадрата со стороной 50 сантиметров). 
Перерыв между всеми действиями полсекунды. После чего робот должен остановиться.
*/

#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6
#define ENCODER_K_DIST 1
unsigned long EncoderCount1, EncoderCount2;
#define ENCODER_K_ANGLE 2.37
int ButtonRead(int ButtonPin)
{
  int Data = digitalRead(ButtonPin);
  if(ButtonPin == 12) Data = !Data;
  return Data;
}

int _1_a;
void InitEnc()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, nEncoder1, CHANGE);
  attachInterrupt(1, nEncoder2, CHANGE);
}

void nEncoder1()
{
  EncoderCount1++;
}

void nEncoder2()
{
  EncoderCount2++;
}

void Encoder1ToNull()
{
  EncoderCount1 = 0;
}

void Encoder2ToNull()
{
  EncoderCount2 = 0;
}

void EncodersToNull()
{
  EncoderCount1 = 0;
  EncoderCount2 = 0;
}

unsigned long GetDistanceFromEnc1()
{
  return (double)EncoderCount1 * (double)ENCODER_K_DIST;
}

unsigned long GetDistanceFromEnc2()
{
  return (double)EncoderCount2 * (double)ENCODER_K_DIST;
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

void MoveForwardByEncoder(int Speed, unsigned long Distance)
{
  EncodersToNull();
  MoveForward(Speed);

  while(1)
  {
    if(GetDistanceFromEnc1() > Distance) break;
    if(GetDistanceFromEnc2() > Distance) break;
    Serial.print("1");
  }

  Stop();
}

unsigned long GetAngleFromEnc1()
{
  return (double)EncoderCount1 * (double)ENCODER_K_ANGLE;
}

unsigned long GetAngleFromEnc2()
{
  return (double)EncoderCount2 * (double)ENCODER_K_ANGLE;
}

void MoveRight(int Speed)
{
  Motors(-Speed, Speed);
}

void MoveRightByEncoder(int Speed, int Angle)
{
  EncodersToNull();
  MoveRight(Speed);

  while(1)
  {
    if(GetAngleFromEnc1() > Angle) break;
    if(GetAngleFromEnc2() > Angle) break;
    Serial.print("1");
  }

  Stop();
}


void setup()
{
  pinMode(12, INPUT_PULLUP);
  InitEnc();
  InitMotors();
}

void loop()
{
  if (ButtonRead(12))
  {
    for (_1_a=1; _1_a<= ( 4 ); ++_1_a )
    {
      MoveForwardByEncoder(150, 50);  
      delay( 500 );
      MoveRightByEncoder(150, 90);  
      delay( 500 );
    }
  }
}
