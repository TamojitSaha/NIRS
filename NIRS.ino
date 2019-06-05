/*
   fNIRS test firmware
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.4.0
   Released under CC-BY-ND 4.0
*/

//#define marker '#'
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
uint32_t  eventStamp  = NULL;

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

    uint32_t  tRef  = micros() - eventStamp;
    if (tRef >= pow(10, 6))
    {
      eventStamp = micros();

#ifdef marker
      Serial.print(marker);
      Serial.print('\t');
      Serial.println(tRef);
#endif

      Serial.print(counter);
      Serial.print('\t');
      if (counter == NULL)
      {
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
    else
    {
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
}
