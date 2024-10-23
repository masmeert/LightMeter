#ifndef HELPERS_H
#define HELPERS_H

bool is_button_pressed(int pin);
void handle_button_pressed(LightMeterSettings &settings, float EV);
void reset_exposure_settings(LightMeterSettings &settings);

#endif
