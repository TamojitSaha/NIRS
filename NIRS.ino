/*
   fNIRS test firmware
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.2.0
   Released under CC-BY-ND 4.0
*/

#define marker '#'

#define disable_CH4

#define NIR PA0

#define CH0 PA1
#define CH1 PA2
#define TRG PA3
#define RST PA4

#define timeOut 5 //See 'rset()' in 'functions'

#define channelDelay 0
#define eventDelay 0

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    ;
  }

  //  pinMode(NIR, INPUT_ANALOG);

  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(TRG, OUTPUT);
  pinMode(RST, OUTPUT);
}

uint8_t   reference   = NULL; //To be accessed by swCH()
uint16_t  counter     = NULL;
uint32_t  timeStamp   = NULL;
uint32_t  eventStamp  = NULL;

boolean initialize  = false;

uint16_t data[4] = {};
uint16_t data_range[2] = {UINT16_MAX, NULL};

void loop()
{
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
  {
    delay(eventDelay);

    for (uint8_t i = NULL; i < 4; i++)
    {
      swCH();
      trig(true);
      data[i] = analogRead(NIR);
      if (data[i] < data_range[LOW])
      {
        data_range[LOW] = data[i];
      }
      if (data[i] > data_range[HIGH])
      {
        data_range[HIGH] = data[i];
      }
      trig(false);
      rset();
      delay(channelDelay);
    }


    if ((micros() - eventStamp) >= pow(10, 6))
    {
      eventStamp = micros();
      Serial.println(marker);
      
      Serial.print(counter);
      Serial.print('\t');
      if (counter == NULL)
      {
        Serial.print(NULL);
      }
      else
      {
        Serial.print(micros() - timeStamp);
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
      }
      else
      {
        Serial.print(micros() - timeStamp);
      }
      Serial.print('\t');
      dataPack();
      timeStamp = micros();
    }
  }
}
