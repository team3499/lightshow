#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(26, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  Serial.begin(9600);
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  //solenoid(&strip, 40, 250);
  //all(&strip, strip.Color(0,255,0));
  //allRGB(&strip, 0,0,255);
  //strip.show();
  //delay(2000);
  //fade(&strip);
  strobe(&strip, strip.Color(127,127,127));
  strip.show();
}

void all(Adafruit_NeoPixel *strip, uint32_t color){ // Sets all the all the Pixels to the specified color
  for(int i=0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, color);
  }
}

void allRGB(Adafruit_NeoPixel *strip, unsigned int r, unsigned int g, unsigned int b){ // Sets all the pixels in strip to rgb values specified.
  for(int i=0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->Color(r, g, b));
  }
}

void fade(Adafruit_NeoPixel *strip){ // Set a color before running (WIP)
  for(unsigned char c=0; c < 256; c++) {
    strip->setBrightness(c);
    strip->show();
    delay(50);
  }
}

void strobe(Adafruit_NeoPixel *strip, uint32_t color){ // Strobing effect (WIP)
  for(int k=0; k < strip->numPixels(); k++) {
    strip->setPixelColor(k, color);
  }
  
  strip->show();
  
  delay(1000);
  
  for(int k=0; k < strip->numPixels(); k++) {
    strip->setPixelColor(k, 0); // Sets the Pixels OFF
  }
  
  delay(1000);

  strip->show();
}

void solenoid(Adafruit_NeoPixel *strip, uint8_t time, uint8_t blinkrate){ // When the solenoids are getting to be fired
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
      strip->setPixelColor(k, strip->Color(0, 0, 255));
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

