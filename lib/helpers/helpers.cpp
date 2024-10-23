#include <Arduino.h>

#include <constants.h>
#include <computation.h>
#include <types.h>

float absolute_value(float value)
{
    return value >= 0 ? value : -value;
}

bool is_button_pressed(int pin)
{
    if (digitalRead(pin) == HIGH)
    {
        delay(DEBOUNCE_DELAY_MS);
        return digitalRead(pin) == HIGH;
    }
    return false;
}

void reset_exposure_settings(LightMeterSettings &settings)
{
    switch (settings.mode)
    {
    case ExposureMode::AperturePriority:
        settings.selected_aperture_index = DEFAULT_APERTURE_INDEX;
        break;
    case ExposureMode::ShutterPriority:
        settings.selected_shutter_speed_index = DEFAULT_SHUTTER_SPEED_INDEX;
        break;
    }
}

void handle_button_pressed(LightMeterSettings &settings, float EV)
{
    if (is_button_pressed(PRIORITY_BUTTON))
    {
        settings.mode = (settings.mode == ExposureMode::AperturePriority) ? ExposureMode::ShutterPriority : ExposureMode::AperturePriority;
        reset_exposure_settings(settings);
    }
    else if (is_button_pressed(SETTINGS_BUTTON))
    {
        switch (settings.mode)
        {
        case ExposureMode::AperturePriority:
        {
            settings.selected_aperture_index = (settings.selected_aperture_index + 1) % (sizeof(APERTURES) / sizeof(APERTURES[0]));
            break;
        }
        case ExposureMode::ShutterPriority:
        {
            settings.selected_shutter_speed_index = (settings.selected_shutter_speed_index + 1) % (sizeof(SHUTTER_SPEEDS) / sizeof(SHUTTER_SPEEDS[0]));
            break;
        }
        }
    }
    compute_exposure_settings(settings, EV);
}

size_t find_closest_index(const float values[], float target, size_t size)
{
    size_t closest_index = 0;
    float smallest_difference = absolute_value(values[0] - target);

    for (size_t i = 1; i < size; ++i)
    {
        float difference = absolute_value(values[i] - target);
        if (difference < smallest_difference)
        {
            smallest_difference = difference;
            closest_index = i;
        }
    }

    return closest_index;
}