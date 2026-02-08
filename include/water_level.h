#ifndef WATER_LEVEL_H
#define WATER_LEVEL_H
#include <Arduino.h>

void setupWaterHardware();
bool waterNeedsFilling();
bool isFillWindow();
void stopFilling();
void startFilling();
void managePump();

#endif