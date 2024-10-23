#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <cstdint>

// Camera settings
constexpr int FILM_ISO = 800;

// Display settings
constexpr int SCREEN_WIDTH = 120;
constexpr int SCREEN_HEIGHT = 32;

// Aperture and shutter speed settings
constexpr std::array<float, 7> APERTURES = {2.8f, 4.0f, 5.6f, 8.0f, 11.0f, 16.0f, 22.0f};
constexpr std::array<float, 13> SHUTTER_SPEEDS = {
    4.0f, 2.0f, 1.0f, 0.5f, 0.25f, 0.125f, 0.06666667f,
    0.03333333f, 0.01666667f, 0.008f, 0.004f, 0.002f, 0.001f};

// Button pin assignments
constexpr uint8_t SETTINGS_BUTTON = 3;
constexpr uint8_t PRIORITY_BUTTON = 4;

// Timing constants
constexpr int DEBOUNCE_DELAY_MS = 250;

#endif // CONSTANTS_H
