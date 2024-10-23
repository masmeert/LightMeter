#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

#include <types.h>

// Camera settings
constexpr int FILM_ISO = 800;

// Display settings
constexpr int SCREEN_WIDTH = 120;
constexpr int SCREEN_HEIGHT = 32;

// Aperture and shutter speed settings
constexpr float APERTURES[] = {2.8f, 4.0f, 5.6f, 8.0f, 11.0f, 16.0f, 22.0f};
constexpr float SHUTTER_SPEEDS[] = {
    4.0f, 2.0f, 1.0f, 0.5f, 0.25f, 0.125f, 0.06666667f,
    0.03333333f, 0.01666667f, 0.008f, 0.004f, 0.002f, 0.001f};
constexpr size_t SHUTTER_SPEEDS_SIZE = sizeof(SHUTTER_SPEEDS) / sizeof(SHUTTER_SPEEDS[0]);
constexpr size_t APERTURES_SIZE = sizeof(APERTURES) / sizeof(APERTURES[0]);

// Button pin assignments
constexpr uint8_t SETTINGS_BUTTON = 3;
constexpr uint8_t PRIORITY_BUTTON = 4;

// Timing constants
constexpr int DEBOUNCE_DELAY_MS = 250;

// Default light meter settings
constexpr ExposureMode DEFAULT_EXPOSURE_MODE = ExposureMode::AperturePriority;
constexpr int DEFAULT_APERTURE_INDEX = 0;
constexpr int DEFAULT_SHUTTER_SPEED_INDEX = 12;

#endif // CONSTANTS_H
