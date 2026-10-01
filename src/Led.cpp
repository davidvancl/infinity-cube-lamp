#include "Led.h"
#include "config.h"

namespace Led {

static const uint16_t PWM_MAX = 4095;

static uint8_t colorR = DEFAULT_R, colorG = DEFAULT_G, colorB = DEFAULT_B;
static uint8_t brightness = BRIGHTNESS_MAX;
static bool ledOn = true;

static bool overrideActive = false;
static uint8_t overrideR = 0, overrideG = 0, overrideB = 0;

static bool errorBlink = false;
static bool errorPhaseOn = false;
static uint32_t errorPhaseStart = 0;
static uint8_t errorR = ERROR_BLINK_R, errorG = ERROR_BLINK_G, errorB = ERROR_BLINK_B;
static uint8_t errorLevel = BRIGHTNESS_MAX;

static uint16_t toPwm(uint8_t value, uint8_t level) {
  float b = powf(level / 100.0f, 2.2f);
  return (uint16_t)(value / 255.0f * b * PWM_MAX);
}

static void write(uint8_t r, uint8_t g, uint8_t b, uint8_t level) {
  analogWrite(RED_PIN, toPwm(r, level));
  analogWrite(GREEN_PIN, toPwm(g, level));
  analogWrite(BLUE_PIN, toPwm(b, level));
}

void begin() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  analogWriteRange(PWM_MAX);
  analogWriteFreq(PWM_FREQUENCY);
  write(0, 0, 0, 0);
}

void apply() {
  if (!ledOn) {
    write(0, 0, 0, 0);
    return;
  }
  if (errorBlink) {
    if (errorPhaseOn) {
      write(errorR, errorG, errorB, errorLevel);
    } else {
      write(0, 0, 0, 0);
    }
  } else if (overrideActive) {
    write(overrideR, overrideG, overrideB, brightness);
  } else {
    write(colorR, colorG, colorB, brightness);
  }
}

void showBooting() {
  write(BOOT_R, BOOT_G, BOOT_B, BRIGHTNESS_MAX);
}

void turnOn() {
  ledOn = true;
  apply();
}

void turnOff() {
  ledOn = false;
  apply();
}

void brighter() {
  brightness = min<int>(brightness + BRIGHTNESS_STEP, BRIGHTNESS_MAX);
  Serial.printf("Brightness: %u %%\n", brightness);
  apply();
}

void dimmer() {
  brightness = max<int>(brightness - BRIGHTNESS_STEP, BRIGHTNESS_MIN);
  Serial.printf("Brightness: %u %%\n", brightness);
  apply();
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  colorR = r;
  colorG = g;
  colorB = b;
  ledOn = true;
  apply();
}

void setOverrideColor(uint8_t r, uint8_t g, uint8_t b) {
  overrideR = r;
  overrideG = g;
  overrideB = b;
  overrideActive = true;
  errorBlink = false;
  apply();
}

void clearOverride() {
  overrideActive = false;
  errorBlink = false;
  apply();
}

static void startErrorBlink(uint8_t r, uint8_t g, uint8_t b, uint8_t level) {
  bool same = errorBlink && errorR == r && errorG == g && errorB == b && errorLevel == level;
  if (same) return;
  errorR = r;
  errorG = g;
  errorB = b;
  errorLevel = level;
  errorBlink = true;
  errorPhaseOn = true;
  errorPhaseStart = millis();
  apply();
}

void showError() {
  startErrorBlink(ERROR_BLINK_R, ERROR_BLINK_G, ERROR_BLINK_B, brightness);
}

void showServerError() {
  startErrorBlink(SERVER_ERROR_BLINK_R, SERVER_ERROR_BLINK_G, SERVER_ERROR_BLINK_B,
                  min<uint8_t>(brightness, SERVER_ERROR_BRIGHTNESS));
}

void tick() {
  if (!errorBlink || millis() - errorPhaseStart < ERROR_BLINK_MS) return;
  errorPhaseOn = !errorPhaseOn;
  errorPhaseStart = millis();
  apply();
}

void blink(uint8_t r, uint8_t g, uint8_t b, uint8_t times, uint16_t intervalMs) {
  for (uint8_t i = 0; i < times; i++) {
    write(0, 0, 0, 0);
    delay(intervalMs);
    write(r, g, b, BRIGHTNESS_MAX);
    delay(intervalMs);
  }
  write(0, 0, 0, 0);
  delay(intervalMs);
  apply();
}

}
