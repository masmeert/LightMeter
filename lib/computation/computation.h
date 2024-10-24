#ifndef COMPUTATION_H_
#define COMPUTATION_H_

#include <cstdint>

float computeShutterSpeed(float EV, float N);
float computeAperture(float EV, float t);
float reverseComputeEV(float aperture, float shutterSpeed);
uint8_t findNearestIndex(float value, const float *array, uint8_t size);

#endif // COMPUTATION_H_