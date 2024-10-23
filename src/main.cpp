#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#include <constants.h>
#include <computation.h>
#include <helpers.h>
#include <lcd.h>
#include <lightsensor.h>
#include <types.h>

LightMeterSettings light_meter_settings;

void setup()
{
  Serial.begin(115200);

  pinMode(SETTINGS_BUTTON, INPUT);
  pinMode(PRIORITY_BUTTON, INPUT);
  setup_light_sensor();
  setup_display();

  // Initialize camera settings
  light_meter_settings = {
      ExposureMode::AperturePriority, // aperture priority
      0,                              // f/4
      2.8f,                           // f/4
      12,                             // 1/1000s
      0.001f                          // 1/1000s
  };
}

void loop()
{
  float EV = read_exposure_value();

  handle_button_pressed(light_meter_settings, EV);
  display_values(light_meter_settings, EV);
  delay(DEBOUNCE_DELAY_MS);
}
