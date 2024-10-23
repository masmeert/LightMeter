#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <types.h>

float compensate_lux_reading(float reading);
float convert_reading_to_ev(float reading);
float convert_settings_to_ev(LightMeterSettings &settings);
float calculate_shutter_speed(float aperture, float ev);
float calculate_aperture(float shutter_speed, float ev);
float sanitize_shutter_speed(float shutter_speed);
void compute_exposure_settings(LightMeterSettings &settings, float EV);

#endif