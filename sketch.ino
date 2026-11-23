#include <Preferences.h>
#include "buttons.h"
#include "actions.h"

// LED pins
#define RED_PIN 38
#define GREEN_PIN 39
#define BLUE_PIN 40

Preferences preferences;

// ---------
// Profiles
// ---------

enum Profile {
  P_GENERAL,
  P_CODING,
  P_ARDUINO
};

Profile currentProfile = P_GENERAL;

// Create our three buttons
Button button1 = {21, HIGH, HIGH, 0};
Button button2 = {13, HIGH, HIGH, 0};
Button button3 = {14, HIGH, HIGH, 0};


// -------------------
// Button 1 long press
// -------------------

unsigned long button1PressTime = 0;

bool button1WasPressed = false;
bool button1LongPress = false;

const unsigned long LONG_PRESS_TIME = 1500;

// -------------------
// Switch profile
// -------------------

void nextProfile(){

  if(currentProfile == P_GENERAL){
    currentProfile = P_CODING;
  }

  else if (currentProfile == P_CODING){
    currentProfile = P_ARDUINO;
  }

  else{
    currentProfile = P_GENERAL;
  }

  setProfileColor();

  // Save profile to flash
  preferences.putInt("profile", currentProfile);
}

// -------------------
// Run button action
// -------------------

void runButtonAction(int buttonNumber){
  switch(currentProfile){
    case P_GENERAL:
      if(buttonNumber == 1){
        generalButton1();
      }

      else if (buttonNumber == 2){
        generalButton2();
      }

      else if(buttonNumber == 3){
        generalButton3();
      }

      break;

    case P_CODING:
      if(buttonNumber == 1){
        codingButton1();
      }

      else if (buttonNumber == 2){
        codingButton2();
      }

      else if(buttonNumber == 3){
        codingButton3();
      }

      break;

    case P_ARDUINO:
      if(buttonNumber == 1){
        arduinoButton1();
      }

      else if (buttonNumber == 2){
        arduinoButton2();
      }

      else if(buttonNumber == 3){
        arduinoButton3();
      }

      break;
  }
}

// -------------------
// Profile Color
// -------------------
void setProfileColor(){
  switch(currentProfile){
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
      // RED
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
      break;
  }
}


void setup() {

  Serial.begin(115200);

  // Configure buttons
  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);
  pinMode(button3.pin, INPUT_PULLUP);

  // Configure LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Load saved profile
  preferences.begin("macropad", false);

  int savedProfile = preferences.getInt("profile", P_GENERAL);

  if(savedProfile >= P_GENERAL && savedProfile <= P_ARDUINO){
    currentProfile = (Profile)savedProfile;
  }
  else{
    currentProfile = P_GENERAL;
  }

  // Show restored profile
  setProfileColor();

  // Start USB keyboard
  initActions();
}

// -------------------
// Main loop
// -------------------

void loop() {

  // Button 1
  if(updateButton(button1)){
    // Button pressed
    if(button1.stableState == LOW){
      button1PressTime = millis();

      button1WasPressed = true;
      button1LongPress = false;
    }

    // Button released
    else{
      if(button1WasPressed && !button1LongPress){
        runButtonAction(1);
      }

      button1WasPressed = false;
    }
  }

  // Check if button 1 is being held
  if(button1WasPressed && !button1LongPress){
    if (millis() - button1PressTime >= LONG_PRESS_TIME){
      button1LongPress = true;

      nextProfile();
    }
  }
  
  // Button 2
  if(updateButton(button2)){
    if(button2.stableState == LOW){
      runButtonAction(2);
    }
  }

  // Button 3
  if(updateButton(button3)){
    if(button3.stableState == LOW){
      runButtonAction(3);
    }
  }
}