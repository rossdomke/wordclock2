#include "GlobalState.h"

void WordClockProgram(GlobalState &_state){
  _state.Frame += 3;

  EVERY_N_MILLISECONDS(1500){
    for(uint8_t i = 0; i < _state.NumOfLeds(); i++){
        bool on = random(0,11) > 5;
        _state.Mask[i] = on;
      }
  }
  // for(uint8_t i = 0; i < _state.NumOfLeds(); i++){
  //   bool on = random(0,21) > 10;
  //   _state.Mask[i] = on;
  // }
}
