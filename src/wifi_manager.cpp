#include "wifi_manager.h"
#include "config.h"
#include "secrets.h"
#include <WiFi.h>

void setupNetwork() {
    pinMode(WIFI_STATUS_LED, OUTPUT);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(WIFI_STATUS_LED, HIGH);
        delay(500);
        digitalWrite(WIFI_STATUS_LED, LOW);
        delay(500);
    }
    digitalWrite(WIFI_STATUS_LED, HIGH);

    configTime(19800, 0, "pool.ntp.org");
}

void updateNetworkStatus() {
    // If we lose connection during operation, start blinking again
    if (WiFi.status() != WL_CONNECTED) {
        digitalWrite(WIFI_STATUS_LED, !digitalRead(WIFI_STATUS_LED));
        delay(500); 
    } else {
        digitalWrite(WIFI_STATUS_LED, HIGH);
    }
}

bool isNetworkConnected() {
    return WiFi.status() == WL_CONNECTED;
}