#include "Led.h"
#include "config.h"

namespace Led {

static const uint16_t PWM_MAX = 4095;

static uint8_t colorR = DEFAULT_R, colorG = DEFAULT_G, colorB = DEFAULT_B;
static uint8_t brightness = BRIGHTNESS_MAX;
static bool ledOn = true;

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
  write(colorR, colorG, colorB, brightness);
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

}
