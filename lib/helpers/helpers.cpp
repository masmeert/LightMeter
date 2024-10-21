#include <math.h>

float find_closest(float value, const float *array, int array_size)
{
  float closest_value = array[0];
  for (int i = 1; i < array_size; i++)
  {
    if (fabs(array[i] - value) < fabs(closest_value - value))
    {
      closest_value = array[i];
    }
  }
  return closest_value;
}