#ifndef coloranimations_h
#define coloranimations_h
typedef CRGB (*Animations[])(GlobalState&,uint8_t x, uint8_t y);

inline CRGB vmirror(GlobalState &_state, uint8_t x, uint8_t y){
  return ColorFromPalette(palettes[_state.GetPaletteIndex()], _state.Frame + (5 - abs(5 - y)) * _state.GetStepSize(), 255, LINEARBLEND );
}
inline CRGB hmirror(GlobalState &_state, uint8_t x, uint8_t y){
  return ColorFromPalette(palettes[_state.GetPaletteIndex()], _state.Frame + (5 - abs(5 - x)) * _state.GetStepSize(), 255, LINEARBLEND );
}

inline CRGB circleout(GlobalState &_state, uint8_t x, uint8_t y){
  return ColorFromPalette(palettes[_state.GetPaletteIndex()], _state.Frame + max(abs(5-x), abs(5-y)) * _state.GetStepSize(), 255, LINEARBLEND );
}
inline CRGB circlein(GlobalState &_state, uint8_t x, uint8_t y){
  return ColorFromPalette(palettes[_state.GetPaletteIndex()],(255 - _state.Frame) + max(abs(5-x), abs(5-y)) * _state.GetStepSize(), 255, LINEARBLEND );
}
inline CRGB leftToRight(GlobalState &_state, uint8_t x, uint8_t y){
  return ColorFromPalette(palettes[_state.GetPaletteIndex()], _state.Frame + x * _state.GetStepSize(), 255, LINEARBLEND );
}
inline CRGB topToBottom(GlobalState &_state, uint8_t x, uint8_t y){
  return ColorFromPalette(palettes[_state.GetPaletteIndex()], _state.Frame + y * _state.GetStepSize(), 255, LINEARBLEND );
}

Animations animations = {leftToRight, topToBottom, vmirror, hmirror, circleout, circlein};
#endif