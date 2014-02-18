#define PWM_INPUT       2
#define NEOPIXEL_OUTPUT 6

////////////////////////////////////////////////////////////////////////////

// These are individual light shows.  They will be called repeatedly so
// should represent a single, full cycle of animation.  See lightshows
// below to define the PWM pulse width that triggers each show.

void blackout() {

}

void autonomous() {

}

void catching() {

}

void passing() {

}

void rainbow() {

}

void cops() {

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
  {  800, 1200, &passing,    "passing" },       // purple alternating
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

  attachInterrupt(0, isr, CHANGE);
}

void loop() {
  selectAndRunLightShow(pwmPulseWidth);
}
