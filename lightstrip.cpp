#include "lightstrip.h"

LightStrip::LightStrip(int pixelCount, int pin) : Adafruit_NeoPixel(pixelCount, pin, NEO_GRB | NEO_KHZ800) {

}

void LightStrip::setColor(uint32_t color, uint32_t mask) {
  for (uint32_t i = 0 ; i < numPixels() ; ++i) {
    if (((1L << (i % 32)) & mask) > 0) {
      setPixelColor(i, color);
    }
  }
}

uint8_t LightStrip::getBrightness() {
  return brightness;
}

void LightStrip::setBrightness(uint8_t value) {
  brightness = value;
  Adafruit_NeoPixel::setBrightness(value); 
}

void LightStrip::fadeOut(uint32_t time) {  
  for (uint8_t v = getBrightness() ; v > 0 ; v--) {
    setBrightness(v);
    show();
    delay(time);
  }
}

void LightStrip::fadeIn(uint32_t time) {  
  for (uint8_t v = getBrightness() ; v < 0xFF ; v++) {
    setBrightness(v);
    show();
    delay(time);
  }
}

