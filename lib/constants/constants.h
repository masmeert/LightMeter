#ifndef CONSTANTS
#define CONSTANTS

const float APERTURES[] = {2.8, 4.0, 5.6, 8.0, 11.0, 16.0, 22.0};
const float SHUTTER_SPEEDS[] = {1.0 / 1000, 1.0 / 500, 1.0 / 250, 1.0 / 125, 1.0 / 60, 1.0 / 30, 1.0 / 15, 1.0 / 8, 1.0 / 4, 1.0 / 2, 1.0, 2.0};

const int APERTURES_COUNT = sizeof(APERTURES) / sizeof(APERTURES[0]);
const int SHUTTER_SPEEDS_COUNT = sizeof(SHUTTER_SPEEDS) / sizeof(SHUTTER_SPEEDS[0]);

const float BASE_APERTURE = 1.0;
const float BASE_SHUTTER_SPEED = 1.0;

const int ISO = 400;

const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 32;

#endif