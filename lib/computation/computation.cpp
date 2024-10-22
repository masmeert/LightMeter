#include <cmath>
#include <string>
#include <sstream>
#include <limits>

#include <constants.h>

/**
 * The VEML7700 provides a LUX value between 0 and 1000
 * once 1000lx is exceeded the sensor's response starts to deviate from a direct linear scale.
 * To correct for this behavior, the manufacturer provides the following formula.
 */
float compensate_lux_reading(float reading)
{
  return (6.0135e-13 * pow(reading, 4)) - (9.3924e-9 * pow(reading, 3)) + (8.1488e-5 * pow(reading, 2)) + (1.0023 * reading);
}

/**
 * Convert the lux reading to an exposure value
 */
float convert_reading_to_ev(float reading)
{
  return log2((compensate_lux_reading(reading) / 2.5));
}

/**
 * Based on the exposure value formula: EV = log2((N*N)/t)-log2(S/100)
 * where t is shutter speed and N is aperture.
 * We can calculate the shutter speed with: t = (N*N)/(2^EV*(S/100))
 */
std::string calculate_shutter_speed(float aperture, float ev)
{
  // Calculate raw shutter speed in seconds using the formula
  float raw_shutter_speed = (pow(aperture, 2) / pow(2, ev)) * 100 / ISO;

  std::ostringstream result;

  if (raw_shutter_speed >= 1.0)
  {
    // Round to the nearest 0.0 or 0.5 for shutter speeds >= 1.0
    float rounded_speed = std::round(raw_shutter_speed * 2.0) / 2.0;
    result << rounded_speed << "s";
  }
  else
  {
    // Initialize the closest shutter speed and minimum difference
    float closest = 0.0;
    float min_diff = std::numeric_limits<float>::max(); // Start with the largest possible value

    // Iterate through SHUTTER_SPEEDS to find the closest
    for (const float &shutter_speed : SHUTTER_SPEEDS)
    {
      // Calculate the equivalent speed in seconds (1/shutter_speed)
      float equivalent_speed = 1.0 / shutter_speed;

      float diff = std::abs(raw_shutter_speed - equivalent_speed);
      if (diff < min_diff)
      {
        min_diff = diff;
        closest = shutter_speed;
      }
    }

    // Check if closest was found and prevent division by zero
    if (closest > 0)
    {
      result << "1/" << static_cast<int>(closest) << "s"; // Return "1/<X>s"
    }
    else
    {
      result << "Invalid shutter speed"; // Error handling
    }
  }

  return result.str();
}