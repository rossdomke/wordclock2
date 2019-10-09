#include "Arduino.h"
#include "GlobalState.h"
#include "EEPROM.h"

GlobalState::GlobalState(uint8_t width, uint8_t height, bool *mask){
  Frame = 1;
  Brightness = 100;
  Width = width;
  Height = height;
  Mask = mask;
  Serpentine = true;
}

const uint8_t BRIGHTNESS_ADDRESS = 0;
uint8_t GlobalState::NumOfLeds(){
  return Width * Height;
}
void GlobalState::ReadFromEEPROM(){
  Brightness = EEPROM.read(BRIGHTNESS_ADDRESS);
}


uint8_t GlobalState::GetBrightness(){
  return Brightness;
}

void GlobalState::SetBrightness(uint8_t brightness){
  EEPROM.write(BRIGHTNESS_ADDRESS, brightness);
  Brightness = brightness;
  return;
}

void GlobalState::PrintState(){
  Serial.print("Num Of Leds: ");
  Serial.println(NumOfLeds()); 
  Serial.print("Frame: ");
  Serial.println(Frame);
  Serial.print("Brightness: ");
  Serial.println(Brightness);
  Serial.println("Mask: ");
  
  Serial.println("#-----------#");
  for(uint8_t x = 0; x < Width; x++){
    Serial.print("#");
    for(uint8_t y = 0; y < Height; y++){
      Serial.print(Mask[XY(x,y)]);
    }
    Serial.println("#");
  }
  Serial.println("#-----------#");
}

uint16_t GlobalState::XY(uint8_t x, uint8_t y){
  
  uint16_t i;
  uint8_t ex = x;
  uint8_t why = y;
  if(true){
    ex = Width - x - 1;
    why = Height - y - 1;
  }
  if( Serpentine == false) {
    i = (y * Width) + x;
  }

  if( Serpentine == true) {
    if( why & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (Width - 1) - ex;
      i = (why * Width) + reverseX;
    } else {
      // Even rows run forwards
      i = (why * Width) + ex;
    }
  }
  
  return i;
}

void GlobalState::SetButtonStatus(uint8_t button, bool on){
  uint8_t btnMap = B1 << (button - 1);
  if(on){
    ButtonStatus = ButtonStatus | btnMap;
  }else{
    btnMap = 255 ^ btnMap;
    ButtonStatus = ButtonStatus & btnMap;
  }
  Serial.print("Btn Map: ");
  Serial.println(btnMap, BIN); 
  Serial.print("Button Status: ");
  Serial.println(ButtonStatus, BIN);
}

bool GlobalState::GetButtonStatus(uint8_t button){
  return ((ButtonStatus >> (button - 1))) % 2 > 0;
}

void GlobalState::ClearButtonStatus(){
  ButtonStatus = B0;
}
bool GlobalState::CheckIfButtonPressed(){
  return ButtonStatus > 0;
}