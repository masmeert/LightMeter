#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <string>

float compensate_lux_reading(float reading);
float convert_reading_to_ev(float reading);
float calculate_shutter_speed(float aperture, float ev);
float calculate_aperture(float shutter_speed, float ev);
void compute_exposure_settings(bool aperture_priority, float EV, float &shutter_speed, float &aperture);

#endif