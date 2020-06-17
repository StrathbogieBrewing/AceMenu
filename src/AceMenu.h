#ifndef ACEMENU_H_
#define ACEMENU_H_

#include "Arduino.h"
#include "Display.h"
#include "Format.h"
#include "Keypad.h"

typedef int (*getValueFunction)();
typedef void (*setValueFunction)(int value);
typedef void (*formatFunction)(Display &dis, int value);

typedef struct {
  char const *itemName;
  getValueFunction getValue;
  setValueFunction setValue;
  formatFunction format;
  int minValue;
  int maxValue;
} menuItem;

class AceMenu {
public:
  AceMenu(menuItem items[], int itemCount, Display &dis, Keypad &key);
  void begin();
  void update();

private:
  menuItem *menuItems;
  int count;
  Display &display;
  Keypad &keypad;
  int index;
  int status;
  int value;
};

#endif /* ACEMENU_H_ */
