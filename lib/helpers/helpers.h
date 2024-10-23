#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"

float absolute_value(float value);
bool is_button_pressed(int pin);
void handle_button_pressed(LightMeterSettings &settings, float EV);
void reset_exposure_settings(LightMeterSettings &settings);
size_t find_closest_index(const float values[], float target, size_t size);

#endif