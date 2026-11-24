#ifndef PROFILES_H
#define PROFILES_H

#include <Arduino.h>
#include "actions.h"

enum Profile{
  P_GENERAL,
  P_CODING,
  P_ARDUINO
};

void initProfiles();
void nextProfile();
void runButtonAction(int buttonNumber);
void setProfileColor();

Action getProfileAction(Profile profile, int buttonIndex);

bool setProfileAction(
  Profile profile,
  int buttonIndex,
  Action action
);

#endif