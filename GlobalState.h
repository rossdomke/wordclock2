#ifndef GlobalState_h
#define GlobalState_h
#include "Arduino.h"
#include "FastLED.h"
#include <DS3231.h>
class GlobalState
{
  public: 
    GlobalState(uint8_t, uint8_t, bool[], DS3231*);
    //variables
    void (*Program)(GlobalState&);
    bool *Mask;
    DS3231 *rtc;
    uint8_t Frame;
    uint8_t Width;
    uint8_t Height;
    bool Serpentine; 
    bool RunAnimation;
    long RunCount; 
    uint8_t Hour;
    uint8_t Min;

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
    void UpdateTime();
    void IncrementTime(int8_t);
    uint8_t GetPaletteIndex();
    uint8_t GetAnimationIndex();
    uint8_t GetStepSize();
    uint8_t GetSpeed();
    void SetPaletteIndex(uint8_t);
    void SetAnimationIndex(uint8_t);
    void SetStepSize(uint8_t);
    void SetSpeed(uint8_t);
  private: 
    uint8_t ButtonStatus;
    uint8_t Brightness;
    uint8_t CurrentPaletteIndex;
    uint8_t CurrentColorAnimationIndex;
    uint8_t StepSize;
    uint8_t Speed;
};
#endif
