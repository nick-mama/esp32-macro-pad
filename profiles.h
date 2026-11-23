#ifndef PROFILES_H
#define PROFILES_H

#include <Arduino.h>

enum Profile{
  P_GENERAL,
  P_CODING,
  P_ARDUINO
};

void initProfiles();
void nextProfile();
void runButtonAction(int buttonNumber);
void setProfileColor();

#endif