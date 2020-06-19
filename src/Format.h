#ifndef FORMAT_H
#define FORMAT_H

#include "Arduino.h"

#include "Display.h"

class Format {
public:
  static void time(Display &disp, int val);
  static void boolean(Display &disp, int val);
  static void unit(Display &disp, int val);
  static void deci(Display &disp, int val);
  static void centi(Display &disp, int val);
  static void twoDigit(Display &disp, int val);

  static void deciTemp(Display &disp, int val);

private:
  static void write(Display &disp, int val, int format);
};

#endif /* FORMAT_H */
