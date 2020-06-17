#ifndef TERMINAL_H
#define TERMINAL_H

#include "Arduino.h"
#include "Display.h"
#include "Keypad.h"

class Terminal : public Display, public Keypad {
public:
	Terminal(HardwareSerial &serial, unsigned long baud = 9600);
  void begin();
  void write(char);
  char read();
private:
	HardwareSerial &serialPort;
  unsigned long serialBaud;
};

#endif /* TERMINAL_H */
