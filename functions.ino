/*
   fNIRS test firmware functions
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.5.0
   Released under CC-BY-ND 4.0

   Version 0.5.1
   Author: Tamojit Saha (mail@tamojitsaha.info)
   Date Modified: 5 June 2019
     # Changes
      - Compile-time PIN name change for MEGA,UNO,STM32F103C8
      - Line 80, function usage fix i.e. read seril string untill '\n'

*/

void trig(bool state)
{
  digitalWrite(TRG, state);
  digitalWrite(RST, !state);

  /*
     Timing inntervals are set as recomended at openNIRS project documentation
     Please refer to page 55
     http://www.opennirs.org/docu/openNIRS_full_documentation_v1.pdf
  */
  if (state)
  {
    delay(4);
  }
  else
  {
    delay(1);
  }
}

void rset()
{
  digitalWrite(TRG, LOW);
  digitalWrite(RST, HIGH);

#ifdef timeOut
  delay(timeOut);
#endif
}

void swCH()
{
  if ((reference % 4) == 0)
  {
    digitalWrite(CH0, LOW);
    digitalWrite(CH1, LOW);
  }
  else if ((reference % 4) == 1)
  {
    digitalWrite(CH0, LOW);
    digitalWrite(CH1, HIGH);
  }
  else if ((reference % 4) == 2)
  {
    digitalWrite(CH0, HIGH);
    digitalWrite(CH1, LOW);
  }
  else if ((reference % 4) == 3)
  {
    digitalWrite(CH0, HIGH);
    digitalWrite(CH1, HIGH);
  }
  reference++;
}

void delayConter()
{
  uint32_t interval = micros() - timeStamp;
  Serial.print(interval / 1000);  //1ms is 1000us
  Serial.print('\t');
  Serial.print(interval % 1000);  //Fetching us value
}

void dataPack()
{
  for (uint8_t i = NULL; i < 4; i++)
  {
    if (i < 3)
    {
      Serial.print(data[i]);
    }
    if (i == 3)
    {
#ifdef CH4
      Serial.println(data[i]);
#else
      Serial.println();
#endif
    }
    else
    {
      Serial.print('\t');
    }
  }
  counter++;
}
