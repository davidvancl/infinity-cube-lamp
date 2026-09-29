#pragma once

#include <Arduino.h>

namespace Led {

void begin();
void apply();
void showBooting();
void turnOn();
void turnOff();
void brighter();
void dimmer();
void setColor(uint8_t r, uint8_t g, uint8_t b);
void setOverrideColor(uint8_t r, uint8_t g, uint8_t b);
void clearOverride();
void showError();
void tick();
void blink(uint8_t r, uint8_t g, uint8_t b, uint8_t times, uint16_t intervalMs);

}
