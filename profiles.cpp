#include <Arduino.h>
#include <Preferences.h>

#include "profiles.h"
#include "actions.h"

// RGB LED pins
#define RED_PIN 38
#define GREEN_PIN 39
#define BLUE_PIN 40

Preferences preferences;

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

  switch (currentProfile) {

    case P_GENERAL:

      if (buttonNumber == 1) {
        generalButton1();
      }
      else if (buttonNumber == 2) {
        generalButton2();
      }
      else if (buttonNumber == 3) {
        generalButton3();
      }

      break;


    case P_CODING:

      if (buttonNumber == 1) {
        codingButton1();
      }
      else if (buttonNumber == 2) {
        codingButton2();
      }
      else if (buttonNumber == 3) {
        codingButton3();
      }

      break;


    case P_ARDUINO:

      if (buttonNumber == 1) {
        arduinoButton1();
      }
      else if (buttonNumber == 2) {
        arduinoButton2();
      }
      else if (buttonNumber == 3) {
        arduinoButton3();
      }

      break;
  }
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