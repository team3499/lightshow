#include <Adafruit_NeoPixel.h>
#include "lightstrip.h"

#define PWM_INPUT       2
#define NEOPIXEL_OUTPUT 6

////////////////////////////////////////////////////////////////////////////

// These are individual light shows.  They will be called repeatedly so
// should represent a single, full cycle of animation.  See lightshows
// below to define the PWM pulse width that triggers each show.

LightStrip strip = LightStrip(26, NEOPIXEL_OUTPUT);

// Alternates even/odd between color
void alternating(uint32_t color1, uint32_t color2) {
  strip.fadeOut();
  strip.setColor(color1, 0xAAAAAAAA);
  strip.setColor(color2, 0x55555555);
  strip.fadeIn();
  strip.fadeOut();
  strip.setColor(color1, 0x55555555);
  strip.setColor(color2, 0xAAAAAAAA);
  strip.fadeIn();
}

void cylon(uint32_t color) {
  strip.setColorAndShow(color, 0b00000000000000000000000001100000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000000011110000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000000111111000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000001110011100, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000011100001110, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000111000000111, true); delay(100);
  strip.setColorAndShow(color, 0b00000010000000000001110000000011, true); delay(100);
  strip.setColorAndShow(color, 0b00000011000000000011100000000001, true); delay(100);
  strip.setColorAndShow(color, 0b00000011100000000111000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000001110000001110000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000111000011100000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000011100111000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000001111110000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000111100000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000011000000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000111100000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000001111110000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000011100111000000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000111000011100000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000001110000001110000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000011100000000111000000000000, true); delay(100);
  strip.setColorAndShow(color, 0b00000011000000000011100000000001, true); delay(100);
  strip.setColorAndShow(color, 0b00000010000000000001110000000011, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000111000000111, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000011100001110, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000001110011100, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000000111111000, true); delay(100);
  strip.setColorAndShow(color, 0b00000000000000000000000011110000, true); delay(100);
}

void blackout() {
  if (strip.getBrightness() > 0) { strip.fadeOut(); }
}

void autonomous() {
  strip.fadeOut(1);
  strip.setColor(strip.Color(255, 215, 0));
  strip.fadeIn(1);
}

void teleop(){
  strip.fadeOut(1);
  strip.setColor(strip.Color(0, 255, 0));
  strip.fadeIn(1);
}  
void catching() {
  uint32_t color = strip.Color(0x00, 0xFF, 0x00);
  strip.setColorAndShow(color, 0b00000000000011000000000001100000, true); delay(50);
  strip.setColorAndShow(color, 0b00000000000111100000000011110000, true); delay(50);
  strip.setColorAndShow(color, 0b00000000001100110000000110011000, true); delay(50);
  strip.setColorAndShow(color, 0b00000000011000011000001100001100, true); delay(50);
  strip.setColorAndShow(color, 0b00000000110000001100011000000110, true); delay(50);
  strip.setColorAndShow(color, 0b00000001100000000110110000000011, true); delay(50);
  strip.setColorAndShow(color, 0b00000011000000000011100000000001, true); delay(50);
  strip.setColorAndShow(color, 0b00000010000000000001000000000000, true); delay(50);
  strip.setColorAndShow(color, 0b00000000000000000000000000000000, true); delay(200);
}

void disabled(){
  strip.fadeOut(3);
  strip.setColor(strip.Color( 0, 0, 255));
  strip.fadeIn(3);
}  

void shoot() {
  strip.setColor(strip.Color(255, 0, 0));
  delay(400);
  strip.show();
  strip.setColor(strip.Color(  0,  0,  0));
  delay(400);
  strip.show();

}
void ball(){
  strip.setColor(strip.Color(75, 0, 130));
  delay(400);
  strip.show();
  strip.setColor(strip.Color( 0, 0, 0));
  delay(400);
  strip.show();
}  

void rainbow() {

}

void cops() {
  strip.setColor(strip.Color(0xFF, 0x00, 0x00), 0b00000000000000000000000000111111);
  strip.setColor(strip.Color(0x00, 0x00, 0xFF), 0b00000000000000000000111111000000);
  strip.setColor(strip.Color(0xFF, 0x00, 0x00), 0b00000000000001111110000000000000);
  strip.setColor(strip.Color(0x00, 0x00, 0xFF), 0b00000001111110000000000000000000);
  strip.show();
  delay(200);
  strip.setColor(strip.Color(0x00, 0x00, 0xFF), 0b00000000000000000000000000111111);
  strip.setColor(strip.Color(0xFF, 0x00, 0x00), 0b00000000000000000000111111000000);
  strip.setColor(strip.Color(0x00, 0x00, 0xFF), 0b00000000000001111110000000000000);
  strip.setColor(strip.Color(0xFF, 0x00, 0x00), 0b00000001111110000000000000000000);
  strip.show();
  delay(200);
}

void chaser() {

}

////////////////////////////////////////////////////////////////////////////

typedef void (*funcptr)(); // a lightshow function

// Lightshow data
typedef struct {
  uint32_t lowerBound;     // lower bound for pwm signal
  uint32_t upperBound;     // upper bound for pwm signal
  funcptr  function;       // function to invoke
  char *   name;           // name of lightshow
} pwm_lightshow_t;

// define the lightshows with pwm time boundaries in microseconds.  The overlap between
// entries allows for some jitter and a new state should not be
pwm_lightshow_t lightshows[] = {
  {    0,  300, &blackout,   "blackout"},       // no lights
  {  200,  600, &autonomous, "autonomous"},     // tbd
  {  500,  900, &catching,   "catching" },      // green alternating
  {  800, 1200, &disabled,   "disabled" },      // purple alternating
  { 1100, 1500, &rainbow,    "rainbow" },       // rainbow happy times
  { 1400, 1800, &cops,       "cops" },          // red and blue flashers
  { 1700, 2100, &blackout,   "blackout" },      // no lights
  { 9999, 9999, &blackout,   "blackout" }       // list boundary (must be last!)
};
pwm_lightshow_t * currentLightShow = lightshows;

// Function declarations
void reportLightShow(pwm_lightshow_t * lightshow, uint32_t pulse);
void selectAndRunLightShow(uint32_t pulse);

////////////////////////////////////////////////////////////////////////////

// Interrupt Service Routine to handle PWM signal output by the cRIO.  The
// main robot code will output a 198 Hz PWM signal (5.05ms).
volatile uint32_t pwmRisingEdge;    // timestamp of current rising edge
volatile uint32_t pwmPulseWidth;    // duration of pulse in microseconds

void isr() {
  uint32_t now = micros();

  if (digitalRead(PWM_INPUT) == LOW) {
    pwmPulseWidth = now - pwmRisingEdge;
  } else {
    pwmRisingEdge = now;
  }
}

////////////////////////////////////////////////////////////////////////////

// Report light show data on the serial port
void reportLightShow(pwm_lightshow_t * lightshow, uint32_t pulse) {
  if (currentLightShow == lightshow) { return; }

  Serial.print(lightshow->name);
  Serial.print(": ");
  Serial.print(lightshow->lowerBound);
  Serial.print("/");
  Serial.print(pulse);
  Serial.print("/");
  Serial.println(lightshow->upperBound);
}

// Run a lightshow based on the current received pwm pulse width received
// from the cRIO and defined in lightshows above.
void selectAndRunLightShow(uint32_t pulse) {
  pwm_lightshow_t * lightshow = lightshows;

  while (lightshow->lowerBound < 9999) {

    if (pulse > lightshow->lowerBound &&
        pulse < lightshow->upperBound) {
      // Pluse is within the window for a light show.  Make sure it has exited
      // the neighboring light show via a guard band (hysteresis) -- prevents
      // bouncing rapidly between two lightshows should we get a borderline
      // signal from the cRIO.
      if ((pulse < (lightshow+1)->lowerBound) &&
          (lightshow == lightshows || pulse > (lightshow-1)->upperBound)) {
        reportLightShow(lightshow, pulse);
        currentLightShow = lightshow;
        break;
      }
    }
    lightshow++;
  }
  (lightshow->function)();
}

////////////////////////////////////////////////////////////////////////////

void setup() {
  pwmRisingEdge = micros();
  pwmPulseWidth = 0;
  currentLightShow = 0;

  Serial.begin(9600);
  
  strip.begin();
  strip.show();

  attachInterrupt(0, isr, CHANGE);
}

void loop() {
  //selectAndRunLightShow(pwmPulseWidth);

  catching();
}
