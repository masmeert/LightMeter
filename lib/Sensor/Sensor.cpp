#include <Adafruit_VEML7700.h>
#include <cmath>

#include <Constants.h>

Adafruit_VEML7700 Sensor = Adafruit_VEML7700();

void initializeSensor()
{
  if (!Sensor.begin())
  {
    Serial.println("Failed to initialize VEML7700");
    while (1)
      ;
  }
  Sensor.setGain(VEML7700_GAIN_1_8);
  Sensor.setIntegrationTime(VEML7700_IT_25MS);
  Sensor.setLowThreshold(10000);
  Sensor.setHighThreshold(20000);
  Sensor.interruptEnable(true);
}

/**
 * @brief Corrects the lux value for high illumination levels (> 1000 lux)
 *
 * This function applies a correction formula for the VEML7700 light sensor
 * when using GAIN levels 1/4 and 1/8, or when illumination is above 1000 lux.
 * The correction is based on a polynomial formula provided by the manufacturer.
 *
 * @note This correction should be applied for illuminations > 1000 lux
 *       or when using GAIN levels 1/4 and 1/8.
 */
float correctLux(float lux)
{
  float lux2 = lux * lux;
  float lux3 = lux2 * lux;
  float lux4 = lux3 * lux;
  return (6.0135e-13f * lux4) - (9.3924e-9f * lux3) +
         (8.1488e-5f * lux2) + (1.0023f * lux);
}

/**
 * @brief Reads the light and converts it to an exposure value (EV)
 *
 * This function reads the light value from the sensor, corrects it, and then
 * converts it to an exposure value (EV) using the formula:
 * EV_ISO = EV_100 * (ISO / 100)
 * Where EV_100 is log2(lux / 2.5)
 *
 */
float readEV()
{
  float clux = correctLux(Sensor.readLux());
  return std::log2f(clux / 2.5f) - std::log2(ISO / 100.0f);
}