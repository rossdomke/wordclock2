#ifndef GlobalState_h
#define GlobalState_h
#include "Arduino.h"
#include "FastLED.h"
#include <DS3231.h>
class GlobalState
{
  public: 
    GlobalState(uint8_t, uint8_t, bool[]);
    //variables
    void (*Program)(GlobalState&);
    bool *Mask;
    uint8_t Frame;
    uint8_t Width;
    uint8_t Height;
    bool Serpentine; 
    bool RunAnimation;
    long RunCount; 
    DateTime Time;
    //functions
    void SetMaskRange(uint8_t, uint8_t, uint8_t, bool);
    void SetMaskRange(uint8_t, uint8_t, uint8_t, uint8_t, bool);
    uint8_t NumOfLeds();
    void ReadFromEEPROM();
    void WriteToEEPROM();
    void PrintState();
    void SetBrightness(uint8_t);
    uint8_t GetBrightness();
    uint16_t XY(uint8_t, uint8_t);
    void SetButtonStatus(uint8_t, bool);
    bool GetButtonStatus(uint8_t);
    void ClearButtonStatus();
    bool CheckIfButtonPressed();
  private: 
    uint8_t ButtonStatus;
    uint8_t Brightness;
};
#endif
