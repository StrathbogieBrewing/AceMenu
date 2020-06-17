#include "AceMenu.h"
#include "Terminal.h"

#define kTemperatureDelta 3

#define kEepromSetpoint ((uint16_t *)0)
#define kEepromHysteresis ((uint16_t *)2)

int temperature = 200;
int heater = 0;

// getter functions
int getTemperature() { return (temperature); }
int getHeater() { return heater; }
int getSetPoint() { return (int)eeprom_read_word(kEepromSetpoint); }
int getHysteresis() { return (int)eeprom_read_word(kEepromHysteresis); }

// setters functions, no setter for the temperature and heater read only
void setSetPoint(int v) { eeprom_write_word(kEepromSetpoint, (uint16_t)v); }
void setHysteresis(int v) { eeprom_write_word(kEepromHysteresis, (uint16_t)v); }

// menu contents
menuItem menuItems[] = {
    // name, getter, setter, format, min value , max value
    {"TEMP", getTemperature, NULL, Format::deci, 0, 0},
    {"SET", getSetPoint, setSetPoint, Format::deci, 100, 400},
    {"HYST", getHysteresis, setHysteresis, Format::deci, 5, 100},
    {"HEAT", getHeater, NULL, Format::boolean, 0, 1},
};
#define kMenuCount (sizeof(menuItems) / sizeof(menuItem))

Terminal terminal(Serial, 9600);

AceMenu menu = AceMenu(menuItems, kMenuCount, terminal, terminal);

void setup() {
  // initialise the menu
  menu.begin();
}

void loop() {
  // update the menu
  menu.update();

  // update temperature control
  if (heater == true) {
    if (temperature > getSetPoint() + getHysteresis())
      heater = false;
  } else {
    if (temperature < getSetPoint() - getHysteresis())
      heater = true;
  }

  // for demo make the temperature value change every 500 ms
  static int temperatureDelta = kTemperatureDelta;
  static long unsigned int waitUntil = 0;
  if (millis() > waitUntil) {
    waitUntil = millis() + 500L;
    // ramp up and down
    temperature += temperatureDelta;
    if (temperature > 250)
      temperatureDelta = -kTemperatureDelta;
    if (temperature < 150)
      temperatureDelta = kTemperatureDelta;
  }
}
