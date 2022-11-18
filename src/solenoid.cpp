#include <Arduino.h>

#define pin_solenoid_left 5
#define pin_solenoid_middle 17
#define pin_solenoid_right 16

void solenoid_init(void)
{
  pinMode(pin_solenoid_left, OUTPUT);
  pinMode(pin_solenoid_middle, OUTPUT);
  pinMode(pin_solenoid_right, OUTPUT);
}

void solenoid(int pin)
{
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);
}

void solenoid_left(void)
{
  for (int i = 0; i < 5; i++)
  {
    solenoid(pin_solenoid_left);
  }
}

void solenoid_middle(void)
{
  for (int i = 0; i < 1; i++)
  {
    solenoid(pin_solenoid_middle);
  }
}

void solenoid_right(void)
{
  for (int i = 0; i < 6; i++)
  {
    solenoid(pin_solenoid_right);
  }
}

// void distribute(int num)
// {
//   static int putBottle = 0;
//   for (int i = 0; i < num; i++)
//   {
//     // n2,p0)2)1,2
//     // n3,p2)5)3,4,5
//     // n1,p5)6)6
//     switch ((i + putBottle) % 3)
//     {
//     case 0:
//       solenoid_left();
//       break;

//     case 1:
//       solenoid_middle();
//       break;

//     case 2:
//       solenoid_right();
//       break;

//     default:
//       break;
//     }
//   }
//   putBottle += num;

//   if (2)
//     digitalWrite(pin_solenoid_left, HIGH);
//   if (3)
//     digitalWrite(pin_solenoid_middle, HIGH);
//   if (5)
//     digitalWrite(pin_solenoid_right, HIGH);
//   delay(1000);

//   if (2)
//     digitalWrite(pin_solenoid_left, LOW);
//   if (3)
//     digitalWrite(pin_solenoid_middle, LOW);
//   if (5)
//     digitalWrite(pin_solenoid_right, LOW);
//   delay(1000);

//   /*
//   2,3,5
//   2)2
//   6)2,3
//   10)2,5
//   30)2,3,5
//   3)3
//   15)3.5
//   5)5
//   */
// };