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

float unformat_shutter_speed(const std::string &shutter_speed_str)
{
  // Check if the string is in the form "1/Xs" (fractional shutter speed)
  if (shutter_speed_str.find("1/") != std::string::npos)
  {
    // Extract the denominator (X) from the string, which is after "1/"
    std::size_t slash_pos = shutter_speed_str.find('/');
    std::size_t s_pos = shutter_speed_str.find('s');

    if (slash_pos != std::string::npos && s_pos != std::string::npos)
    {
      // Extract the number after "1/"
      std::string denominator_str = shutter_speed_str.substr(slash_pos + 1, s_pos - slash_pos - 1);

      // Check if denominator_str contains only digits
      for (char c : denominator_str)
      {
        if (!isdigit(c))
        {
          return -1.0f; // Return -1.0 if it's not a valid number
        }
      }

      // Convert the denominator to an integer
      int denominator = atoi(denominator_str.c_str());
      if (denominator > 0)
      {
        return 1.0f / static_cast<float>(denominator);
      }
    }
  }
  // Check if the string is in the form "X.Xs" (whole or decimal shutter speed)
  else if (shutter_speed_str.find("s") != std::string::npos)
  {
    // Extract the number before "s"
    std::size_t s_pos = shutter_speed_str.find('s');
    std::string speed_str = shutter_speed_str.substr(0, s_pos);

    // Check if speed_str is a valid float
    bool dot_found = false;
    for (char c : speed_str)
    {
      if (c == '.')
      {
        if (dot_found)
        {
          return -1.0f; // Invalid if there are multiple dots
        }
        dot_found = true;
      }
      else if (!isdigit(c))
      {
        return -1.0f; // Return -1.0 if it's not a valid number
      }
    }

    // Convert the speed_str to a float
    return atof(speed_str.c_str());
  }

  // Return -1.0 if the input format is invalid
  return -1.0f;
}