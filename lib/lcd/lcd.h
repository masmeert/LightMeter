#ifndef LCD_H
#define LCD_H

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
void setup_display();
void display_values(LightMeterSettings &settings, float EV);

#endif