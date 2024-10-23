#ifndef CONSTANTS
#define CONSTANTS

const int FILM_ISO = 800;
const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 32;

const float APERTURES[] = {2.8f, 4.0f, 5.6f, 8.0f, 11.0f, 16.0f, 22.0f};
const float SHUTTER_SPEEDS[] = {4.0f, 2.0f, 1.0f, 0.5f, 0.25f, 0.125f, 0.06666667f, 0.03333333f, 0.01666667f, 0.008f, 0.004f, 0.002f, 0.001f};
const float FRACTIONAL_SHUTTER_SPEEDS[] = {0.5f, 0.25f, 0.125f, 0.06666667f, 0.03333333f, 0.01666667f, 0.008f, 0.004f, 0.002f, 0.001f};
const int FRACTIONAL_SHUTTER_SPEEDS_DENOMINATOR[] = {2, 4, 8, 15, 30, 60, 125, 250, 500, 1000};

const int SETTINGS_BUTTON = 3;
const int PRIORITY_BUTTON = 4;

const int DEBOUNCE_DELAY_MS = 250;

#endif