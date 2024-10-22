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

const int SETTINGS_BUTTON = 4;

// Set aperture to 2.8 by default
int selected_aperture_index = 0;

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

void setup()
{
  Serial.begin(115200);

  pinMode(SETTINGS_BUTTON, INPUT);
  initialize_veml();
  initialize_lcd();
}

void loop()
{
  // Read light
  float reading = VEML.readLux();
  float ev = convert_reading_to_ev(reading);

  // Change prioritised setting on input
  if (digitalRead(SETTINGS_BUTTON) == HIGH)
  {
    // Debounce delay
    delay(250);
    selected_aperture_index++;
    if (selected_aperture_index >= static_cast<int>(sizeof(APERTURES) / sizeof(APERTURES[0])))
      selected_aperture_index = 0; // Reset to the first aperture if on the last
  }

  // Base display settings
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Camera settings display
  float aperture = APERTURES[selected_aperture_index];
  std::string shutter_speed = calculate_shutter_speed(aperture, ev);
  display.setCursor(0, 0);
  display.println(aperture);
  display.println(shutter_speed.c_str());

  // Debug display
  display.setTextSize(1);
  display.setCursor(60, 0);
  display.print("ISO: ");
  display.println(ISO);
  display.setCursor(60, 10);
  display.print("EV:");
  display.println(ev);

  display.display();
  delay(250);
}