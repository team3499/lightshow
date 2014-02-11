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


void setup() {
  strip.begin();
  Serial.begin(9600);
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  //TeleopContinuous(&strip);
  //Disabled(&strip);
  //Autonomous(&strip);
  //Shoot(&strip);
  //Ready(&strip);
  Ball(&strip);
}

void TeleopContinuous(Strip *strip){
  fadeInColor(strip, 500, strip->Color(0, 255, 0));
  fadeOutColor(strip, 500, strip->Color(0, 255, 0));  
}

void Disabled(Strip *strip){
  fadeInColor(strip, 500, strip->Color(0, 180, 247));
  fadeOutColor(strip, 500, strip->Color(0, 180, 247));
}  

void Autonomous(Strip *strip){
  fadeInColor(strip, 500, strip->Color(255, 204, 0));
  fadeOutColor(strip, 500, strip->Color(255, 204, 0));
}  

void Shoot(Strip *strip){
  setPixelsColor(strip, strip->Color(255, 0, 0));
  strip->show();
  delay(500);
  setPixelsColor(strip, strip->Color(0, 0, 0));
  strip->show();
  delay(500);
}  

void Ready(Strip *strip){
  setPixelsColor(strip, strip->Color(255, 0, 0));
  strip->show();
  delay(500);
  setPixelsColor(strip, strip->Color(0, 250, 0));
  strip->show();
  delay(500);
}  

void Ball(Strip *strip){
  setPixelsColor(strip, strip->Color(75, 0, 130));
  strip->show();
  delay(500);
  setPixelsColor(strip, strip->Color(0, 0, 0));
  strip->show();
  delay(500);
}  
