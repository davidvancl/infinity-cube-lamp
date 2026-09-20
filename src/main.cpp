#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <OtaUpdater.h>
#include "IRController.h"
#include "config.h"

#if __has_include("secrets.h")
#include "secrets.h"
#define WIFI_CREDENTIALS SECRET_SSID, SECRET_PASS
#else
#define WIFI_CREDENTIALS nullptr, nullptr
#endif

static const uint16_t PWM_MAX = 4095;

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

uint8_t colorR = DEFAULT_R, colorG = DEFAULT_G, colorB = DEFAULT_B;
uint8_t brightness = BRIGHTNESS_MAX;
bool ledOn = true;

// Gama korekce jen na jas, poměr barevných kanálů zůstává beze změny
uint16_t toPwm(uint8_t value) {
  float b = powf(brightness / 100.0f, 2.2f);
  return (uint16_t)(value / 255.0f * b * PWM_MAX);
}

void applyOutput() {
  if (!ledOn) {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
    return;
  }
  analogWrite(RED_PIN, toPwm(colorR));
  analogWrite(GREEN_PIN, toPwm(colorG));
  analogWrite(BLUE_PIN, toPwm(colorB));
}

void handleCode(uint64_t code) {
  if (code == IR_BTN_ON) {
    ledOn = true;
    Serial.println("Turned on");
  } else if (code == IR_BTN_OFF) {
    ledOn = false;
    Serial.println("Turned off");
  } else if (code == IR_BTN_VOLUME_UP) {
    brightness = min<int>(brightness + BRIGHTNESS_STEP, BRIGHTNESS_MAX);
    Serial.printf("Brightness: %u %%\n", brightness);
  } else if (code == IR_BTN_VOLUME_DOWN) {
    brightness = max<int>(brightness - BRIGHTNESS_STEP, BRIGHTNESS_MIN);
    Serial.printf("Brightness: %u %%\n", brightness);
  } else {
    for (const ColorButton& button : COLOR_BUTTONS) {
      if (button.code == code) {
        colorR = button.r;
        colorG = button.g;
        colorB = button.b;
        ledOn = true;
        Serial.printf("Color: %s\n", button.name);
        applyOutput();
        return;
      }
    }
    Serial.println("Unknown code");
    return;
  }
  applyOutput();
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Výstupy nastavit hned na začátku, aby pásek během OTA nesvítil náhodně
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  analogWriteRange(PWM_MAX);
  analogWriteFreq(PWM_FREQUENCY);
  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);

  Serial.print("Firmware version: ");
  Serial.println(FW_VERSION);
  OtaUpdater::run(WIFI_CREDENTIALS);
  Serial.print("Firmware version after update check: ");
  Serial.println(FW_VERSION);

  applyOutput();

  irrecv.enableIRIn();
  Serial.println("Initialization complete.");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type != decode_type_t::UNKNOWN && !results.repeat) {
      Serial.print("Received IR signal: ");
      Serial.println(resultToHexidecimal(&results));
      handleCode(results.value);
    }
    irrecv.resume();
  }
  yield();
}