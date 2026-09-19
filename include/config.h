#pragma once

#include <Arduino.h>
#include "IRController.h"

// I2C (PWM driver)
#define SDA_PIN 4
#define SCL_PIN 5
#define PWM_DRIVER_ADDRESS 0x40
#define PWM_FREQUENCY 1000

// GPIO4 is used by I2C (SDA), so the IR receiver is on GPIO14 (D5)
#define IR_RECEIVE_PIN 14

// PWM driver channels for the LED strip
#define RED_PIN   0
#define GREEN_PIN 1
#define BLUE_PIN  2

// Brightness in percent
#define BRIGHTNESS_STEP 10
#define BRIGHTNESS_MIN  10
#define BRIGHTNESS_MAX  100

// Default color after startup
#define DEFAULT_R 255
#define DEFAULT_G 255
#define DEFAULT_B 255

struct ColorButton {
  uint64_t code;
  uint8_t r, g, b;
  const char* name;
};

static const ColorButton COLOR_BUTTONS[] = {
  // row 2
  {IR_BTN_R,   255,   0,   0, "red"},
  {IR_BTN_G,     0, 255,   0, "green"},
  {IR_BTN_B,     0,   0, 255, "blue"},
  {IR_BTN_W,   255, 255, 255, "white"},
  // row 3
  {IR_BTN_R_1, 255,  60,   0, "orange-red"},
  {IR_BTN_G_1,   0, 255, 100, "light green"},
  {IR_BTN_B_1,  60,  60, 255, "light blue"},
  // row 4
  {IR_BTN_R_2, 255, 110,   0, "orange"},
  {IR_BTN_G_2,   0, 255, 180, "turquoise"},
  {IR_BTN_B_2, 140,   0, 255, "violet"},
  // row 5
  {IR_BTN_R_3, 255, 170,   0, "dark yellow"},
  {IR_BTN_G_3,   0, 220, 255, "azure"},
  {IR_BTN_B_3, 200,   0, 255, "purple"},
  // row 6
  {IR_BTN_R_4, 255, 230,   0, "yellow"},
  {IR_BTN_G_4,   0, 140, 255, "sky blue"},
  {IR_BTN_B_4, 255,   0, 150, "pink"},
};
