#include <Arduino.h>
#include "Mode.h"
#include "Indicator.h"
#include "Led.h"
#include "config.h"

namespace Mode {

static Type mode = MANUAL;
static uint32_t lastPoll = 0;

static void enterManual() {
  mode = MANUAL;
  Led::clearOverride();
  Serial.println("Mode 1: manual");
}

static bool enterIndicator() {
  uint8_t r, g, b;
  lastPoll = millis();
  if (!Indicator::fetchColor(r, g, b)) return false;

  mode = INDICATOR;
  Led::setOverrideColor(r, g, b);
  Serial.println("Mode 2: indicator");
  return true;
}

void begin() {
  if (!enterIndicator()) enterManual();
}

void poll() {
  if (mode != INDICATOR || millis() - lastPoll < INDICATOR_POLL_INTERVAL_MS) return;
  lastPoll = millis();

  uint8_t r, g, b;
  if (Indicator::fetchColor(r, g, b)) {
    Led::setOverrideColor(r, g, b);
  } else {
    Led::showError();
  }
}

void toggle() {
  if (mode == INDICATOR) {
    enterManual();
  } else if (!enterIndicator()) {
    Serial.println("Indicator unavailable, staying in manual mode");
    showActive();
  }
}

void showActive() {
  if (mode == INDICATOR) {
    Led::blink(MODE_INDICATOR_BLINK_R, MODE_INDICATOR_BLINK_G, MODE_INDICATOR_BLINK_B,
               MODE_BLINK_COUNT, MODE_BLINK_MS);
  } else {
    Led::blink(MODE_MANUAL_BLINK_R, MODE_MANUAL_BLINK_G, MODE_MANUAL_BLINK_B,
               MODE_BLINK_COUNT, MODE_BLINK_MS);
  }
}

Type current() {
  return mode;
}

}
