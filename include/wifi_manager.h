#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

void setupNetwork();
void updateNetworkStatus();
bool isNetworkConnected();

#endif