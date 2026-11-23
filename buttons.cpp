#include "buttons.h"

const unsigned long DEBOUNCE_DELAY = 50;

bool updateButton(Button &button){
  bool currentReading = digitalRead(button.pin);

  if(currentReading != button.lastReading){
    button.lastDebounceTime = millis();
  }

  if((millis() - button.lastDebounceTime) > DEBOUNCE_DELAY){
    if(currentReading != button.stableState){
      button.stableState = currentReading;
      button.lastReading = currentReading;

      return true;
    }
  }
}