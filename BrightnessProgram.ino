#include "GlobalState.h"

void BrightnessProgram(GlobalState &_state){
  
  const uint8_t mag = 3;
  uint8_t limit = ((double)_state.Height / 255) * (255 - (double)_state.GetBrightness());
  if(_state.RunAnimation){
    //TODO: Add button clicks to brightness program
   
    for(uint8_t x = 0; x < _state.Width; x++){
      for(uint8_t y = 0; y < _state.Height; y++){
        //sin((pi/22)x) * 2 + 3
        int8_t sinY = limit + mag - sin(((2* PI) / 20) * x) * mag;
        

          

        if(y >= sinY)
          _state.Mask[_state.XY(x,y)] = true;
        else
          _state.Mask[_state.XY(x,y)] = false;
        
      }
    }
  }
 
}
