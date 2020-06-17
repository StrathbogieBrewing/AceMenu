#include "AceMenu.h"

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
    if ((keyIn == keypad.EDITKEY) && menuItems[index].setValue) {
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
    if ((keyIn == keypad.SELECTKEY) || (keyIn == keypad.EDITKEY)) {
      menuItems[index].setValue(value);
      status = kShowValue;
      displayChanged = true;
    }
    if (keyIn == keypad.LEFTKEY) {
      if (value > menuItems[index].minValue) {
        value--;
      } else {
        value = menuItems[index].minValue;
      }
      displayChanged = true;
    }
    if (keyIn == keypad.RIGHTKEY) {
      if (value < menuItems[index].maxValue) {
        value++;
      } else {
        value = menuItems[index].maxValue;
      }
      displayChanged = true;
    }
  } else {
    if ((status != kShowLabel) || (keyIn != keypad.NOKEY)) {
      displayChanged = true;
    }
    status = kShowLabel;
    if (keyIn == keypad.RIGHTKEY) {
      if (index < count - 1) {
        index++;
      } else {
        index = 0;
      }
    }
    if (keyIn == keypad.LEFTKEY) {
      if (index > 0) {
        index--;
      } else {
        index = count - 1;
      }
    }
    if ((keyIn == keypad.SELECTKEY) || (keyIn == keypad.EDITKEY)) {
      status = kShowValue;
      value = menuItems[index].getValue();
      displayChanged = true;
    }
  }

  // update display
  if (displayChanged) {
    display.write(display.CLRSCR);
    display.write(display.HOME);
    display.write(display.RESET);
    if (status == kShowSetting)
      display.write(display.FLASHON);
    if (status == kShowLabel)
      display.write(menuItems[index].itemName);
    else
      menuItems[index].format(display, value);
    display.write(display.CRLF);
  }
}
