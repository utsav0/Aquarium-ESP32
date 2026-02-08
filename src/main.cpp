#include <Arduino.h>
#include "wifi_manager.h"
#include "blynk_manager.h"
#include "water_level.h"
#include "light_manager.h"

void setup() {
    Serial.begin(115200);
    setupNetwork();
    setupBlynk();
    setupWaterHardware();
    setupLightHardware();
    
    if (isNetworkConnected()) {
        syncBlynkSettings();
    }
}

void loop() {
    updateNetworkStatus();
    runBlynk();
    if (isNetworkConnected()) {
        managePump();
        manageLight();
    }
    
    delay(100);
}