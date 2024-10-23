#include <Adafruit_VEML7700.h>

#include <computation.h>

Adafruit_VEML7700 VEML = Adafruit_VEML7700();

void setup_light_sensor()
{
    if (!VEML.begin())
    {
        Serial.println("Failed to init VEML7700.");
        return;
    }
    VEML.setGain(VEML7700_GAIN_1);
    VEML.setIntegrationTime(VEML7700_IT_25MS);
    VEML.setLowThreshold(10000);
    VEML.setHighThreshold(20000);
    VEML.interruptEnable(true);
}

float read_exposure_value()
{
    float lux_reading = VEML.readLux();
    return convert_reading_to_ev(lux_reading);
}