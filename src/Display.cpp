// ANSI / VT100 escape codes
#include "Display.h"

const char Display::ESC = '\x1b';
const char Display::CRLF[] = "\r\n";
const char Display::HOME[] = "\x1b[H";
const char Display::CLRSCR[] = "\x1b[2J";
const char Display::FLASHON[] = "\x1b[5m";
const char Display::RESET[] = "\x1b[0m";
