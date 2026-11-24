#include <Arduino.h>

#include "protocol.h"
#include "profiles.h"

void initProtocol(){
  Serial.println("Macro Pad configuration protocol ready");
}

void updateProtocol(){
  if(Serial.available() == 0){
    return;
  }

  String command = Serial.readStringUntil('\n');
  command.trim();

  if(command == "GET"){
    Serial.println("Current mappings:");

    for(int profile = 0; profile < 3; profile++){
      Serial.print("Profile ");
      Serial.println(profile);

      for(int button = 0; button < 3; button++){
        Action action = getProfileAction((Profile)profile, button);

        Serial.print(" Button");
        Serial.print(button);
        Serial.print(": ");
        Serial.println((int)action);
      }
    }
  }

  else{
    Serial.println("ERROR: Unknown command");
  }
}