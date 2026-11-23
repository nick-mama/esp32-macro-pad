#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

struct Button{
  int pin;
  bool lastReading;
  bool stableState;
  unsigned long lastDebounceTime;
};

bool updateButton(Button &button);

#endif