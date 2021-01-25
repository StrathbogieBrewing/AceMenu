#include "Buttons.h"
#include <Arduino.h>

#define kShortPeriod 50
#define kLongPeriod 500
#define kButtonCount 3

enum { kNoPress = 0, kShortPress, kLongPress };

Buttons::Buttons(uint8_t leftPin, uint8_t centerPin, uint8_t rightPin)
    : pins{leftPin, centerPin, rightPin} {}

void Buttons::begin(void) {
  Serial.println("Buttons Begin");
  lastReadTime = millis();
  for (int i = 0; i < kButtonCount; i++) {
    debounceTimer[i] = 0;
    pinMode(pins[i], INPUT_PULLUP);
  }
}

char Buttons::read(void) {
  unsigned long time = millis();
  unsigned long delta = time - lastReadTime;
  lastReadTime = time;
  char press = kNoPress;

  int i;
  for (i = 0; i < kButtonCount; i++) {
    if (digitalRead(pins[i]) == LOW) {
      if (debounceTimer[i] < 0)
        debounceTimer[i] -= delta;
      else
        debounceTimer[i] += delta;
      if ((debounceTimer[i] > kLongPeriod) ||
          (debounceTimer[i] < -kLongPeriod)) {
        debounceTimer[i] = -1;
        press = kLongPress;
        break;
      }
    } else {
      if (debounceTimer[i] > kShortPeriod) {
        debounceTimer[i] = 0;
        press = kShortPress;
        break;
      } else {
        debounceTimer[i] = 0;
      }
    }
  }

  if (press == kLongPress) {
    if (i == 0)
      return DECKEYLONG;
    if (i == 1)
      return SELKEYLONG;
    if (i == 2)
      return INCKEYLONG;
  }
  if (press == kShortPress) {
    if (i == 0)
      return DECKEYSHORT;
    if (i == 1)
      return SELKEYSHORT;
    if (i == 2)
      return INCKEYSHORT;
  }

  return NOKEY;
}
