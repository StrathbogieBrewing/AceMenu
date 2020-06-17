#include "Terminal.h"

Terminal::Terminal(HardwareSerial &serial = Serial, unsigned long baud)
    : serialPort{serial}, serialBaud{baud} {}

void Terminal::begin() { serialPort.begin(serialBaud); }

void Terminal::write(char byte) { serialPort.write(byte); }

char Terminal::read(void) {
  char key = NOKEY;
  if (serialPort.available() > 0) {
    key = serialPort.read();
  }
  return key;
}
