#include <Arduino.h>

#define pin_dout 18
#define pin_slk 19

// ロードセル　シングルポイント（ビーム型）　ＳＣ６１６Ｃ　５００ｇ[P-12532]
#define OUT_VOL 0.0007f //定格出力 [V]
#define LOAD 500.0f     //定格容量 [g]

float AE_HX711_getGram(char num);
long AE_HX711_Read(void);

static float offset;

float loadcell_read(void)
{
  float data;
  float mass;
  char S1[20];
  char s[20];
  data = AE_HX711_getGram(5);

  // data = 55.0 / 50.0; //ここで校正を行う

  // sprintf(S1, "%s [g] (0x%4x)", dtostrf((data - offset), 5, 3, s), AE_HX711_Read());
  // Serial.println(S1);

  mass = data - offset;

  // Serial.print("data :");
  // Serial.println(data);
  // Serial.print("offset :");
  // Serial.println(offset);
  // Serial.print("mass   :");
  // Serial.print(mass);
  // Serial.println(" [g]");
  // Serial.println("--------------------");

  return mass;
}

void loadcell_init(void)
{
  pinMode(pin_slk, OUTPUT);
  pinMode(pin_dout, INPUT);
  offset = AE_HX711_getGram(30);
}

void loadcell_reset(void)
{
  digitalWrite(pin_slk, 1);
  delayMicroseconds(100);
  digitalWrite(pin_slk, 0);
  delayMicroseconds(100);
}

long AE_HX711_Read(void)
{
  long data = 0;
  while (digitalRead(pin_dout) != 0)
    ;
  delayMicroseconds(10);
  for (int i = 0; i < 24; i++)
  {
    digitalWrite(pin_slk, 1);
    delayMicroseconds(5);
    digitalWrite(pin_slk, 0);
    delayMicroseconds(5);
    data = (data << 1) | (digitalRead(pin_dout));
  }
  // Serial.println(data,HEX);
  digitalWrite(pin_slk, 1);
  delayMicroseconds(10);
  digitalWrite(pin_slk, 0);
  delayMicroseconds(10);
  return data ^ 0x800000;
}

long AE_HX711_Averaging(long adc, char num)
{
  long sum = 0;
  for (int i = 0; i < num; i++)
    sum += AE_HX711_Read();
  return sum / num;
}

float AE_HX711_getGram(char num)
{
#define HX711_R1 20000.0f
#define HX711_R2 8200.0f
#define HX711_VBG 1.25f
#define HX711_AVDD 4.2987f                  //(HX711_VBG*((HX711_R1+HX711_R2)/HX711_R2))
#define HX711_ADC1bit HX711_AVDD / 16777216 // 16777216=(2^24)
#define HX711_PGA 128
#define HX711_SCALE (OUT_VOL * HX711_AVDD / LOAD * HX711_PGA)

  float data;

  data = AE_HX711_Averaging(AE_HX711_Read(), num) * HX711_ADC1bit;
  // Serial.println( HX711_AVDD);
  // Serial.println( HX711_ADC1bit);
  // Serial.println( HX711_SCALE);
  // Serial.println( data);
  data = data / HX711_SCALE;

  return data;
}