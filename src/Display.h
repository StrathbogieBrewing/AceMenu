#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
  virtual void begin(void) = 0;
  virtual void write(char) = 0;
  virtual void write(const char *str) {
    while (*str) {
      write(*str++);
    }
  }

  static const char NEWLINE;
  static const char CLRSCR;
  static const char FLASHON;
  static const char FLASHOFF;
};

#endif /* DISPLAY_H */
