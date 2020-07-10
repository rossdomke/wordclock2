#include "GlobalState.h"

void RandomMaskProgram(GlobalState &_state){
  if(_state.Frame % 25 == 0 || _state.RunCount == 0){
    _state.Frame++;
    for(uint8_t i = 0; i < _state.NumOfLeds(); i++){
        bool on = random(0,11) > 5;
        _state.Mask[i] = on;
      }
    
  } 
}

enum Words {Its, A, Half, MinTen, Quarter, Twenty, MinFive, To, Past, After, Seven, Noon,
            Midnight, Ten, Five, Nine, Two, Eleven, Eight, One, Six, Three, Four, Oclock,
            Birth, Day, Pasta, Last};
enum WCModes {run, editMin, editHour, Count}; 
WCModes activeMode = WCModes::run;
void WordClockProgram(GlobalState &_state){
  if (_state.RunCount == 0){
    activeMode = WCModes::run;
  }
  if(_state.GetButtonStatus(2)){
    activeMode = (WCModes)((activeMode + 1) % WCModes::Count);
  }
  if(_state.GetButtonStatus(3)){
    if(activeMode == WCModes::editMin){
      _state.IncrementTime(5);
    }
    if(activeMode == WCModes::editHour){
      _state.IncrementTime(60);
    }
  
  }
  if(_state.GetButtonStatus(4)){
  
    if(activeMode == WCModes::editMin){
      _state.IncrementTime(-5);
    }
    if(activeMode == WCModes::editHour){
      _state.IncrementTime(-60);
    }
  }
  if(_state.RunAnimation){
    _state.SetMaskRange(0,11,0,11, false);
    
    WordClock(_state);
    if(_state.Frame % 20 < 5){
      if( activeMode == WCModes::editMin){
        LightWord(Words::Its, false, _state);
        for (uint8_t i = Words::Half; i <= Words::MinFive; i++){
          LightWord(i, false, _state);
        }
      }
  
      if( activeMode == WCModes::editHour){
        LightWord(Words::Its, false, _state);
        LightWord(Words::Oclock, false, _state);
        for (uint8_t i = Words::Seven; i <= Words::Four; i++){
          LightWord(i, false, _state);
        }
      }
    }
  }
}



void WordClock(GlobalState &_state){
  for(int i = 0; i < NUM_LEDS; i++){
    mask[i] = 0;
  }
  
  
  uint8_t Hour = _state.Hour;
  uint8_t Min = round(_state.Min / 5.00) * 5;

  LightWord(Words::Its, _state);
  if(Min != 0 && Min != 60){
    if(Min == 30){
      LightWord(Words::Past, _state);
    }
    else if(Min > 30){
      LightWord(Words::To, _state);
    }else{
      LightWord(Words::After, _state);
    }
  }
  if(Min > 30){
    Hour = (Hour +1) % 24;
  }
  if(Hour != 0 && Hour != 12){
    LightWord(Words::Oclock, _state);
  }
  switch(Min){
    case 0:
    case 60:
      break;
    case 5:
    case 55:
      LightWord(Words::MinFive, _state);
      break;
    case 10:
    case 50:
      LightWord(Words::MinTen, _state);
      break;
    case 15:
    case 45:
      LightWord(Words::A, _state);
      LightWord(Words::Quarter, _state);
      break;
    case 20:
    case 40:
      LightWord(Words::Twenty, _state);
      break;
    case 25:
    case 35:
      LightWord(Words::Twenty, _state);
      LightWord(Words::MinFive, _state);
      break;
    case 30:
      LightWord(Words::Half, _state);
      break;
  }
  switch(Hour){
    case 0:
      LightWord(Words::Midnight, _state);
      break;
    case 12:
      LightWord(Words::Noon, _state);
      break;
    case 1:
    case 13:
      LightWord(Words::One, _state);
      break;
    case 2:
    case 14:
      LightWord(Words::Two, _state);
      break;
    case 3:
    case 15:
      LightWord(Words::Three, _state);
      break;
    case 4:
    case 16:
      LightWord(Words::Four, _state);
      break;
    case 5:
    case 17:
      LightWord(Words::Five, _state);
      break;
    case 6:
    case 18:
      LightWord(Words::Six, _state);
      break;
    case 7:
    case 19:
      LightWord(Words::Seven, _state);
      break;
    case 8:
    case 20:
      LightWord(Words::Eight, _state);
      break;
    case 9:
    case 21:
      LightWord(Words::Nine, _state);
      break;
    case 10:
    case 22:
      LightWord(Words::Ten, _state);
      break;
    case 11:
    case 23:
      LightWord(Words::Eleven, _state);
      break;
  }
}
void LightWord(uint8_t wrd, GlobalState &_state){
  LightWord(wrd, true, _state);
}
void LightWord(uint8_t wrd, bool on, GlobalState &_state){
  switch(wrd){
    case Words::Its:
      _state.SetMaskRange(0, 0, 2, on);
      break;
    case Words::A:
      _state.SetMaskRange(0, 4, 4, on);
      break;
    case Words::Half:
      _state.SetMaskRange(0, 6, 9, on);
      break;
    case Words::MinTen:
      _state.SetMaskRange(1, 1, 3, on);
      break;
    case Words::Quarter:
      _state.SetMaskRange(1, 4, 10, on);
      break;
    case Words::Twenty:
      _state.SetMaskRange(2, 0, 5, on);
      break;
    case Words::MinFive:
      _state.SetMaskRange(2, 7, 10, on);
      break;
    case Words::To:
      _state.SetMaskRange(3, 0, 1, on);
      break;
    case Words::Past:
      _state.SetMaskRange(3, 2, 5, on);
      break;
    case Words::After:
      _state.SetMaskRange(3, 6, 10, on);
      break;
    case Words::Seven:
      _state.SetMaskRange(4, 1, 5, on);
      break;
    case Words::Noon:
      _state.SetMaskRange(4, 7, 10, on);
      break;
    case Words::Midnight:
      _state.SetMaskRange(6, 0, 7, on);
      break;
    case Words::Ten:
      _state.SetMaskRange(6, 8, 10, on);
      break;
    case Words::Five:
      _state.SetMaskRange(7, 0, 3, on);
      break;
    case Words::Nine:
      _state.SetMaskRange(7, 4, 7, on);
      break;
    case Words::Two:
      _state.SetMaskRange(7, 8, 10, on);
      break;
    case Words::Eleven:
      _state.SetMaskRange(8, 0, 5, on);
      break;
    case Words::Eight:
      _state.SetMaskRange(8, 6, 10, on);
      break;
    case Words::One:
      _state.SetMaskRange(9, 0, 2, on);
      break;
    case Words::Six:
      _state.SetMaskRange(9, 3, 5, on);
      break;
    case Words::Three:
      _state.SetMaskRange(9, 6, 10, on);
      break;
    case Words::Four:
      _state.SetMaskRange(10, 0, 3, on);
      break;
    case Words::Oclock:
      _state.SetMaskRange(10, 5, 10, on);
      break;
    case Words::Pasta:
      _state.SetMaskRange(3, 2, 6, on);
      break;
    case Words::Birth:
      _state.SetMaskRange(5, 1, 5, on);
      break;
    case Words::Day:
      _state.SetMaskRange(5, 7, 9, on);
      break;
    default:
      _state.SetMaskRange(2, 2, 8, 8, on);
      break;
  }
}
