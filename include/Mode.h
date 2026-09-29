#pragma once

namespace Mode {

enum Type {
  MANUAL,
  INDICATOR,
};

void begin();
void poll();
void toggle();
void showActive();
Type current();

}
