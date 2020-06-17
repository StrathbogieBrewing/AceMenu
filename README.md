# AceMenu
## Arduino Super Simple Menu
### Features
Simple interface to any display and keypad

Supports simple fixed point integer values

### Background
Many projects require some form of user interface which provides a means of viewing status information and adjusting settings.

As an example, a simple thermostat for a fermenter could have a 4 menu items - Temperature, Set Point, Hysteresis and Heater State.
Some menu items are read only, like the Temperature and Heater State.
Some menu items can be changed by the user, like the Set Point and the Hysteresis.

Read only menu items require a method of getting the value to display and a way to format the value for the user.
Changable values also require a method of setting the value and a method to validate that the new value is within an acceptable range.

AceMenu uses functions to get, set and format the data. Constant values are used for the name of the menu item and for maximum and minimum values.

### Hardware
The menu requires a keypad for user input and a display to show the information.

Displays can have various characteristics:
Number of lines can be single or multiple
Number of characters on a line
Format of characters can be 7 segment, alphanumeric or dot matrix
Electrical interface can be serial, I2C, SPI

Similarly keypads can have from a few buttons to a full keyboard with a variety of electrical interfaces.

The AceMenu reads characters from the keypad and writes characters to the display. ANSI terminal codes are used to control the display in a consistent and well defined way.
