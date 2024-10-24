#include <Arduino.h>

#include "Constants.h"
#include "Sensor.h"
#include "Screen.h"
#include "State.h"

void setup()
{
  Serial.begin(115200);
  initializeSensor();
  initializeScreen();
  initializeLightMeterState();
  pinMode(INCREMENT_BUTTON_PIN, INPUT);
  pinMode(MODE_BUTTON_PIN, INPUT);
}

void loop()
{
  handleButtonPress();
  meter();
  displayLightmeterState();
  delay(DEBOUNCE_DELAY_MS);
}