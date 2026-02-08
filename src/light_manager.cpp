#include "light_manager.h"
#include "config.h"
#include <Preferences.h>
#include <time.h>

Preferences lightPrefs;
unsigned long lastLightUpdateMillis = 0;
unsigned long lastFlashSaveMillis = 0;
int lightOverrideMode = 0; 
unsigned int remainingSecondsRAM = 0;

void setupLightHardware() {
    pinMode(LIGHT_RELAY_PIN, OUTPUT);
    digitalWrite(LIGHT_RELAY_PIN, LOW);
    lightPrefs.begin("schedule", false);
    
    remainingSecondsRAM = lightPrefs.getUInt("seconds", TOTAL_LIGHT_SECONDS);
}

void setLightOverride(int value) {
    lightOverrideMode = value;

    if (lightOverrideMode == 1) {
        digitalWrite(LIGHT_RELAY_PIN, HIGH);
    } 
    else if (lightOverrideMode == 2) {
        digitalWrite(LIGHT_RELAY_PIN, LOW);
    }
}

void resetLightQuota() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return;

    remainingSecondsRAM = TOTAL_LIGHT_SECONDS;
    lightPrefs.putUInt("seconds", TOTAL_LIGHT_SECONDS);
    lightPrefs.putInt("resetDay", timeinfo.tm_yday);
}

void manageLight() {
    if (lightOverrideMode != 0) return;

    unsigned long currentMillis = millis();

    if (currentMillis - lastLightUpdateMillis >= LIGHT_UPDATE_INTERVAL_MS) {
        lastLightUpdateMillis = currentMillis;

        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) return;

        int currentMins = timeinfo.tm_hour * 60 + timeinfo.tm_min;
        int startMins = LIGHT_HOUR_START * 60 + LIGHT_MINUTE_START;
        int endMins = LIGHT_HOUR_END * 60 + LIGHT_MINUTE_END;

        bool isInsideWindow = (currentMins >= startMins && currentMins < endMins);

        if (isInsideWindow && remainingSecondsRAM > 0) {
            digitalWrite(LIGHT_RELAY_PIN, HIGH);
            if (remainingSecondsRAM > 0) remainingSecondsRAM--; 
        } else {
            digitalWrite(LIGHT_RELAY_PIN, LOW);
        }

        int lastResetDay = lightPrefs.getInt("resetDay", 0);
        if (currentMins >= endMins && timeinfo.tm_yday != lastResetDay) {
            resetLightQuota();
        }
    }

    if (currentMillis - lastFlashSaveMillis >= LIGHT_SAVE_INTERVAL_MS) {
        lastFlashSaveMillis = currentMillis;
        
        unsigned int savedSeconds = lightPrefs.getUInt("seconds", 0);
        if (savedSeconds != remainingSecondsRAM) {
            lightPrefs.putUInt("seconds", remainingSecondsRAM);
        }
    }
}