#include "blynk_manager.h"
#include "config.h"
#include "secrets.h"
#include "light_manager.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int _pumpMode = 0;

void setupBlynk() {
    Blynk.config(BLYNK_AUTH_TOKEN); 
}

void runBlynk() {
    Blynk.run();
}

// Fetch values from the cloud on startup
void syncBlynkSettings() {
    Blynk.syncVirtual(V_PIN_PUMP_MODES);
}

// Virtual Pin Handlers
BLYNK_WRITE(V_PIN_PUMP_MODES) { _pumpMode = param.asInt(); }

// Getter implementations
int getPumpMode() { return _pumpMode; }

// Lights
BLYNK_WRITE(V_PIN_LIGHT_MANUAL) {
    setLightOverride(param.asInt());
}
// Lights Manual Quota Reset
BLYNK_WRITE(V_PIN_LIGHT_RESET) {
    if (param.asInt() == 1) { 
        resetLightQuota();
    }
}