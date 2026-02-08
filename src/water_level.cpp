#include "water_level.h"
#include "config.h"
#include <time.h>
#include "blynk_manager.h"
#include "wifi_manager.h"


void setupWaterHardware() {
    pinMode(WATER_SENSOR_PIN, INPUT_PULLUP);
    pinMode(WATER_PUMP_PIN, OUTPUT);
    digitalWrite(WATER_PUMP_PIN, LOW);
}

bool isFillWindow() {
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) return false;
    
    if (timeinfo.tm_hour == FILL_HOUR_START) {
    if (timeinfo.tm_min >= FILL_MINUTE_START && 
        timeinfo.tm_min < (FILL_MINUTE_START + FILL_DURATION_MINS)) {
                return true;
        }
    }
    return false;
}

void startFilling() {
    digitalWrite(WATER_PUMP_PIN, HIGH);
}

void stopFilling() {
    digitalWrite(WATER_PUMP_PIN, LOW);
}

void managePump() {
    int mode = getPumpMode();
    bool waterLow = (digitalRead(WATER_SENSOR_PIN) == HIGH);

    if (mode == 2) { // FORCE OFF
        stopFilling();
    } 
    else if (mode == 1) { // FORCE ON
        startFilling();
    } 
    else { // AUTO
        if (isFillWindow() && waterLow) {
            startFilling();
        } else {
            stopFilling();
        }
    }
}