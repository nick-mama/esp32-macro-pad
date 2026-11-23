#include <Arduino.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
#include "USBHIDConsumerControl.h"

#include "actions.h"

USBHIDKeyboard Keyboard;
USBHIDConsumerControl ConsumerControl;

// ------------------
// Initialize USB HID
// ------------------

void initActions(){
  Keyboard.begin();
  ConsumerControl.begin();

  // USB must begin last
  USB.begin();
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