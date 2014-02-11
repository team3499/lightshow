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

// When the solenoids are getting to be fired
void solenoid(Strip *strip, uint8_t time, uint8_t blinkrate){
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

// Does the first half of bounce.
void middleblink(Strip *strip){
  int b=0;
  int e=strip->numPixels()-1;
  setPixelsRGB(strip, 0, 0, 0);
  for(int pixelstrip=0; pixelstrip <= strip->numPixels()/2; pixelstrip++){
    strip->setPixelColor(b, 255, 0, 255);
    strip->setPixelColor(e, 255, 0, 255);
    strip->setPixelColor(b-1, 0, 0, 0);
    strip->setPixelColor(e+1, 0, 0, 0);
    b++;
    e--;
    Serial.print(b);
    Serial.print(e);
    strip->show();
    delay(500);
  }
}

// Blink the strip one color, then a second.
void blink(Strip *strip, int r1, int g1, int b1, int r2, int g2, int b2, int wait){
  setPixelsColor(strip, strip->Color(r1, g1, b1));
  strip->show();
  delay(wait);
  setPixelsColor(strip, strip->Color(r2, g2, b2));
  strip->show();
  delay(wait);
}
