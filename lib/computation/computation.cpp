#include <cmath>

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
float calculate_shutter_speed(float aperture, float ev)
{
  // Calculate raw shutter speed in seconds using the formula
  return (pow(aperture, 2) / pow(2, ev)) * 100 / ISO;
}

/**
 * Using the same EV formula as above,
 * We can calculate the aperture with : N = sqrt(t * 2 ^ EV * (S / 100)) float calculate_aperture(float shutter_speed, float ev)
 */
float calculate_aperture(float shutter_speed, float ev)
{
  return sqrt(shutter_speed * pow(2, ev) * ISO);
}

float find_closest_aperture(float calculated_aperture)
{
  float closest_aperture = 0.0f;

  for (int i = 0; i < sizeof(APERTURES) / sizeof(APERTURES[0]); ++i)
  {
    if (APERTURES[i] <= calculated_aperture)
    {
      closest_aperture = APERTURES[i];
    }
    else
    {
      break;
    }
  }

  return closest_aperture;
}

/**
 * Compute the right exposure setting
 * base on the priority mode
 */
void compute_exposure_settings(bool aperture_priority, float EV, float &shutter_speed, float &aperture)
{
  if (aperture_priority)
  {
    shutter_speed = calculate_shutter_speed(aperture, EV);
  }
  else
  {
    aperture = calculate_aperture(shutter_speed, EV);
  }
}