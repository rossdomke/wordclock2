#include "GlobalState.h"

void WordClockProgram(GlobalState &_state){
  bool updateMask = false;
  EVERY_N_MILLISECONDS(500){
    updateMask = true;
  }

  if(updateMask || _state.RunCount == 0){
    for(uint8_t i = 0; i < _state.NumOfLeds(); i++){
        bool on = random(0,11) > 5;
        _state.Mask[i] = on;
      }
    
  }
}
