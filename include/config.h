#ifndef CONFIG_H
#define CONFIG_H

// Hardware Pins
#define WATER_PUMP_PIN 4
#define WATER_SENSOR_PIN 25
#define WIFI_STATUS_LED 12
#define LIGHT_RELAY_PIN 13

// Pump Schedule
const int FILL_HOUR_START = 16;
const int FILL_MINUTE_START = 35;
const int FILL_DURATION_MINS = 7;

// Light Schedule (10:30 AM to 8:00 PM)
const int LIGHT_HOUR_START = 10;
const int LIGHT_MINUTE_START = 30;
const int LIGHT_HOUR_END = 20;
const int LIGHT_MINUTE_END = 0;

// Light Settings
const unsigned int LIGHT_QUOTA_HOURS = 8;
const unsigned int TOTAL_LIGHT_SECONDS = LIGHT_QUOTA_HOURS * 3600;

const unsigned long LIGHT_UPDATE_INTERVAL_MS = 1000;

const unsigned int LIGHT_SAVE_INTERVAL_MINS = 10;
const unsigned long LIGHT_SAVE_INTERVAL_MS = LIGHT_SAVE_INTERVAL_MINS * 60 * 1000;

// Blynk Virtual Pins
#define V_PIN_PUMP_MODES V0
#define V_PIN_LIGHT_MANUAL V1
#define V_PIN_LIGHT_RESET V2

#endif