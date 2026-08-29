// #include <Arduino.h>
// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>

// #define SDA_PIN 4
// #define SCL_PIN 5

// #define RED_PIN   0
// #define GREEN_PIN 1
// #define BLUE_PIN  2

// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// void setRGB(uint16_t r, uint16_t g, uint16_t b) {
//   pwm.setPWM(RED_PIN, 0, r);
//   pwm.setPWM(GREEN_PIN, 0, g);
//   pwm.setPWM(BLUE_PIN, 0, b);
// }

// void setup() {
//   Serial.begin(115200);
//   Wire.begin(SDA_PIN, SCL_PIN);
//   pwm.begin();
//   pwm.setPWMFreq(1000);
//   setRGB(0, 0, 0);
// }

// void loop() {
//   Serial.println("Cervena");
//   setRGB(4095, 0, 0);
//   delay(1000);

//   Serial.println("Zelena");
//   setRGB(0, 4095, 0);
//   delay(1000);

//   Serial.println("Modra");
//   setRGB(0, 0, 4095);
//   delay(1000);
// }