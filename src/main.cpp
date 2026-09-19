#include <Arduino.h>
#include <OtaUpdater.h>

#if __has_include("secrets.h")
#include "secrets.h"
#define WIFI_CREDENTIALS SECRET_SSID, SECRET_PASS
#else
#define WIFI_CREDENTIALS nullptr, nullptr
#endif

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Verze firmwaru: ");
  Serial.println(FW_VERSION);
  OtaUpdater::run(WIFI_CREDENTIALS);
  Serial.print("Verze firmwaru po kontrole aktualizace: ");
  Serial.println(FW_VERSION);
}

void loop() {
  yield();
}
