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

  static const char ESC;
  static const char CRLF[];
  static const char HOME[];
  static const char CLRSCR[];
  static const char FLASHON[];
  static const char RESET[];
};

#endif /* DISPLAY_H */
