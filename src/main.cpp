#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "IRController.h"

#define IR_RECEIVE_PIN 4

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println("Initialization complete.");
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type != decode_type_t::UNKNOWN && !results.repeat) {
      Serial.print("Decoded IR signal: ");
      Serial.println(resultToHexidecimal(&results));

      switch (results.value) {
        case IR_BTN_ON:
          Serial.println("Stisknuto POWER ON");
          break;
        case IR_BTN_OFF:
          Serial.println("Stisknuto POWER OFF");
          break;
      }
    }

    irrecv.resume();
  }
  
  yield();
}