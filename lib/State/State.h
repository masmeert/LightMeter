#ifndef STATE_H_
#define STATE_H_

#include "Constants.h"

struct LightmeterState
{
  float EV;
  uint8_t apertureIndex;
  uint8_t shutterSpeedIndex;
  ExposureMode mode;
  float expositionStatus;
};
extern LightmeterState Lightmeter;
void initializeLightMeterState();
void changeExposureMode();
void incrementSetting();
void getExpositionStatus();
void meter();
bool isButtonPressed(int pin);
void handleButtonPress();

#endif // STATE_H_