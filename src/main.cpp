#include <Arduino.h>
#include <Adafruit_VEML7700.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#include <constants.h>
#include <computation.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  if (!veml.begin())
  {
    Serial.println("Failed to initialize VEML7700 sensor.");
    while (1)
      ;
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed.");
    while (1)
      ;
  }

  // VEML7700 settings
  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_25MS);
  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);

  // Clear the display buffer
  display.clearDisplay();
  display.display();
}

void loop()
{
  float reading = veml.readLux();
  float ev = convert_reading_to_ev(reading);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("EV: ");
  display.println(ev);
  display.display();

  delay(500);
}