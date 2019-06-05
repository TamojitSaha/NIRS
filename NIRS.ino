/*
   fNIRS test firmware
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.5.0
   Released under CC-BY-ND 4.0
*/

#define marker '#'
#define _Simulate_

//#define CH4

#define NIR PA0

#define CH0 PA1
#define CH1 PA2
#define TRG PA3
#define RST PA4

//#define timeOut 5 //See 'rset()' in 'functions'

#define channelDelay 0
#define eventDelay 0

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    ;
  }

#ifndef _Simulate_
  pinMode(NIR, INPUT_ANALOG);
#endif

  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(TRG, OUTPUT);
  pinMode(RST, OUTPUT);
}

uint8_t   reference   = NULL; //To be accessed by swCH()
uint16_t  counter     = NULL;
uint32_t  timeStamp   = NULL;

#ifdef marker
boolean initialize  = false;
#endif

uint16_t data[4] = {};

void loop()
{

#ifdef marker
  if (!initialize)
  {
    while (Serial.available() > NULL)
    {
      if (Serial.read() == marker)
      {
        initialize = true;
        Serial.write("~\n");
      }
    }
  }
  else if (initialize)
#endif

  {
    delay(eventDelay);

    for (uint8_t i = NULL; i < 4; i++)
    {
      swCH();
      trig(true);
      data[i] = analogRead(NIR);
      trig(false);
      rset();
      delay(channelDelay);
    }

    Serial.print(counter);
    Serial.print('\t');
    if (counter == NULL)
    {
      Serial.print(NULL);
      Serial.print('\t');
      Serial.print(NULL);
    }
    else
    {
      delayConter();
    }
    Serial.print('\t');
    dataPack();
    timeStamp = micros();
  }
}
