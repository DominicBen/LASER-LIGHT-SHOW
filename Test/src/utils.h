#ifndef UTIL_H
#define UTIL_H
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

#endif