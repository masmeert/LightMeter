#include <Arduino.h>
#include <Adafruit_VEML7700.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <string>

#include <constants.h>
#include <computation.h>

Adafruit_VEML7700 VEML = Adafruit_VEML7700();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

const int SETTINGS_BUTTON = 3;
const int PRIORITY_BUTTON = 4;

// Set aperture to 2.8 by default
int selected_aperture_index = 0;
// Set shutter speed to 1/1000s by default
int selected_shutter_speed_index = 12;

// 1 = Aperture priority, 0 = shutter priority
bool priority_mode = 1;

float shutter_speed = 0.001f;
float aperture = 2.8f;

void initialize_veml()
{
  if (!VEML.begin())
  {
    Serial.println("Failed to init VEML7700.");
    return;
  }
  VEML.setGain(VEML7700_GAIN_1);
  VEML.setIntegrationTime(VEML7700_IT_25MS);
  VEML.setLowThreshold(10000);
  VEML.setHighThreshold(20000);
  VEML.interruptEnable(true);
}

void initialize_lcd()
{
  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Failed to initialize VEML7700 sensor.");
    return;
  }
  display.clearDisplay();
  display.display();
}

void compute_settings(float ev)
{
  if (priority_mode)
  {
    shutter_speed = calculate_shutter_speed(aperture, ev);
  }
  else
  {
    aperture = calculate_aperture(shutter_speed, ev);
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(SETTINGS_BUTTON, INPUT);
  pinMode(PRIORITY_BUTTON, INPUT);
  initialize_veml();
  initialize_lcd();
}

void loop()
{
  // Read light
  float reading = VEML.readLux();
  float ev = convert_reading_to_ev(reading);
  compute_settings(ev);

  // Base display settings
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Change priority mode on input
  if (digitalRead(PRIORITY_BUTTON) == HIGH)
  {
    delay(250);
    priority_mode = !priority_mode;
  }

  // Change aperture on input
  if (digitalRead(SETTINGS_BUTTON) == HIGH)
  {
    // Debounce delay
    delay(250);
    if (priority_mode)
    {
      selected_aperture_index++;
      if (selected_aperture_index >= static_cast<int>(sizeof(APERTURES) / sizeof(APERTURES[0])))
        selected_aperture_index = 0;

      aperture = APERTURES[selected_aperture_index];
    }
    else
    {
      selected_shutter_speed_index++;
      if (selected_shutter_speed_index >= static_cast<int>(sizeof(SHUTTER_SPEEDS) / sizeof(SHUTTER_SPEEDS[0])))
        selected_shutter_speed_index = 0;

      shutter_speed = SHUTTER_SPEEDS[selected_shutter_speed_index];
    }
    compute_settings(ev);
  }

  // display
  display.setCursor(0, 0);
  display.println(aperture);
  display.println(shutter_speed, 4);

  // Debug display
  display.setTextSize(1);
  display.setCursor(60, 0);
  display.print("ISO: ");
  display.println(ISO);
  display.setCursor(60, 8);
  display.print("EV:");
  display.println(ev);

  display.display();
  delay(250);
}