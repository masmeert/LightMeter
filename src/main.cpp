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

float calculate_shutter_speed(float aperture, float ev)
{
  float raw_shutter_speed = (aperture * aperture) / (pow(2, ev) * ISO);
  int stops_over_base = round(log2(BASE_SHUTTER_SPEED_SECONDS / raw_shutter_speed));

  return BASE_SHUTTER_SPEED_SECONDS / pow(2, stops_over_base);
}

float calculate_aperture(float shutter_speed, float ev)
{
  float raw_aperture = sqrt(shutter_speed * pow(2, ev) * ISO);
  float stops_over_base = (raw_aperture / BASE_APERTURE) / 0.5;

  return BASE_APERTURE * pow(sqrt(2), stops_over_base);
}

void setup() {}

void loop() {}