#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

template <typename T>
T clamp(T n, T min, T max)
{
  if (n > max)
  {
    return max;
  }
  else if (n < min)
  {
    return min;
  }
  else
  {
    return n;
  }
}

double normalize(double old_value, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
{
  double new_value = ((old_value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
  return new_value;
}

#endif