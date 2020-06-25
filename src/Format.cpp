#include "Format.h"

enum {
  // Milli,       // make fixed point with 3 decimal places
  Centi,     // make fixed point with 2 decimal places
  Deci,      // make fixed point with 1 decimal places
  Unit,      // dispplay at least one digit
  TwoDigits, // dispplay at least two digit
  Time,      // dispplay as a time
  Bool,      // dispplay as on / off
};

void Format::write(Display &disp, int val, int format) {
  unsigned char digit;
  uint8_t enable_digits = 0;
  // do sign
  if (val < 0) {
    val = -val;
    disp.write('-');
  } else {
    // if ((format == Unit) || (format == Deci) || (format == Centi))
    //   disp.write(' ');
  }
  // do 10000's
  digit = '0';
  while (val > 9999) {
    val -= 10000;
    digit++;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    disp.write(digit);
    enable_digits = 1;
  }
  // do 1000's
  digit = '0';
  while (val > 999) {
    val -= 1000;
    digit++;
  }
  if ((digit != '0') || (enable_digits != 0)) {
    disp.write(digit);
    enable_digits = 1;
  }
  // do 100's
  digit = '0';
  while (val > 99) {
    val -= 100;
    digit++;
  }
  // if (format == Milli) {
  //   if (enable_digits == 0)
  //     disp.write('0');
  //   disp.write('.');
  //   enable_digits = 1;
  // }
  if ((digit != '0') || (enable_digits != 0)) {
    disp.write(digit);
    enable_digits = 1;
  }
  // do 10's
  digit = '0';
  while (val > 9) {
    val -= 10;
    digit++;
  }
  if (format == Centi) {
    if (enable_digits == 0)
      disp.write('0');
    disp.write('.');
    enable_digits = 1;
  }
  if ((digit != '0') || (enable_digits != 0) || (format == TwoDigits)) {
    disp.write(digit);
    enable_digits = 1;
  }
  // do 1's
  digit = '0' + val;
  if (format == Deci) {
    if (enable_digits == 0)
      disp.write('0');
    disp.write('.');
    enable_digits = 1;
  }
  if ((digit != '0') || (enable_digits != 0) || (format == Unit)) {
    disp.write(digit);
    enable_digits = 1;
  }
}

void Format::boolean(Display &disp, int val) {
  if (val)
    disp.write("ON");
  else
    disp.write("OFF");
}

void Format::unit(Display &disp, int val) { write(disp, val, Unit); }

void Format::deciTemp(Display &disp, int val) {
  if ((val < 999) && (val > -99)) {
    if ((val < 100) && (val >= 0))
      disp.write(' ');
    write(disp, val, Deci);
  } else
    write(disp, val / 10, Unit);
  disp.write('~');
}

void Format::deci(Display &disp, int val) { write(disp, val, Deci); }

void Format::centi(Display &disp, int val) { write(disp, val, Centi); }

void Format::twoDigit(Display &disp, int val) { write(disp, val, TwoDigits); }

void Format::time(Display &disp, int val) {
  int hours = 0;
  while (val >= 60) {
    ++hours;
    val -= 60;
  }
  twoDigit(disp, hours);
  disp.write('.');
  twoDigit(disp, val);
}
