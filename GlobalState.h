#ifndef GlobalState_h
#define GlobalState_h
#include "Arduino.h"
#include "FastLED.h"
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

    //functions
    uint8_t NumOfLeds();
    void ReadFromEEPROM();
    void WriteToEEPROM();
    void PrintState();
    void SetBrightness(uint8_t);
    uint8_t GetBrightness();
    uint16_t XY(uint8_t, uint8_t);
  private: 
    uint8_t Brightness;
};
#endif
