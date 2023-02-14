/**
 * @file Utils.h
 * @author Laser Light Snow
 * @brief A small collection of helper functions
 * @version 0.1
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <vec.h>
/**
 * @brief the clamp function takes a number n, and clamps it between the range of min-max
 * Example) if n is greater than max, then return max, if n is less than min, return min. else, return n
 *
 * @tparam T Generic Type
 * @param n The value to be clamped
 * @param min The minimum number in the range
 * @param max The maximum number in the range
 * @return T Clamped value
 */
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
/**
 * @brief Takes a value, bound to some range, and projects it onto a new range
 * For example, say we have 0.5 that exists on a range between 0-1. if we project that onto our new range, say 50-100
 * our new value will be 75
 *
 * @param old_value
 * @param old_min
 * @param old_max
 * @param new_min
 * @param new_max
 * @return double
 */
double normalize(double old_value, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
{
  double new_value = ((old_value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
  return new_value;
}

Vec2 normalize(Vec2 old_value, int16_t old_min, int16_t old_max, int16_t new_min, int16_t new_max)
{
  float newx = ((old_value.x - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
  float newy = ((old_value.y - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min;
  return {newx, newy};
}

#endif