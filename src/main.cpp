#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <string>

#include <constants.h>
#include <computation.h>
#include <helpers.h>
#include <lcd.h>
#include <lightsensor.h>

int selected_aperture_index;
int selected_shutter_speed_index;
bool aperture_priority;
float shutter_speed;
float aperture;

void setup()
{
  Serial.begin(115200);

  pinMode(SETTINGS_BUTTON, INPUT);
  pinMode(PRIORITY_BUTTON, INPUT);
  setup_light_sensor();
  setup_display();

  // Set aperture to 2.8 by default
  selected_aperture_index = 0;
  aperture = 2.8f;
  // Set shutter speed to 1/1000s by default
  selected_shutter_speed_index = 12;
  // Set to aperture priority by default
  aperture_priority = 1;
}

void loop()
{
  float EV = read_exposure_value();

  handle_button_pressed(aperture_priority, EV, shutter_speed, aperture, selected_aperture_index, selected_shutter_speed_index);
  display_values(EV, shutter_speed, aperture);
  delay(DEBOUNCE_DELAY_MS);
}