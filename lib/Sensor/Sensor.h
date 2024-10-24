#ifndef SENSOR_H_
#define SENSOR_H_

#include <Adafruit_VEML7700.h>

extern Adafruit_VEML7700 Sensor;

void initializeSensor();
float correctLux(float lux);
float readEV();

#endif // SENSOR_H_