#ifndef TYPES_H
#define TYPES_H

enum class ExposureMode
{
  AperturePriority,
  ShutterPriority
};

struct LightMeterSettings
{
  ExposureMode mode;
  int selected_aperture_index;
  float aperture;
  int selected_shutter_speed_index;
  float shutter_speed;
};

#endif