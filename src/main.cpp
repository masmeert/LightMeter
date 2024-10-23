#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <string>

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
      0,      // 4.0s
      12,     // 1/1000s
      true,   // aperture priority
      0.001f, // 1/1000s
      2.8f    // aperture
  };
}

void loop()
{
  float EV = read_exposure_value();

  handle_button_pressed(light_meter_settings.aperture_priority, EV,
                        light_meter_settings.shutter_speed, light_meter_settings.aperture,
                        light_meter_settings.selected_aperture_index,
                        light_meter_settings.selected_shutter_speed_index);

  Serial.println(light_meter_settings.shutter_speed, 3);
  display_values(EV, light_meter_settings.shutter_speed, light_meter_settings.aperture);
  delay(DEBOUNCE_DELAY_MS);
}
