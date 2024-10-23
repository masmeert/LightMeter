#ifndef TYPES_H
#define TYPES_H

struct LightMeterSettings
{
  int selected_aperture_index;
  int selected_shutter_speed_index;
  bool aperture_priority;
  float shutter_speed;
  float aperture;
};

#endif