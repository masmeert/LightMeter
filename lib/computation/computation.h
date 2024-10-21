#ifndef COMPUTATION
#define COMPUTATION

float compensate_lux_reading(float reading);

float calculate_shutter_speed(float aperture, float ev);

float calculate_aperture(float shutter_speed, float ev);

#endif