/*
Омегабот должен при нажатии на кнопку на плате расширения помигать 3 раза светодиодом (каждый сигнал светодиода длится 1 секунду), 
затем 3 раза издать звук модулем пьезодинамика (каждый звук пьезодинамика длится 3 секунды), затем опять подать 3 сигнала светодиодом. 
Между действиями перерыв полсекунды. Цикл не повторять.
*/

int ButtonRead(int ButtonPin)
{
  int Data = digitalRead(ButtonPin);
  if(ButtonPin == 12) Data = !Data;
  return Data;
}

void LedControl(int LedPin, int State)
{
  if(LedPin != 13)  State = !State;
  digitalWrite(LedPin, State);
}

void LedBlinks(int LedPin, int Count, int TimeON, int TimeOFF)
{
  for(int i = 0; i < Count; i++)
  {
    LedControl(LedPin, 1);
    delay(TimeON);
    LedControl(LedPin, 0);
    delay(TimeOFF);
  }
}

void PiezoBeep(int PiezoPin, int Tone, int TimeON, int TimeOFF, int Count)
{
  for(int i = 0; i < Count; i++)
  {
    tone(PiezoPin, Tone);
    delay(TimeON);
    noTone(PiezoPin);
    delay(TimeOFF);
  }
}


void setup()
{
  pinMode(12, INPUT_PULLUP);
  pinMode(9, OUTPUT);
}

void loop()
{
  while ( ButtonRead(12) )
  {
    LedBlinks(9, 3, 1000, 500);
    delay( 500 );
    PiezoBeep(8, 3000, 3000, 500, 3);
    delay( 500 );
    LedBlinks(9, 3, 1000, 500);
  }

}
