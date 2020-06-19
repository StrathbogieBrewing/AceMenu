#ifndef KEYPAD_H
#define KEYPAD_H

class Keypad {
public:
  virtual void begin(void) = 0;
  virtual char read(void) = 0;

  // keys used in navigation of menu system
  static const char NOKEY;
  static const char DECKEYSHORT;
  static const char DECKEYLONG;
  static const char INCKEYSHORT;
  static const char INCKEYLONG;
  static const char SELKEYSHORT;
  static const char SELKEYLONG;
};

#endif /* KEYPAD_H */
