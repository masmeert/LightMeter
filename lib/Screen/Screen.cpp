#include <Adafruit_SSD1306.h>

#include "Constants.h"
#include "State.h"

Adafruit_SSD1306 Screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void initializeScreen()
{
  if (!Screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("Failed to initialize screen");
    while (1)
      ;
  }
  Screen.clearDisplay();
  Screen.display();
}

void displayLightmeterState()
{
  Screen.clearDisplay();
  Screen.setTextColor(TEXT_COLOR);
  Screen.setTextSize(LARGE_TEXT_SIZE);
  Screen.setCursor(0, 0);

  if (Lightmeter.mode == ExposureMode::AperturePriority)
    Screen.print(">");
  Screen.println(DISPLAY_APERTURES[Lightmeter.apertureIndex]);
  if (Lightmeter.mode == ExposureMode::ShutterPriority)
    Screen.print(">");
  Screen.println(DISPLAY_SHUTTER_SPEEDS[Lightmeter.shutterSpeedIndex]);

  Screen.setCursor(SCREEN_WIDTH - 30, 0);
  Screen.setTextSize(SMALL_TEXT_SIZE);
  if (Lightmeter.expositionStatus >= 0)
    Screen.print("+");
  Screen.println(Lightmeter.expositionStatus, 1);

  Screen.display();
}