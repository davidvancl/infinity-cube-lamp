#include <Arduino.h>
#include <OtaUpdater.h>
#include "IrRemote.h"
#include "Led.h"
#include "WifiCredentials.h"

void setup() {
  Serial.begin(115200);
  Serial.println();

  Led::begin();
  Led::showBooting();

  Serial.print("Firmware version: ");
  Serial.println(FW_VERSION);
  OtaUpdater::run(WIFI_CREDENTIALS);
  Serial.print("Firmware version after update check: ");
  Serial.println(FW_VERSION);

  Led::apply();
  IrRemote::begin();
  Serial.println("Initialization complete.");
}

void loop() {
  IrRemote::poll();
}
