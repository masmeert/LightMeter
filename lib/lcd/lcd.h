#ifndef LCD
#define LCD

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
void setup_display();
void display_values(float EV, float shutter_speed, float aperture);

#endif