#ifndef BUTTONS_H
#define BUTTONS_H

#include "Arduino.h"
#include "Keypad.h"

class Buttons : public Keypad {
public:
  Buttons(uint8_t leftPin, uint8_t centerPin, uint8_t rightPin);
  void begin();
  char read();

private:
  uint8_t pins[3];
  uint32_t lastReadTime;
  int16_t debounceTimer[3];
};

#endif
