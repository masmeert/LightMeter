#include <Arduino.h>
#include <array>

#include <constants.h>
#include <computation.h>
#include <types.h>
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
        settings.selected_aperture_index = 0;
        settings.aperture = 2.8f;
        break;
    case ExposureMode::ShutterPriority:
        settings.selected_shutter_speed_index = 12;
        settings.shutter_speed = 0.001f;
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
            settings.selected_aperture_index = (settings.selected_aperture_index + 1) % APERTURES.size();
            settings.aperture = APERTURES[settings.selected_aperture_index];
            break;
        case ExposureMode::ShutterPriority:
            settings.selected_shutter_speed_index = (settings.selected_shutter_speed_index + 1) % SHUTTER_SPEEDS.size();
            settings.shutter_speed = SHUTTER_SPEEDS[settings.selected_shutter_speed_index];
            break;
        }
    }
    compute_exposure_settings(settings, EV);
}
