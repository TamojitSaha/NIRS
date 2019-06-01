/*
   fNIRS test firmware
   Author: Sandeepan Sengupta (mail@sandeepan.info)
   Version 0.1.0
   Released under CC-BY-ND 4.0
*/

//#define count 500
#define margin 10
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

  pinMode(NIR, INPUT_ANALOG);

  pinMode(CH0, OUTPUT);
  pinMode(CH1, OUTPUT);
  pinMode(TRG, OUTPUT);
  pinMode(RST, OUTPUT);
}

uint8_t   reference = NULL;
uint16_t  counter   = NULL;

void loop()
{
  delay(eventDelay);

  uint16_t data[4] = {};
  uint16_t data_range[2] = {UINT16_MAX, NULL};

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

  for (uint8_t i = NULL; i < 4; i++)
  {
#ifdef count
    if (counter < count)
#endif
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
  }
  counter++;
}
