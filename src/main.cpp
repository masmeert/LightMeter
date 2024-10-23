#include <Arduino.h>
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
      DEFAULT_EXPOSURE_MODE,
      DEFAULT_APERTURE_INDEX,
      DEFAULT_SHUTTER_SPEED_INDEX,
  };
}

void loop()
{
  float EV = read_exposure_value();

  handle_button_pressed(light_meter_settings, EV);
  display_values(light_meter_settings, EV);
  delay(DEBOUNCE_DELAY_MS);
}
