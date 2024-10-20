#include <Arduino.h>

#define ISO 400
#define BASE_APERTURE 1.0
#define BASE_SHUTTER_SPEED_SECONDS 1.0

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
 * Based on the exposure value formula: EV = log2((N*N)/t)-log2(S/100)
 * where t is shutter speed and N is aperture.
 * We can calculate the shutter speed with: t = (N*N)/(2^EV*(S/100))
 * Each full stop is calculated as either doubling or halving the previous value
 * Standard shutter speeds (1/1000, 1/500, 1/250, etc.) follow the formula: S = S_0 / 2^n, 
 * where S_0 is the base shutter speed and n is the number of stops from the base.
 */
float calculate_shutter_speed(float aperture, float ev)
{
  float raw_shutter_speed = (aperture * aperture) / (pow(2, ev) * (ISO / 100));
  int stops_over_base = round(log2(BASE_SHUTTER_SPEED_SECONDS / raw_shutter_speed));

  return BASE_SHUTTER_SPEED_SECONDS / pow(2, stops_over_base);
}

/**
 * Using the same EV formula as above,
 * We can calculate the aperture with: N = sqrt(t*2^EV*(S/100))
 * Each full f-stop is calculated by multiplying or dividing by sqrt(2)
 * Standard aperture sequence (f/1.0, f/1.4, f/2.0, f/2.8, etc.) is based on f = f_0 * (sqrt(2))^n, 
 * where f_0 is the base aperture (like f/1.0), and n is the number of stops from the base.
 */
float calculate_aperture(float shutter_speed, float ev)
{
  float raw_aperture = sqrt(shutter_speed * pow(2, ev) * (ISO / 100));
  float stops_over_base = (raw_aperture / BASE_APERTURE) / 0.5;

  return BASE_APERTURE * pow(sqrt(2), stops_over_base);
}

void setup() {}

void loop() {}