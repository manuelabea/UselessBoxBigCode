#include "led.h"
#include "FastLED.h"

const int ledPin = 32;

#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS    6
CRGB leds[NUM_LEDS];
#define BRIGHTNESS 123
#define FRAMES_PER_SECOND  120

uint8_t hue;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

ledStates_t ledState;



void setLEDState(ledStates_t _ledState){
  ledState = _ledState;
}

void setUpLED(){
  FastLED.addLeds<NEOPIXEL, 32>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void checkLEDState(){
  switch (ledState) {
    case NOLED:
      FastLED.clear();
      FastLED.show();  // display the pixels
      break;
    case RED:
      fill_solid( leds, NUM_LEDS, CHSV(0,255,255) );  //set color of pixels - red
      FastLED.show();  // display the pixels
      break;
    case GREEN:
      fill_solid( leds, NUM_LEDS, CHSV(90,255,255) );  //set color of pixels - green
      FastLED.show();  // display the pixels
      break;
    case BLUE:
      fill_solid( leds, NUM_LEDS, CHSV(160,255,255) );  //set color of pixels - blue
      FastLED.show();  // display the pixels
      break;
  }
}

