#include <Adafruit_NeoPixel.h>
#include "lightstrip.h"

#define PWM_PORT        2
#define RING_FRONT_PORT 5
#define RING_BACK_PORT  6

////////////////////////////////////////////////////////////////////////////

#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF

////////////////////////////////////////////////////////////////////////////

// These are individual light shows.  They will be called repeatedly so
// should represent a single, full cycle of animation.  See lightshows
// below to define the PWM pulse width that triggers each show.

LightStrip ringFront = LightStrip(16, RING_FRONT_PORT);
LightStrip ringBack  = LightStrip(16, RING_BACK_PORT);

// Alternates even/odd between color
void alternating(uint32_t color1, uint32_t color2) {
  ringFront.setBrightness(0xFF);
  ringBack.setBrightness(0xFF);

  ringFront.setColor(color1, 0xAAAA);
  ringFront.setColor(color2, 0x5555);
  ringBack.setColor(color1, 0xAAAA);
  ringBack.setColor(color2, 0x5555);
  ringFront.show();
  ringBack.show();
  delay(250);
  ringFront.setColor(color1, 0x5555);
  ringFront.setColor(color2, 0xAAAA);
  ringBack.setColor(color1, 0x5555);
  ringBack.setColor(color2, 0xAAAA);
  ringFront.show();
  ringBack.show();
  delay(250);
}

void autonomous() {
  ringFront.setBrightness(0xFF);
  ringBack.setBrightness(0xFF);

  // ringFront.setColor(BLUE, 0b0000000000000001, true);
  // ringFront.setColor(RED,  0b0000000100000000);
  // ringFront.show();
  // ringBack.setColor(BLUE,  0b0000000000000001, true);
  // ringBack.setColor(RED,   0b0000000100000000);
  // ringBack.show();

  for (int i = 0 ; i < 8 ; ++i) {
    ringFront.setColor(RED, 1 << i, true);
    ringFront.setColor(BLUE,  1 << (i+8));
    ringFront.show();
    ringBack.setColor(RED,  1 << i, true);
    ringBack.setColor(BLUE,   1 << (i+8));
    ringBack.show();
    delay(100);
  }
  for (int i = 0 ; i < 8 ; ++i) {
    ringFront.setColor(BLUE, 1 << i, true);
    ringFront.setColor(RED,  1 << (i+8));
    ringFront.show();
    ringBack.setColor(BLUE,  1 << i, true);
    ringBack.setColor(RED,   1 << (i+8));
    ringBack.show();
    delay(100);
  }
}

void ramp0() {
  ringFront.setColor(RED, 0xFFFF, true);
  ringBack.setColor(RED,  0xFFFF, true);
  ringFront.setBrightness(0xFF);
  ringBack.setBrightness(0xFF);
  ringFront.show();
  ringBack.show();
}

void ramp1() {
  ringFront.setColor(GREEN, 0xFF00, true);
  ringFront.setColor(RED,   0x00FF);
  ringBack.setColor(GREEN,  0x00FF, true);
  ringBack.setColor(RED,    0xFF00);
  ringFront.setBrightness(0xFF);
  ringBack.setBrightness(0xFF);
  ringFront.show();
  ringBack.show();
}

void ramp2() {
  ringFront.setColor(RED,   0xFF00, true);
  ringFront.setColor(GREEN, 0x00FF);
  ringBack.setColor(RED,    0x00FF, true);
  ringBack.setColor(GREEN,  0xFF00);
  ringFront.setBrightness(0xFF);
  ringBack.setBrightness(0xFF);
  ringFront.show();
  ringBack.show();
}

void ramp3() {
  ringFront.setColor(GREEN, 0xFFFF, true);
  ringBack.setColor(GREEN,  0xFFFF, true);
  ringFront.setBrightness(0xFF);
  ringBack.setBrightness(0xFF);
  ringFront.show();
  ringBack.show();
}

void blackout() {
  if (ringFront.getBrightness() > 0) { ringFront.fadeOut(); }
  ringFront.setBrightness(0);
  if (ringBack.getBrightness() > 0) { ringBack.fadeOut(); }
  ringBack.setBrightness(0);
}

void camera() {
  ringFront.setColorAndShow(0x0000FF);
  ringBack.setColorAndShow(0x0000FF);
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

// define the lightshows with pwm time boundaries in microseconds.  The overlap
// between entries allows for some jitter and a new state should not be entered
// until the neighboring state has been left.  Values measured off the cRIO:
//     650us   Autonomous
//    1000us   Showoff
//    1300us   Catching
//    1650us   Disabled
//    2000us   Teleop
pwm_lightshow_t lightshows[] = {
  {    0,  500, &blackout,   "blackout"},     // blackout
  {  450,  850, &ramp0,      "ramp_neither"}, // ramp sensors detect: neither
  {  800, 1200, &ramp1,      "ramp_left" },   // ramp sensors detect: left
  { 1100, 1500, &ramp2,      "ramp_right" },  // ramp sensors detect: right
  { 1450, 1850, &ramp3,      "ramp_both" },   // ramp sensors detect: both
  { 1800, 2200, &autonomous, "autonomous" },  // spinner
  { 2150, 9000, &camera,     "camera" },      // camera illumination
  { 9999, 9999, &blackout,   "boundary" }     // no lights
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

  if (digitalRead(PWM_PORT) == LOW) {
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

    if (pulse >= lightshow->lowerBound &&
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

  ringFront.begin();
  ringBack.begin();
  ringFront.show();
  ringBack.show();

  pinMode(PWM_PORT, INPUT);
  pinMode(RING_FRONT_PORT, OUTPUT);
  pinMode(RING_BACK_PORT, OUTPUT);

  attachInterrupt(0, isr, CHANGE);
}

void loop() {
  selectAndRunLightShow(pwmPulseWidth);
}
