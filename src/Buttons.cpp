#include "Buttons.h"
#include <Arduino.h>

#define kShortPeriod 100
#define kLongPeriod 500

Buttons::Buttons(uint8_t leftPin, uint8_t centerPin, uint8_t rightPin)
    : pins{leftPin, centerPin, rightPin} {}

void Buttons::begin(void) {
  unsigned long time = millis();
  for (int i = 0; i < 3; i++) {
    pinMode(pins[i], INPUT_PULLUP);
    debounceTime[i] = time + kShortPeriod;
    state[i] = HIGH;
  }
}

char Buttons::read(void) {
  unsigned long time = millis();
  unsigned long delta = 0;
  int i;
  for (i = 0; i < 3; i++) {
    if (debounceTime[i] < time) {
      delta = time - debounceTime[i];
      if (digitalRead(pins[i]) != state[i]) {
        state[i] = !state[i];
        debounceTime[i] = time + kShortPeriod;
        break;
      }
    }
  }

  if ((delta != 0) && (state[i] != 0)) {
    if (delta > kLongPeriod) {
      if (i == 0)
        return LEFTKEY;
      if (i == 1)
        return EDITKEY;
      if (i == 2)
        return RIGHTKEY;
    } else {
      if (i == 0)
        return LEFTKEY;
      if (i == 1)
        return SELECTKEY;
      if (i == 2)
        return RIGHTKEY;
    }
  }

  return NOKEY;
}
