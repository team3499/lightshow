#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){ // For testing
  uint16_t n = strip.numPixels();
  Serial.print('pixels:'+n);
  solenoid(40, 200);
}

void solenoid(uint8_t time, uint8_t blinkrate){ // When the solenoids are getting to be fired
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setBrightness(255);
    strip.setPixelColor(i, strip.Color(127,0,0));
    strip.show();
    Serial.print("solenoid - light on #"+i);
    delay(time);
  }
  for(uint16_t i=0; i<3; i++){
    strip.setBrightness(0);
    strip.show();
    Serial.print("solenoid - blink -lights off");
    delay(blinkrate);
    strip.setBrightness(255);
    strip.show();
    Serial.print("solenoid - blink -lights on");
    delay(blinkrate);
  }
  strip.setBrightness(0);
  strip.show();
}
