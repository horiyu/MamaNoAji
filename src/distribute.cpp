#include <Arduino.h>
#include "solenoid.hpp"

void distribute(int colBottle, int putBottle)
{
  int disBottle = colBottle - putBottle;

  for (int i = 0; i < disBottle; i++)
  {
    switch ((i + putBottle) % 3)
    {
    case 0:
      solenoid_left();
      break;

    case 1:
      solenoid_middle();
      break;

    case 2:
      solenoid_right();
      break;

    default:
      break;
    }
  }
  putBottle += disBottle;

  /*
  2,3,5
  2)2
  6)2,3
  10)2,5
  30)2,3,5
  3)3
  15)3.5
  5)5
  */
  // int current;
  // current = 6 - num;
};