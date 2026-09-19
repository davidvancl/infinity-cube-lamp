#pragma once

#include <Arduino.h>
#include "IRController.h"

// I2C (PWM driver)
#define SDA_PIN 4
#define SCL_PIN 5
#define PWM_DRIVER_ADDRESS 0x40
#define PWM_FREQUENCY 1000

// GPIO4 je obsazený I2C (SDA), IR přijímač proto sedí na GPIO14 (D5)
#define IR_RECEIVE_PIN 14

// Kanály PWM driveru pro LED pásek
#define RED_PIN   0
#define GREEN_PIN 1
#define BLUE_PIN  2

// Jas v procentech
#define BRIGHTNESS_STEP 10
#define BRIGHTNESS_MIN  10
#define BRIGHTNESS_MAX  100

// Výchozí barva po startu
#define DEFAULT_R 255
#define DEFAULT_G 255
#define DEFAULT_B 255

struct ColorButton {
  uint64_t code;
  uint8_t r, g, b;
  const char* name;
};

static const ColorButton COLOR_BUTTONS[] = {
  // 2. řada
  {IR_BTN_R,   255,   0,   0, "cervena"},
  {IR_BTN_G,     0, 255,   0, "zelena"},
  {IR_BTN_B,     0,   0, 255, "modra"},
  {IR_BTN_W,   255, 255, 255, "bila"},
  // 3. řada
  {IR_BTN_R_1, 255,  60,   0, "oranzovocervena"},
  {IR_BTN_G_1,   0, 255, 100, "svetle zelena"},
  {IR_BTN_B_1,  60,  60, 255, "svetle modra"},
  // 4. řada
  {IR_BTN_R_2, 255, 110,   0, "oranzova"},
  {IR_BTN_G_2,   0, 255, 180, "tyrkysova"},
  {IR_BTN_B_2, 140,   0, 255, "fialova"},
  // 5. řada
  {IR_BTN_R_3, 255, 170,   0, "tmave zluta"},
  {IR_BTN_G_3,   0, 220, 255, "azurova"},
  {IR_BTN_B_3, 200,   0, 255, "purpurova"},
  // 6. řada
  {IR_BTN_R_4, 255, 230,   0, "zluta"},
  {IR_BTN_G_4,   0, 140, 255, "svetle modra 2"},
  {IR_BTN_B_4, 255,   0, 150, "ruzova"},
};
