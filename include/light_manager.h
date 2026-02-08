#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include <Arduino.h>

void setupLightHardware();
void manageLight();
void setLightOverride(int value);
void resetLightQuota();

#endif