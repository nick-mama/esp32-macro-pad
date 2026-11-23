#include "USB.h"
#include "USBHIDKeyboard.h"
#include "USBHIDConsumerControl.h"

// LED pins
#define RED_PIN 38
#define GREEN_PIN 39
#define BLUE_PIN 40

USBHIDKeyboard Keyboard;
USBHIDConsumerControl ConsumerControl;

// ---------
// Profiles
// ---------

enum Profile {
  P_GENERAL,
  P_CODING,
  P_ARDUINO
};

Profile currentProfile = P_GENERAL;

// -------------------
// Button structure
// -------------------

struct Button {
  int pin;
  bool lastReading;
  bool stableState;
  unsigned long lastDebounceTime;
};

// Create our three buttons
Button button1 = {21, HIGH, HIGH, 0};
Button button2 = {13, HIGH, HIGH, 0};
Button button3 = {14, HIGH, HIGH, 0};

const unsigned long DEBOUNCE_DELAY = 50;

// -------------------
// Button 1 long press
// -------------------

unsigned long button1PressTime = 0;

bool button1WasPressed = false;
bool button1LongPress = false;

const unsigned long LONG_PRESS_TIME = 1500;

// ------------------
// Debounce function
// ------------------
bool updateButton(Button &button) {

  bool currentReading = digitalRead(button.pin);

  if (currentReading != button.lastReading) {
    button.lastDebounceTime = millis();
  }

  if ((millis() - button.lastDebounceTime) > DEBOUNCE_DELAY) {

    if (currentReading != button.stableState) {
      button.stableState = currentReading;
      button.lastReading = currentReading;

      return true;
    }
  }

  button.lastReading = currentReading;

  return false;
}

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
}

// ------------------------------
// General profile button actions
// ------------------------------

void generalButton1(){

  // Play/pause
  ConsumerControl.press(CONSUMER_CONTROL_PLAY_PAUSE);
  delay(10);
  ConsumerControl.release();
}


void generalButton2() {

  // Screenshot (Windows + Shift + S)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('s');

  delay(10);

  Keyboard.releaseAll();
}


void generalButton3() {

  // Lock PC (Windows + L)
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('l');

  delay(10);

  Keyboard.releaseAll();
}

// ------------------------------
// Coding profile button actions
// ------------------------------

void codingButton1(){

  // Toggle terminal (Ctrl + `)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('`');

  delay(10);
  Keyboard.releaseAll();
}


void codingButton2() {

  // Toggle comment (Ctrl + /)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('/');

  delay(10);

  Keyboard.releaseAll();
}


void codingButton3() {

  // Find in files (Ctrl + shift + f)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('f');

  delay(10);

  Keyboard.releaseAll();
}

// ------------------------------
// Arduino profile button actions
// ------------------------------

void arduinoButton1(){

  // Verify/compile (Ctrl + r)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('r');

  delay(10);
  Keyboard.releaseAll();
}


void arduinoButton2() {

  // Upload (Ctrl + u)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('u');

  delay(10);

  Keyboard.releaseAll();
}


void arduinoButton3() {

  // Serial monitor (Ctrl + shift + m)
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('m');

  delay(10);

  Keyboard.releaseAll();
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

  setProfileColor();

  // Start USB keyboard
  Keyboard.begin();
  ConsumerControl.begin();

  USB.begin();
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