#include <Adafruit_NeoPixel.h>
#include "lib.h"
#include "instruction.h"

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Strip strip = Strip(26, PIN, NEO_GRB | NEO_KHZ800);
Instruction *i = new Instruction();


void setup() {
  strip.begin();
  Serial.begin(9600);
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop(){
  
  // Check for mode switch
  
  // Switch based on mode
  switch (i->step()) {
    case 0:
      DisabledContinuous();
      break;
    case 1:
      TeleopContinuous();
      break;
    case 2:
      AutonomousContinuous();
      break;
    default:
      break;
  }
}
