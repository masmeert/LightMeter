#include <cmath>
#include <cstdint>

/**
 * @brief Computes the shutter speed from the exposure value and the aperture
 *
 * As the EV formula is EV = 2log2(N) - log2(t)
 * Where N is the aperture and t is the shutter speed
 * We can solve for t: t = N^2 / 2^EV
 */
float computeShutterSpeed(float EV, float N)
{
  return (N * N) / std::exp2f(EV);
}

/**
 * @brief Computes the aperture from the exposure value and the shutter speed
 *
 * As the EV formula is EV = 2log2(N) - log2(t)
 * We can solve for N: N = 2^((EV + log2(t))/2)
 */
float computeAperture(float EV, float t)
{
  return std::exp2f((EV + std::log2f(t)) / 2.0f);
}

/**
 * @brief Computes the exposure value from the aperture and the shutter speed
 *
 * EV = 2log2(N) - log2(t)
 */
float reverseComputeEV(float aperture, float shutterSpeed)
{
  return 2 * std::log2f(aperture) - std::log2f(shutterSpeed);
}

/**
 * @brief Finds the index of the nearest float value in an array of floats
 */
uint8_t findNearestIndex(float value, const float *array, uint8_t size)
{
  uint8_t nearestIndex = 0;
  float nearestDistance = std::abs(value - array[0]);
  for (uint8_t i = 1; i < size; ++i)
  {
    float distance = std::abs(value - array[i]);
    if (distance < nearestDistance)
    {
      nearestIndex = i;
      nearestDistance = distance;
      if (distance == 0.0f)
        break;
    }
  }
  return nearestIndex;
}