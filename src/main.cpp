#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <OtaUpdater.h>

#if __has_include("secrets.h")
#include "secrets.h"
#define WIFI_CREDENTIALS SECRET_SSID, SECRET_PASS
#else
#define WIFI_CREDENTIALS nullptr, nullptr
#endif

#define SDA_PIN 4
#define SCL_PIN 5

#define MOTOR   0

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(115200);
  OtaUpdater::run(WIFI_CREDENTIALS);
  Wire.begin(SDA_PIN, SCL_PIN);
  pwm.begin();
  pwm.setPWMFreq(100);

  pwm.setPWM(MOTOR, 0, 1000); // Výchozí hodnota
  Serial.println("Zadej PWM hodnotu (0 - 4095):");
}

void loop() {
  // Ponechá prostor pro vnitřní procesy ESP (WiFi, watchdog...)
  yield();

  if (Serial.available() > 0) {
    // Přečte celý řádek až po entru (neblokuje zbytečně dlouho)
    String input = Serial.readStringUntil('\n');
    input.trim(); // Odstraní mezery, \r a další bílé znaky

    if (input.length() > 0) {
      int pwmValue = input.toInt(); // Převede text na číslo

      // Ověření platnosti vstupu (0 může být hodnota 0 nebo chyba převodu)
      if (pwmValue >= 0 && pwmValue <= 4095) {
        pwm.setPWM(MOTOR, 0, pwmValue);

        Serial.print("MOTOR PWM nastaveno na: ");
        Serial.println(pwmValue);
      } else {
        Serial.println("Chyba: Zadavej pouze hodnoty v rozsahu 0 az 4095!");
      }
    }
  }
}