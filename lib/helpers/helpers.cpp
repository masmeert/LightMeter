#include <Arduino.h>

#include <constants.h>
#include <computation.h>

bool is_button_pressed(int pin)
{
    if (digitalRead(pin) == HIGH)
    {
        delay(DEBOUNCE_DELAY_MS);
        return true;
    }
    return false;
}

void reset_exposure_settings(bool aperture_priority, float &shutter_speed, float &aperture, int &selected_aperture_index, int &selected_shutter_speed_index)
{
    if (aperture_priority)
    {
        selected_aperture_index = 0;
        aperture = 2.8f;
    }
    else
    {
        selected_shutter_speed_index = 12;
        shutter_speed = 0.001f;
    }
}

void handle_button_pressed(bool &aperture_priority, float EV, float &shutter_speed, float &aperture, int &selected_aperture_index, int &selected_shutter_speed_index)
{
    if (is_button_pressed(PRIORITY_BUTTON))
    {
        aperture_priority = !aperture_priority;
        reset_exposure_settings(aperture_priority, shutter_speed, aperture, selected_aperture_index, selected_shutter_speed_index);
    }

    if (is_button_pressed(SETTINGS_BUTTON))
    {
        if (aperture_priority)
        {
            selected_aperture_index = (selected_aperture_index + 1) % (sizeof(APERTURES) / sizeof(APERTURES[0]));
            aperture = APERTURES[selected_aperture_index];
        }
        else
        {
            selected_shutter_speed_index = (selected_shutter_speed_index + 1) % (sizeof(SHUTTER_SPEEDS) / sizeof(SHUTTER_SPEEDS[0]));
            shutter_speed = SHUTTER_SPEEDS[selected_shutter_speed_index];
        }
    }

    compute_exposure_settings(aperture_priority, EV, shutter_speed, aperture);
}
