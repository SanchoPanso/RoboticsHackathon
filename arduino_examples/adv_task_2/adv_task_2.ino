/*
Омегабот должен при повороте ручки потенциометра увеличивать или уменьшать яркость освещения светодиода на модуле светодиода.
*/

int PotentiometerRead(int SensorPin)
{
  if(SensorPin < A0 || SensorPin > A3)
    return -1;

  int Data = analogRead(SensorPin);
  return Data;
}

void LedBrightness(int LedPin, int Bright)
{
  if(LedPin > 255) LedPin = 255;
  if(LedPin < 0) LedPin = 0;

  analogWrite(LedPin, 255 - Bright);
}


void setup()
{
  pinMode(9, OUTPUT);
}

void loop()
{
  LedBrightness(9, map ( PotentiometerRead(A0) , 0 , 1023 , 0 , 255 ) );
}
