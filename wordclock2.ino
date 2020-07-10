#include "FastLED.h"
#include "GlobalState.h"
#include "EEPROM.h"
#include "ColorPallettes.h"
#include "ColorAnimations.h"

FASTLED_USING_NAMESPACE

#include <DS3231.h>
#include <btn.h>

DS3231  rtc;

btn b1 = btn(10, btn::HoldType::ONE_CLICK);
btn b2 = btn(9, btn::HoldType::ONE_CLICK);
btn b3 = btn(8, btn::HoldType::ONE_CLICK);
btn b4 = btn(7, btn::HoldType::ONE_CLICK);
#define DATA_PIN 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

const uint8_t kMatrixWidth = 11;
const uint8_t kMatrixHeight = 11;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
const uint16_t NUM_LEDS = kMatrixWidth * kMatrixHeight;
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND 120;
bool mask[NUM_LEDS];
GlobalState state = GlobalState(kMatrixWidth, kMatrixHeight, mask, &rtc);




void setup() {

 delay(1000);
  Wire.begin();
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //Set Default Program
  state.Program = WordClockProgram;
  state.ReadFromEEPROM();
  FastLED.setBrightness(state.GetBrightness());
  Serial.begin(57600);
}
uint8_t hue = 0;

uint8_t currentProgram = 0;
typedef void (*Progs[])(GlobalState&);
Progs programs = {WordClockProgram, BrightnessProgram, ColorPaletteProgram, RandomMaskProgram};
void loop() {
  state.RunAnimation = false;
  state.ClearButtonStatus();
  if(b1.CheckButton()){
    currentProgram = (currentProgram + 1) % (sizeof(programs) /2);
    state.Program = programs[currentProgram];
    state.RunCount = 0;
    state.SetButtonStatus(1, !state.GetButtonStatus(1));
  }

  if(b2.CheckButton()){
    state.SetButtonStatus(2, true);
    state.PrintState();
  }
  if(b3.CheckButton()){
    state.SetButtonStatus(3, true);
  }
  if(b4.CheckButton()){
    
    state.SetButtonStatus(4, true);
  }
  if(state.CheckIfButtonPressed())
    state.RunAnimation = true;

  EVERY_N_MILLISECONDS(30){
    state.RunAnimation = true;
  }
  
  EVERY_N_MILLISECONDS(50){
    state.Frame += state.GetSpeed();
  }
  EVERY_N_SECONDS(1){
    state.UpdateTime();
    state.RunAnimation = true;
  }
  EVERY_N_MINUTES(1){
    //state.CurrentPaletteIndex = GetRandomPaletteIndex();
  }
 
  if(state.RunAnimation){
    state.Program(state);
    

    for(int x = 0; x < kMatrixWidth; x++){
      for(int y = 0; y < kMatrixHeight; y++){
        // leds[state.XY(x,y)].setHue(state.Frame + x * 3);
        leds[state.XY(x,y)] =  animations[state.GetAnimationIndex()](state, x, y);//
      }
    }
    RunMask();
    FastLED.setBrightness(state.GetBrightness());
    FastLED.show();
    state.RunCount++;

  }
}


void RunMask(){
   for(int i = 0; i < NUM_LEDS; i++){
     leds[i].fadeToBlackBy(255 * (1 - mask[i]));
   }
 } 
