#include <cmath>

#include <constants.h>
#include <helpers.h>
#include <types.h>

/**
 * The VEML7700 provides a LUX value between 0 and 1000
 * once 1000lx is exceeded the sensor's response starts to deviate from a direct linear scale.
 * To correct for this behavior, the manufacturer provides the following formula.
 */
float compensate_lux_reading(float reading)
{
  return (6.0135e-13f * std::pow(reading, 4)) - (9.3924e-9f * std::pow(reading, 3)) +
         (8.1488e-5f * std::pow(reading, 2)) + (1.0023f * reading);
}

/**
 * Convert the lux reading to an exposure value
 */
float convert_reading_to_ev(float reading)
{
  return std::log2((compensate_lux_reading(reading) / 2.5f));
}

/**
 * Convert settings to EV
 */
float convert_settings_to_ev(LightMeterSettings &settings)
{
  float aperture = APERTURES[settings.selected_aperture_index];
  float shutter_speed = SHUTTER_SPEEDS[settings.selected_shutter_speed_index];
  return std::log2((aperture * aperture) / shutter_speed) - std::log2(ISO / 100.0f);
}

/**
 * Based on the exposure value formula: EV = log2((N*N)/t)-log2(S/100)
 * where t is shutter speed and N is aperture.
 * We can calculate the shutter speed with: t = (NN)/(2^EV(S/100))
 */
float calculate_shutter_speed(float aperture, float ev)
{
  return (std::pow(aperture, 2) / std::pow(2, ev)) * (ISO / 100.0f);
}

/**
 * Using the same EV formula as above,
 * We can calculate the aperture with : N = sqrt(t * 2 ^ EV * (S / 100)) float calculate_aperture(float shutter_speed, float ev)
 */
float calculate_aperture(float shutter_speed, float ev)
{
  return std::sqrt(shutter_speed * std::pow(2, ev) * (ISO / 100.0f));
}

/**
 * Convert shutter speed from seconds to fraction of a second
 * if >= 1, else return a rounded value
 */
float sanitize_shutter_speed(float shutter_speed)
{
  if (shutter_speed < 0)
    return -1.0f;

  if (shutter_speed >= 1.0f)
    return round(shutter_speed * 2.0f) / 2.0f;

  float denominator = 1.0f / shutter_speed;
  size_t closest_index = find_closest_index(SHUTTER_SPEEDS_DENOMINATORS, denominator, SHUTTER_SPEEDS_DENOMINATORS_SIZE);
  return SHUTTER_SPEEDS_DENOMINATORS[closest_index];
}

/**
 * Compute the right exposure setting
 * base on the priority mode
 */
void compute_exposure_settings(LightMeterSettings &settings, float EV)
{
  switch (settings.mode)
  {
  case ExposureMode::AperturePriority:
  {
    float shutter_speed = calculate_shutter_speed(APERTURES[settings.selected_aperture_index], EV);
    settings.selected_shutter_speed_index = find_closest_index(SHUTTER_SPEEDS, shutter_speed, SHUTTER_SPEEDS_SIZE);
    break;
  }
  case ExposureMode::ShutterPriority:
  {
    float aperture = calculate_aperture(SHUTTER_SPEEDS[settings.selected_shutter_speed_index], EV);
    settings.selected_aperture_index = find_closest_index(APERTURES, aperture, APERTURES_SIZE);
    break;
  }
  // Add a default case to handle all enum values
  default:
    // Handle unexpected mode or do nothing
    break;
  }
}
