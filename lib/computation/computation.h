#ifndef COMPUTATION
#define COMPUTATION

#include <string>

float compensate_lux_reading(float reading);

float convert_reading_to_ev(float reading);

std::string calculate_shutter_speed(float aperture, float ev);

#endif