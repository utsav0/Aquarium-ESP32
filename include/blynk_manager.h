#ifndef BLYNK_MANAGER_H
#define BLYNK_MANAGER_H

#include <Arduino.h>

void setupBlynk();
void runBlynk();
void syncBlynkSettings();

// Getters so water_level.cpp can read the app's settings
int getPumpMode();
int getDynamicStartHour();
int getDynamicDuration();

#endif