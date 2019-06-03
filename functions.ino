/*
   fNIRS test firmware functions
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.1.0
   Released under CC-BY-ND 4.0
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
  delay(timeOut);
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
#ifdef disable_CH4
      Serial.println(random(data_range[LOW], data_range[HIGH]));
#else
      Serial.println(data[i]);
#endif
    }
    else
    {
      Serial.print('\t');
    }
  }
  counter++;
}
