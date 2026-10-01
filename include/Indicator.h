#pragma once

#include <Arduino.h>

namespace Indicator {

enum Result {
  OK,
  SERVER_ERROR,
  FAILED,
};

Result fetchColor(uint8_t& r, uint8_t& g, uint8_t& b);

}
