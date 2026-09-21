#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "IrRemote.h"
#include "IRController.h"
#include "Led.h"
#include "config.h"

namespace IrRemote {

static IRrecv irrecv(IR_RECEIVE_PIN);
static decode_results results;

static void handleCode(uint64_t code) {
  if (code == IR_BTN_ON) {
    Serial.println("Turned on");
    Led::turnOn();
  } else if (code == IR_BTN_OFF) {
    Serial.println("Turned off");
    Led::turnOff();
  } else if (code == IR_BTN_VOLUME_UP) {
    Led::brighter();
  } else if (code == IR_BTN_VOLUME_DOWN) {
    Led::dimmer();
  } else {
    for (const ColorButton& button : COLOR_BUTTONS) {
      if (button.code == code) {
        Serial.printf("Color: %s\n", button.name);
        Led::setColor(button.r, button.g, button.b);
        return;
      }
    }
    Serial.println("Unknown code");
  }
}

void begin() {
  irrecv.enableIRIn();
}

void poll() {
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

}
