#ifndef HELPERS
#define HELPERS

bool is_button_pressed(int pin);
void handle_button_pressed(bool &aperture_priority, float EV, float &shutter_speed, float &aperture, int &selected_aperture_index, int &selected_shutter_speed_index);
void reset_exposure_settings(bool aperture_priority, float &shutter_speed, float &aperture, int &selected_aperture_index, int &selected_shutter_speed_index);

#endif
