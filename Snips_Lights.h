#ifndef SNIPS_LIGHTS_H
#define SNIPS_LIGHTS_H

// A combined color as defined in the Adafruit library
#define SLColor uint32_t
#define SLBLACK 0

// The index type for pixel iteration
#define SLPixelIndex uint16_t

// The index type for frame iteration
#define SLFrameIndex uint16_t

// Time interval in milliseconds
#define SLTimeInterval unsigned long

#define UPDATE_STATE(state, index) \
  do { \
    switch (index) { \
      case 0: \
        *state = SLStateNone; \
        break; \
      case 1: \
        *state = SLStateWakingUp; \
        break; \
      case 2: \
        *state = SLStateStandby; \
        break; \
      case 3: \
        *state = SLStateListening; \
        break; \
      case 4: \
        *state = SLStateError; \
        break; \
      default: \
        Serial.println("Unknown State"); \
        while (true) {} \
    } \
  } while (0)

#define PRINT_STATE(state) \
  do { \
    switch (state) { \
      case SLStateNone: \
        Serial.println("SLStateNone"); \
        break; \
      case SLStateWakingUp: \
        Serial.println("SLStateWakingUp"); \
        break; \
      case SLStateStandby: \
        Serial.println("SLStateStandby"); \
        break; \
      case SLStateListening: \
        Serial.println("SLStateListening"); \
        break; \
      case SLStateError: \
        Serial.println("SLStateError"); \
        break; \
      default: \
        Serial.println("Unkown State"); \
        while (true) {} \
    } \
  } while (0)

enum SLState {
  SLStateNone, SLStateWakingUp, SLStateStandby,
  SLStateListening, SLStateError
};

struct SLAnimationParameters {
  SLTimeInterval period;
  SLFrameIndex maxFrame;
};

class Snips_Lights {

 public:
  Snips_Lights(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);

  void
    setPrimaryColor(SLColor color),
    setSecondaryColor(SLColor color),
    setErrorColor(SLColor color),
    setState(SLState state),
    step();

  SLState
    getState() { return _currentState; }
  Adafruit_NeoPixel
    *getPixels() { return &_pixels; }
  SLPixelIndex
    pixelCount() { return _pixels.numPixels(); }

 private:
  void 
    transitionToNextState(),
    setPixels(Adafruit_NeoPixel pixels),
    setPixel(SLPixelIndex index, SLColor color),
    setAllPixels(SLColor color);
  Adafruit_NeoPixel
    _pixels;
  SLColor
    primaryColor,
    secondaryColor,
    errorColor;
  SLState
    _currentState;
  SLFrameIndex
    // used for continuing from previous rotation animation
    _previousRotationIndex,
    _currentFrame;
  SLAnimationParameters
    _animationParameters;
};

#endif // SNIPS_LIGHTS_H
