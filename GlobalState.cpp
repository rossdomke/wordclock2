#include "Arduino.h"
#include "GlobalState.h"
#include "EEPROM.h"

GlobalState::GlobalState(uint8_t width, uint8_t height, bool *mask, DS3231 *_rtc){
  CurrentPaletteIndex = 0;
  rtc = _rtc;
  Frame = 1;
  Brightness = 100;
  Width = width;
  Height = height;
  Mask = mask;
  Serpentine = true;
  CurrentColorAnimationIndex = 0;
  StepSize = 3;
}
bool H12 = false;
bool pm;
const uint8_t BRIGHTNESS_ADDRESS = 0;
const uint8_t STEPSIZE_ADDRESS = 1;
const uint8_t ANIMATION_ADDRESS = 2;
const uint8_t PALETTE_ADDRESS = 3;
const uint8_t SPEED_ADDRESS = 4;
void GlobalState::UpdateTime(){
  Hour = rtc->getHour(H12, pm);
  Min = rtc->getMinute();
}
void GlobalState::IncrementTime(int8_t amount){
  uint16_t mins = (Hour * 60) + Min;
  if (mins < abs(amount) && amount < 0){
    mins = 24 * 60 + mins + amount;
  }else{
    mins = (mins + amount) % (24 * 60);
  }
  Hour = mins / 60;
  Min = mins % 60;
  rtc->setHour(Hour);
  rtc->setMinute(Min);
}
uint8_t GlobalState::NumOfLeds(){
  return Width * Height;
}
void GlobalState::ReadFromEEPROM(){
  Brightness = EEPROM.read(BRIGHTNESS_ADDRESS);
  StepSize = EEPROM.read(STEPSIZE_ADDRESS);
  CurrentColorAnimationIndex = EEPROM.read(ANIMATION_ADDRESS);
  CurrentPaletteIndex = EEPROM.read(PALETTE_ADDRESS);
  Speed = EEPROM.read(SPEED_ADDRESS);
  if(Speed < 1)
    SetSpeed(1);
}


uint8_t GlobalState::GetBrightness(){
  return Brightness;
}
uint8_t GlobalState::GetPaletteIndex(){
  return CurrentPaletteIndex;
}
uint8_t GlobalState::GetAnimationIndex(){
  return CurrentColorAnimationIndex;
}
uint8_t GlobalState::GetStepSize(){
  return StepSize;
}
uint8_t GlobalState::GetSpeed(){
  return Speed;
}
void GlobalState::SetSpeed(uint8_t speed){
  EEPROM.write(SPEED_ADDRESS, speed);
  Speed = speed;
  return;
}
void GlobalState::SetPaletteIndex(uint8_t index){
  EEPROM.write(PALETTE_ADDRESS, index);
  CurrentPaletteIndex = index;
  return;
}
void GlobalState::SetAnimationIndex(uint8_t index){
  EEPROM.write(ANIMATION_ADDRESS, index);
  CurrentColorAnimationIndex = index;
  return;
}
void GlobalState::SetStepSize(uint8_t stepsize){
  EEPROM.write(STEPSIZE_ADDRESS, stepsize);
  StepSize = stepsize;
  return;
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
  Serial.print("Time: ");
  Serial.print(Hour);
  Serial.print(":");
  Serial.println(Min);
  Serial.print("Color Palette: ");
  Serial.println(CurrentPaletteIndex);
  Serial.print("Speed: ");
  Serial.println(Speed);
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
  // Serial.print("Btn Map: ");
  // Serial.println(btnMap, BIN); 
  // Serial.print("Button Status: ");
  // Serial.println(ButtonStatus, BIN);
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



void GlobalState::SetMaskRange(uint8_t y,uint8_t x1,uint8_t x2, bool On){
  SetMaskRange(x1, y, x2, y, On);
}
void GlobalState::SetMaskRange(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool On){
  for(uint8_t o = x1; o <= x2; o++){
    for(uint8_t i = y1; i <= y2; i++){
      Mask[XY(o, i)] = On;
    }
  }
}