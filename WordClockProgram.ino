#include "GlobalState.h"

void RandomMaskProgram(GlobalState &_state){
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
enum Words {Its, A, Half, MinTen, Quarter, Twenty, MinFive, To, Past, After, Seven, Noon,
            Midnight, Ten, Five, Nine, Two, Eleven, Eight, One, Six, Three, Four, Oclock,
            Birth, Day, Pasta, Last};
uint8_t activeWord = 0;
void WordClockProgram(GlobalState &_state){
  if(_state.GetButtonStatus(3)){
    activeWord = (activeWord + 1) % Words::Last;
  }
  if(_state.GetButtonStatus(4)){
    activeWord = (activeWord - 1) % Words::Last;
  }
  if(_state.RunAnimation){
    const uint8_t hour = _state.Time.hour();
    const uint8_t min =_state.Time.minute();

    _state.SetMaskRange(0,0,11,11, false);
    LightWord(activeWord, _state);
    // WordClock();
  }
}



// void WordClock(){
//   for(int i = 0; i < NUM_LEDS; i++){
//     mask[i] = 0;
//   }
//   EVERY_N_MILLISECONDS(500){
//     t = rtc.getTime();
//   }
  
//   Hour = t.hour;
//   Min = round(t.min / 5.00) * 5;

//   LightWord(Words::Its);
//   if(Min != 0 && Min != 60){
//     if(Min > 30){
//       LightWord(Words::Til);
//     }else{
//       LightWord(Words::Past);
//     }
//   }
//   if(Min > 30){
//     Hour = (Hour +1) % 24;
//   }
//   if(Hour != 0 && Hour != 12){
//     LightWord(Words::Oclock);
//   }
//   switch(Min){
//     case 0:
//     case 60:
//       break;
//     case 5:
//     case 55:
//       LightWord(Words::MinFive);
//       break;
//     case 10:
//     case 50:
//       LightWord(Words::MinTen);
//       break;
//     case 15:
//     case 45:
//       LightWord(Words::A);
//       LightWord(Words::Quarter);
//       break;
//     case 20:
//     case 40:
//       LightWord(Words::Twenty);
//       break;
//     case 25:
//     case 35:
//       LightWord(Words::Twenty);
//       LightWord(Words::MinFive);
//       break;
//     case 30:
//       LightWord(Words::Half);
//       break;
//   }
//   switch(Hour){
//     case 0:
//       LightWord(Words::Midnight);
//       break;
//     case 12:
//       LightWord(Words::Noon);
//       break;
//     case 1:
//     case 13:
//       LightWord(Words::One);
//       break;
//     case 2:
//     case 14:
//       LightWord(Words::Two);
//       break;
//     case 3:
//     case 15:
//       LightWord(Words::Three);
//       break;
//     case 4:
//     case 16:
//       LightWord(Words::Four);
//       break;
//     case 5:
//     case 17:
//       LightWord(Words::Five);
//       break;
//     case 6:
//     case 18:
//       LightWord(Words::Six);
//       break;
//     case 7:
//     case 19:
//       LightWord(Words::Seven);
//       break;
//     case 8:
//     case 20:
//       LightWord(Words::Eight);
//       break;
//     case 9:
//     case 21:
//       LightWord(Words::Nine);
//       break;
//     case 10:
//     case 22:
//       LightWord(Words::Ten);
//       break;
//     case 11:
//     case 23:
//       LightWord(Words::Eleven);
//       break;
//   }
// }
void LightWord(uint8_t wrd, GlobalState &_state){
  switch(wrd){
    case Words::Its:
      _state.SetMaskRange(0, 0, 2, true);
      break;
    case Words::A:
      _state.SetMaskRange(0, 4, 4, true);
      break;
    case Words::Half:
      _state.SetMaskRange(0, 6, 9, true);
      break;
    case Words::MinTen:
      _state.SetMaskRange(1, 1, 3, true);
      break;
    case Words::Quarter:
      _state.SetMaskRange(1, 4, 10, true);
      break;
    case Words::Twenty:
      _state.SetMaskRange(2, 0, 5, true);
      break;
    case Words::MinFive:
      _state.SetMaskRange(2, 7, 10, true);
      break;
    case Words::To:
      _state.SetMaskRange(3, 0, 1, true);
      break;
    case Words::Past:
      _state.SetMaskRange(3, 2, 5, true);
      break;
    case Words::After:
      _state.SetMaskRange(3, 6, 10, true);
      break;
    case Words::Seven:
      _state.SetMaskRange(4, 1, 5, true);
      break;
    case Words::Noon:
      _state.SetMaskRange(4, 7, 10, true);
      break;
    case Words::Midnight:
      _state.SetMaskRange(6, 0, 7, true);
      break;
    case Words::Ten:
      _state.SetMaskRange(6, 8, 10, true);
      break;
    case Words::Five:
      _state.SetMaskRange(7, 0, 3, true);
      break;
    case Words::Nine:
      _state.SetMaskRange(7, 4, 7, true);
      break;
    case Words::Two:
      _state.SetMaskRange(7, 8, 10, true);
      break;
    case Words::Eleven:
      _state.SetMaskRange(8, 0, 5, true);
      break;
    case Words::Eight:
      _state.SetMaskRange(8, 6, 10, true);
      break;
    case Words::One:
      _state.SetMaskRange(9, 0, 2, true);
      break;
    case Words::Six:
      _state.SetMaskRange(9, 3, 5, true);
      break;
    case Words::Three:
      _state.SetMaskRange(9, 6, 10, true);
      break;
    case Words::Four:
      _state.SetMaskRange(10, 0, 3, true);
      break;
    case Words::Oclock:
      _state.SetMaskRange(10, 5, 10, true);
      break;
    case Words::Pasta:
      _state.SetMaskRange(3, 2, 6, true);
      break;
    case Words::Birth:
      _state.SetMaskRange(5, 1, 5, true);
      break;
    case Words::Day:
      _state.SetMaskRange(5, 7, 9, true);
      break;
    default:
      _state.SetMaskRange(2, 2, 8, 8, true);
      break;
  }
}
