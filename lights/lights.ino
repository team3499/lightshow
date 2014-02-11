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
  solenoid(&strip, 40, 250);
  //all(&strip, strip.Color(0,255,0));
  //allRGB(&strip, 0,0,255);
  //strip.show();
  //delay(2000);
  //fade(&strip);
  //strobe(&strip, strip.Color(127,127,127));
  strip.show();
}


void solenoid(Strip *strip, uint8_t time, uint8_t blinkrate){ // When the solenoids are getting to be fired
  Serial.print("CHASE RED ");
  for(int i=0; i<strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->Color(255,0,0));
    strip->show();
    Serial.print(i);
    Serial.print(" ");
    delay(time);
  }
  
  Serial.print(" \n");

  for(uint16_t j=0; j<3; j++){ // Supposed to blink
    for(int k=0; k < strip->numPixels(); k++) {
      strip->setPixelColor(k, 0); // Sets the Pixels OFF
    }

    strip->show();
    Serial.print("solenoid blink ");
    Serial.print(j);
    Serial.print(" off\n");
    delay(blinkrate);

    for(int k=0; k < strip->numPixels(); k++) {
      strip->setPixelColor(k, strip->Color(255, 0, 0));
    }

    strip->show();
    Serial.print("solenoid blink ");
    Serial.print(j);
    Serial.print(" on\n");
    delay(blinkrate);
  }

  strip->show();
  Serial.print("solenoid - all off\n");
}

void blinky(Strip *strip, int r, int g, int b, int r1, int g1, int b1, int wait){
  for(int i=0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->Color(r, g, b));
  }
  strip->show();
  delay(wait);
  for(int i=0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->Color(r1, g1, b1));
  }
  strip->show();
  delay(wait);
}

void run(Strip *strip){
  for(int b=0; b < strip->numPixels(); b++) {
    strip->setPixelColor(b, strip->Color(255, 0, 255));
    strip->show();
  //Serial.print(b);
  //for(int e=25; e < strip->numPixels(); e--){
    //strip->setPixelColor(e, strip->Color(255, 0, 255));
    //strip->show();
  }
  delay(1000);
  for(int b=0; b < strip->numPixels(); b++)
    strip->setPixelColor(b, strip->Color(0,0,0));
  strip->show();
  //Serial.print(b);
  //for(int e=25; e < strip->numPixels(); e--)
  //strip->setPixelColor(e, strip->Color(0,0,0));
  //strip->show();
  delay(1000);
}

