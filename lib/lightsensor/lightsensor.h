#ifndef LIGHTSENSOR
#define LIGHTSENSOR

#include <Adafruit_VEML7700.h>

extern Adafruit_VEML7700 VEML;

void setup_light_sensor();
float read_exposure_value();

#endif