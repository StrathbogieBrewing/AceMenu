#ifndef KEYPAD_H
#define KEYPAD_H

class Keypad {
public:
  virtual void begin(void) = 0;
  virtual char read(void) = 0;

  // keys used in navigation of menu system
  static const char NOKEY;
  static const char LEFTKEY;
  static const char RIGHTKEY;
  static const char SELECTKEY;
  static const char EDITKEY;
};

#endif /* KEYPAD_H */
