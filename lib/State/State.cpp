#include <Arduino.h>

#include "Constants.h"
#include "Computation.h"
#include "State.h"
#include "Sensor.h"

LightmeterState Lightmeter;

void initializeLightMeterState()
{
  Lightmeter.EV = 0.0f;
  Lightmeter.apertureIndex = DEFAULT_APERTURE_INDEX;
  Lightmeter.shutterSpeedIndex = DEFAULT_SHUTTER_SPEED_INDEX;
  Lightmeter.mode = DEFAULT_EXPOSURE_MODE;
}

void changeExposureMode()
{
  Lightmeter.mode = Lightmeter.mode == ExposureMode::AperturePriority ? ExposureMode::ShutterPriority : ExposureMode::AperturePriority;
}

void incrementSetting()
{
  if (Lightmeter.mode == ExposureMode::AperturePriority)
    Lightmeter.apertureIndex = (Lightmeter.apertureIndex + 1) % APERTURE_COUNT;
  else
    Lightmeter.shutterSpeedIndex = (Lightmeter.shutterSpeedIndex + 1) % SHUTTER_SPEED_COUNT;
}

void getExpositionStatus()
{
  float computedEV = reverseComputeEV(APERTURES[Lightmeter.apertureIndex], SHUTTER_SPEEDS[Lightmeter.shutterSpeedIndex]);
  Lightmeter.expositionStatus = computedEV - Lightmeter.EV;
}

void meter()
{
  Lightmeter.EV = readEV();
  switch (Lightmeter.mode)
  {
  case ExposureMode::AperturePriority:
  {
    float shutterSpeed = computeShutterSpeed(Lightmeter.EV, APERTURES[Lightmeter.apertureIndex]);
    Lightmeter.shutterSpeedIndex = findNearestIndex(shutterSpeed, SHUTTER_SPEEDS, SHUTTER_SPEED_COUNT);
    break;
  }
  case ExposureMode::ShutterPriority:
  {
    float aperture = computeAperture(Lightmeter.EV, SHUTTER_SPEEDS[Lightmeter.shutterSpeedIndex]);
    Lightmeter.apertureIndex = findNearestIndex(aperture, APERTURES, APERTURE_COUNT);
    break;
  }
  }
  getExpositionStatus();
}

bool isButtonPressed(int pin)
{
  if (digitalRead(pin) == HIGH)
  {
    delay(DEBOUNCE_DELAY_MS);
    return digitalRead(pin) == HIGH;
  }
  return false;
}

void handleButtonPress()
{
  if (isButtonPressed(MODE_BUTTON_PIN))
    changeExposureMode();
  else if (isButtonPressed(INCREMENT_BUTTON_PIN))
    incrementSetting();
}