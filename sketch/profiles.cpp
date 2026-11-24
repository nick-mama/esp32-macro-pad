#include <Arduino.h>
#include <Preferences.h>

#include "profiles.h"
#include "actions.h"

// RGB LED pins
#define RED_PIN 38
#define GREEN_PIN 39
#define BLUE_PIN 40

Preferences preferences;

// -------------------
// Mapping table for buttons
// -------------------

Action profileMappings[3][3] = {
  // General
  {
    ACTION_PLAY_PAUSE,
    ACTION_SCREENSHOT,
    ACTION_LOCK
  },

  // Coding
  {
    ACTION_TERMINAL,
    ACTION_TOGGLE_COMMENT,
    ACTION_FIND_FILES
  },

  // Arduino
  {
    ACTION_VERIFY,
    ACTION_UPLOAD,
    ACTION_SERIAL_MONITOR
  }
};

Profile currentProfile = P_GENERAL;

// -------------------
// Initialize profiles
// -------------------

void initProfiles(){
  // Configure LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Open NVS
  preferences.begin("macropad", false);

  // Load saved profile
  int savedProfile = preferences.getInt("profile", P_GENERAL);

  if(savedProfile >= P_GENERAL && savedProfile <= P_ARDUINO){
    currentProfile = (Profile)savedProfile;
  }
  else{
    currentProfile = P_GENERAL;
  }
  setProfileColor();
}

// --------------------
// Switch profile
// --------------------

void nextProfile() {

  if (currentProfile == P_GENERAL) {
    currentProfile = P_CODING;
  }
  else if (currentProfile == P_CODING) {
    currentProfile = P_ARDUINO;
  }
  else {
    currentProfile = P_GENERAL;
  }

  setProfileColor();

  // Save current profile to flash
  preferences.putInt("profile", currentProfile);
}


// --------------------
// Run button action
// --------------------

void runButtonAction(int buttonNumber) {
  // Convert buttons 1-3 into array indexes 0-2
  int buttonIndex = buttonNumber - 1;

  if(buttonIndex < 0 || buttonIndex > 2){
    return;
  }

  Action action = profileMappings[currentProfile][buttonIndex];

  runAction(action);
}


// --------------------
// RGB profile indicator
// --------------------

void setProfileColor() {

  switch (currentProfile) {

    case P_GENERAL:
      // Green
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
      break;

    case P_CODING:
      // Blue
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
      break;

    case P_ARDUINO:
      // Red
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
      break;
  }
}

Action getProfileAction(Profile profile, int buttonIndex){
  if(profile < P_GENERAL || profile > P_ARDUINO){
    return ACTION_NONE;
  }

  if(buttonIndex < 0 || buttonIndex > 2){
    return ACTION_NONE;
  }

  return profileMappings[profile][buttonIndex];
}

bool setProfileAction(Profile profile, int buttonIndex, Action action) {
  // Make sure profile is valid
  if (profile < P_GENERAL || profile > P_ARDUINO) {
    return false;
  }

  // Make sure button index is valid
  if (buttonIndex < 0 || buttonIndex > 2) {
    return false;
  }

  // Make sure action is valid
  if (action < ACTION_PLAY_PAUSE || action > ACTION_NONE) {
    return false;
  }

  profileMappings[profile][buttonIndex] = action;

  return true;
}