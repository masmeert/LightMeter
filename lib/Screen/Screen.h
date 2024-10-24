#ifndef SCREEN_H_
#define SCREEN_H_

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 Screen;
void initializeScreen();
void displayLightmeterState();

#endif // SCREEN_H_