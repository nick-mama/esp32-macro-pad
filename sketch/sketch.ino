#include "buttons.h"
#include "actions.h"
#include "profiles.h"
#include "protocol.h"

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

void setup() {

  Serial.begin(115200);

  // Configure buttons
  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);
  pinMode(button3.pin, INPUT_PULLUP);

  // Configure LED + load saved profile
  initProfiles();

  // Start USB keyboard
  initActions();

  initProtocol();
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

  updateProtocol();
}