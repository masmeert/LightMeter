#include <cmath>

#include <constants.h>
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
 * Based on the exposure value formula: EV = log2((N*N)/t)-log2(S/100)
 * where t is shutter speed and N is aperture.
 * We can calculate the shutter speed with: t = (NN)/(2^EV(S/100))
 */
float calculate_shutter_speed(float aperture, float ev)
{
  return (std::pow(aperture, 2) / std::pow(2, ev)) * (FILM_ISO / 100.0f);
}

/**
 * Using the same EV formula as above,
 * We can calculate the aperture with : N = sqrt(t * 2 ^ EV * (S / 100)) float calculate_aperture(float shutter_speed, float ev)
 */
float calculate_aperture(float shutter_speed, float ev)
{
  return std::sqrt(shutter_speed * std::pow(2, ev) * (FILM_ISO / 100.0f));
}

/**
 * Compute the right exposure setting
 * base on the priority mode
 */
void compute_exposure_settings(LightMeterSettings &settings, float EV)
{
  settings.mode == ExposureMode::AperturePriority ? settings.shutter_speed = calculate_shutter_speed(settings.aperture, EV)
                                                  : settings.aperture = calculate_aperture(settings.shutter_speed, EV);
}
