#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <cstdint>

// Screen settings
const uint8_t SCREEN_WIDTH = 128; // px
const uint8_t SCREEN_HEIGHT = 32; // px
const uint8_t SCREEN_ADDRESS = 0x3C;

// Display settings
const uint8_t TEXT_COLOR = 1;      // 0 = black, 1 = white
const uint8_t LARGE_TEXT_SIZE = 2; // px
const uint8_t SMALL_TEXT_SIZE = 1; // px

// Button settings
const uint8_t INCREMENT_BUTTON_PIN = 3;
const uint8_t MODE_BUTTON_PIN = 4;

// Debounce settings
const unsigned long DEBOUNCE_DELAY_MS = 100; // ms

// Lightmeter settings
enum ExposureMode : uint8_t
{
    AperturePriority,
    ShutterPriority
};
const uint16_t ISO = 800;
const uint8_t DEFAULT_APERTURE_INDEX = 17;      // f/8
const uint8_t DEFAULT_SHUTTER_SPEED_INDEX = 15; // 1.0s
const ExposureMode DEFAULT_EXPOSURE_MODE = ExposureMode::AperturePriority;

// Aperture and shutter speed values + their display strings to avoid computation
const uint8_t APERTURE_COUNT = 36;
const uint8_t SHUTTER_SPEED_COUNT = 52;
extern const float APERTURES[APERTURE_COUNT];
extern const char *DISPLAY_APERTURES[APERTURE_COUNT];
extern const float SHUTTER_SPEEDS[SHUTTER_SPEED_COUNT];
extern const char *DISPLAY_SHUTTER_SPEEDS[SHUTTER_SPEED_COUNT];

#endif // CONSTANTS_H_