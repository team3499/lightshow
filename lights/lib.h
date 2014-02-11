typedef Adafruit_NeoPixel Strip;

// Set all pixels with RGB values
// setPixelsRGB(strip, 255, 255, 255);
void setPixelsRGB(Strip *strip, unsigned int r, unsigned int b, unsigned int g, bool show = false){
  for(int i = 0; i < strip->numPixels(); ++i){
    strip->setPixelColor(i, strip->Color(r, g, b));
  }
  if(show) strip->show();
}

// Set all pixles with color
// setPixelsColor(strip, strip->Color(255, 255, 255));
void setPixelsColor(Strip *strip, uint32_t color, bool show = false){
  for(int i = 0; i < strip->numPixels(); ++i){
    strip->setPixelColor(i, color);
  }
  if(show) strip->show();
}

// Strobe all the pixels once, using RGB values, and a time
// strobeOnce(strip, 255, 255, 255, 30);
int strobeOnce(Strip *strip, int r, int g, int b, int wait){
  setPixelsRGB(strip, r, g, b);
  strip->show();
  delay(wait);
  setPixelsRGB(strip, 0, 0, 0);
  strip->show();
  delay(wait);
}

// Strobe all the pixels repeatedly, using RGB values, a time, and a possible count. If count is 0, indefinatly
// strobe(strip, 30);
void strobe(Strip *strip, unsigned int wait, int count = 0){
  int num = 1;
  if(count)
    num = count;
  for(int i = 0; i <= num; i += (!!count)) {
    strobeOnce(strip, 255,   0,   0, wait);
    strobeOnce(strip, 255, 255,   0, wait);
    strobeOnce(strip, 255, 255, 255, wait);
    strobeOnce(strip,   0, 255, 255, wait);
    strobeOnce(strip,   0,   0, 255, wait);
    strobeOnce(strip, 255,   0, 255, wait);
    strobeOnce(strip,   0, 255,   0, wait);
  }
}

// Fade from off to RGB with RGB values, and time
// fadeInRGB(strip, 1000, 255, 255, 255); // One second fade in time
void fadeInRGB(Strip *strip, unsigned int time, unsigned int r, unsigned int g, unsigned int b, unsigned char mx = 255, unsigned char mn = 0){
  for(int i = mn; i < mx; ++i){
    setPixelsRGB(strip, r, g, b);
    strip->setBrightness(i);
    strip->show();
    delay(time/(mx-mn));
  }
}

// Fade from off to color, with time
// fadeInColor(strip, 1000, strip->Color(255, 255, 255));
void fadeInColor(Strip *strip, unsigned int time, uint32_t color, unsigned char mx = 255, unsigned char mn = 0){
  for(int i = mn; i < mx; ++i){
    setPixelsColor(strip, color);
    strip->setBrightness(i);
    strip->show();
    delay(time/(mx-mn));
  }
}


// Fade from RGB to off, with time
// fadeOutRGB(strip, 1000, 255, 255, 255);
void fadeOutRGB(Strip *strip, unsigned int time, unsigned int r, unsigned int g, unsigned int b, unsigned char mx = 255, unsigned char mn = 0){
  for(int i = mx; i > mn; --i){
    setPixelsRGB(strip, r, g, b);
    strip->setBrightness(i);
    strip->show();
    delay(time/(mx-mn));
  }
}

// Fade from color to off, with time
// fadeOutColor(strip, 1000, strip->Color(255, 255, 255));
void fadeOutColor(Strip *strip, unsigned int time, uint32_t color, unsigned char mx = 255, unsigned char mn = 0){
  for(int i = mx; i > mn; --i){
    setPixelsColor(strip, color);
    strip->setBrightness(i);
    strip->show();
    delay(time/(mx-mn));
  }
}
