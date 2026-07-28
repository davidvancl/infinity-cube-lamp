#pragma once

#include <Arduino.h>

// 1. row
const uint64_t IR_BTN_VOLUME_UP = 0xF700FF;
const uint64_t IR_BTN_VOLUME_DOWN = 0xF7807F;
const uint64_t IR_BTN_OFF = 0xF740BF;
const uint64_t IR_BTN_ON = 0xF7C03F;

// 2. row
const uint64_t IR_BTN_R = 0xF720DF;
const uint64_t IR_BTN_G = 0xF7A05F;
const uint64_t IR_BTN_B = 0xF7609F;
const uint64_t IR_BTN_W = 0xF7E01F;

// 3. row
const uint64_t IR_BTN_R_1 = 0xF710EF;
const uint64_t IR_BTN_G_1 = 0xF7906F;
const uint64_t IR_BTN_B_1 = 0xF750AF;
const uint64_t IR_BTN_FLASH = 0xF7D02F;

// 4. row
const uint64_t IR_BTN_R_2 = 0xF730CF;
const uint64_t IR_BTN_G_2 = 0xF7B04F;
const uint64_t IR_BTN_B_2 = 0xF7708F;
const uint64_t IR_BTN_STROBE = 0xF7F00F;

// 5. row
const uint64_t IR_BTN_R_3 = 0xF708F7;
const uint64_t IR_BTN_G_3 = 0xF78877;
const uint64_t IR_BTN_B_3 = 0xF748B7;
const uint64_t IR_BTN_FADE = 0xF7C837;

// 6. row
const uint64_t IR_BTN_R_4 = 0xF728D7;
const uint64_t IR_BTN_G_4 = 0xF7A857;
const uint64_t IR_BTN_B_4 = 0xF76897;
const uint64_t IR_BTN_SMOOTH = 0xF7E817;