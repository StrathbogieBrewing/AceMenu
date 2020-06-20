#include "Terminal.h"

Terminal::Terminal(HardwareSerial &serial = Serial, unsigned long baud)
    : serialPort{serial}, serialBaud{baud} {}

void Terminal::begin() { serialPort.begin(serialBaud); }

void Terminal::write(char byte) {
  if (byte == NEWLINE) {
    serialPort.write("\r\n");
  } else if (byte == FLASHON) {
    serialPort.write("\x1b[5m");
  } else if (byte == FLASHOFF) {
    serialPort.write("\x1b[0m");
  } else if (byte == CLRSCR) {
    serialPort.write("\x1b[2J");
    serialPort.write("\x1b[H");
  } else {
    serialPort.write(byte);
  }
}

char Terminal::read(void) {
  char key = NOKEY;
  if (serialPort.available() > 0) {
    key = serialPort.read();
  }
  return key;
}
