#include "lightstrip.h"

LightStrip::LightStrip(int pixelCount, int pin) : Adafruit_NeoPixel(pixelCount, pin, NEO_GRB | NEO_KHZ800) {

}

void LightStrip::setColor(uint32_t color, uint32_t mask, bool clear) {
  for (uint32_t i = 0 ; i < numPixels() ; ++i) {
    if (clear) { setPixelColor(i, 0x00); }
    if (((1L << (i % 32)) & mask) > 0) {
      setPixelColor(i, color);
    }
  }
}

void LightStrip::setColorAndShow(uint32_t color, uint32_t mask, bool clear) {
  for (uint32_t i = 0 ; i < numPixels() ; ++i) {
    if (clear) { setPixelColor(i, 0x00); }
    if (((1L << (i % 32)) & mask) > 0) {
      setPixelColor(i, color);
    }
  }
  show();
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

