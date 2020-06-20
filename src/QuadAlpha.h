#ifndef QUADALPHA_H
#define QUADALPHA_H

#include "Arduino.h"
#include "Display.h"

#define quad_kBufferSize 4

class QuadAlpha : public Display {
public:
  void begin();
  void write(char);

  void setBrightness(uint8_t b);
  void setBlinkRate(uint8_t b);

private:
  void writeDisplay();
  void clearDisplay();
  uint16_t displayBuffer[quad_kBufferSize];
  uint8_t displayIndex;
  uint8_t digit;
  static const uint16_t fontTable[] PROGMEM;
};

#endif /* QUADALPHA_H */
