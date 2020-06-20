#include "AceMenu.h"

#define kFastStep 5

// menu states
enum { kInitialise, kShowLabel, kShowValue, kShowSetting };

AceMenu::AceMenu(menuItem items[], int itemCount, Display &dis, Keypad &key)
    :  menuItems{items}, count{itemCount}, display{dis}, keypad{key} {}

void AceMenu::begin() {
  display.begin();
  keypad.begin();
  status = kInitialise;
  update();
}

void AceMenu::update() {
  char keyIn = keypad.read();
  bool displayChanged = false;
  // if key pressed update state and menu value
  if (status == kShowValue) {
    int newValue = menuItems[index].getValue();
    if (value != newValue) {
      displayChanged = true;
    }
    value = newValue;
    if ((keyIn == keypad.SELKEYLONG) && menuItems[index].setValue) {
      status = kShowSetting;
      displayChanged = true;
      if (value > menuItems[index].maxValue) {
        value = menuItems[index].maxValue;
      }
      if (value < menuItems[index].minValue) {
        value = menuItems[index].minValue;
      }
    } else if (keyIn != keypad.NOKEY) {
      status = kShowLabel;
      displayChanged = true;
    }
  } else if (status == kShowSetting) {
    if ((keyIn == keypad.SELKEYSHORT) || (keyIn == keypad.SELKEYLONG)) {
      menuItems[index].setValue(value);
      status = kShowValue;
      displayChanged = true;
    }

    if (keyIn == keypad.DECKEYSHORT) {
      if (value > menuItems[index].minValue) {
        value--;
      }
      displayChanged = true;
    }
    if (keyIn == keypad.DECKEYLONG) {
      if (value > menuItems[index].minValue + kFastStep) {
        value -= kFastStep;
      }
      displayChanged = true;
    }

    if (keyIn == keypad.INCKEYSHORT) {
      if (value < menuItems[index].maxValue) {
        value++;
      }
      displayChanged = true;
    }
    if (keyIn == keypad.INCKEYLONG) {
      if (value < menuItems[index].maxValue - kFastStep) {
        value += kFastStep;
      }
      displayChanged = true;
    }

    // range check
    if (value > menuItems[index].maxValue) {
      value = menuItems[index].maxValue;
    }
    if (value < menuItems[index].minValue) {
      value = menuItems[index].minValue;
    }

  } else {
    if ((status != kShowLabel) || (keyIn != keypad.NOKEY)) {
      displayChanged = true;
    }
    status = kShowLabel;
    if (keyIn == keypad.INCKEYSHORT) {
      if (index < count - 1) {
        index++;
      } else {
        index = 0;
      }
    }
    if (keyIn == keypad.DECKEYSHORT) {
      if (index > 0) {
        index--;
      } else {
        index = count - 1;
      }
    }
    if ((keyIn == keypad.SELKEYSHORT) || (keyIn == keypad.SELKEYLONG)) {
      status = kShowValue;
      value = menuItems[index].getValue();
      displayChanged = true;
    }
  }

  // update display
  if (displayChanged) {
    display.write(display.CLRSCR);
    display.write(display.FLASHOFF);
    if (status == kShowSetting)
      display.write(display.FLASHON);
    if (status == kShowLabel)
      display.write(menuItems[index].itemName);
    else
      menuItems[index].format(display, value);
    display.write(display.NEWLINE);
  }
}
