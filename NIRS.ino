/*
   fNIRS test firmware
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

#define marker "#"
#define _Simulate_

//#define CH4

#if defined(ARDUINO_AVR_MEGA) || defined (ARDUINO_AVR_UNO)
#define NIR A0
#define CH0 3
#define CH1 4
#define TRG 5
#define RST 6

#elif defined(ARDUINO_BLUEPILL_F103C8) || defined(ARDUINO_BLACKPILL_F103C8)
#define NIR PA0

#define CH0 PA1
#define CH1 PA2
#define TRG PA3
#define RST PA4
#else
#error Unsupported hardware
#endif

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
      if (Serial.readStringUntil('\n') == marker)
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
