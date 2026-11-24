#ifndef ACTIONS_H
#define ACTIONS_H

enum Action{
  ACTION_PLAY_PAUSE,
  ACTION_SCREENSHOT,
  ACTION_LOCK,

  ACTION_TERMINAL,
  ACTION_TOGGLE_COMMENT,
  ACTION_FIND_FILES,

  ACTION_VERIFY,
  ACTION_UPLOAD,
  ACTION_SERIAL_MONITOR,

  ACTION_NONE
};

void initActions();

void runAction(Action action);

// General profile
void generalButton1();
void generalButton2();
void generalButton3();

// Coding profile
void codingButton1();
void codingButton2();
void codingButton3();

// Arduino profile
void arduinoButton1();
void arduinoButton2();
void arduinoButton3();

#endif