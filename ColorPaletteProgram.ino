#include "GlobalState.h"
#include "ColorPallettes.h"
enum CPMode { changePalette, changePattern, changeStepSize, changeSpeed, CPCount };
CPMode activeCPMode = CPMode::changePalette;
void ColorPaletteProgram(GlobalState &_state){
  if(_state.RunCount == 0){
    activeCPMode = changePalette;
  }

  if(_state.GetButtonStatus(2)){
    activeCPMode = (CPMode)((activeCPMode + 1) % CPMode::CPCount);
  }
  if (activeCPMode == CPMode::changePalette){
    if(_state.GetButtonStatus(3)){
      _state.SetPaletteIndex((_state.GetPaletteIndex() + 1) %(sizeof(palettes)/sizeof(CRGBPalette16)));
    }
    if(_state.GetButtonStatus(4)){
      if(state.GetPaletteIndex() == 0){
        _state.SetPaletteIndex((sizeof(palettes)/sizeof(CRGBPalette16)) -1);
      }
      else
      {
        _state.SetPaletteIndex(_state.GetPaletteIndex() - 1);
      }
    }
  }
  if(activeCPMode == CPMode::changePattern){
     if(_state.GetButtonStatus(3)){
       _state.SetAnimationIndex((_state.GetAnimationIndex() + 1) % (sizeof(animations)/2));
    }
    if(_state.GetButtonStatus(4)){
      if(_state.GetAnimationIndex() == 0){
   
        _state.SetAnimationIndex((sizeof(animations)/2) - 1);
      }
      else
      {
        _state.SetAnimationIndex(_state.GetAnimationIndex() - 1);
      }
    }
  }
  if(activeCPMode == CPMode::changeStepSize){
     if(_state.GetButtonStatus(3)){
       if(_state.GetStepSize() < 20)
        _state.SetStepSize(_state.GetStepSize() + 1);
    }
    if(_state.GetButtonStatus(4)){
      if(_state.GetStepSize() > 1)
        _state.SetStepSize(_state.GetStepSize() - 1);
    }
  }
  if(activeCPMode == CPMode::changeSpeed){
    if(_state.GetButtonStatus(3)){
      Serial.println("faster daddy");
      if(_state.GetSpeed() < 10)
        _state.SetSpeed(_state.GetSpeed() + 1);
    }
    if(_state.GetButtonStatus(4)){
      Serial.println("slower please");
      if(_state.GetSpeed() > 1)
        _state.SetSpeed(_state.GetSpeed() - 1);
    }
  }
  if(_state.RunCount == 0 || _state.RunAnimation){
    _state.SetMaskRange(0,0,10,10, true);
  }
}