
#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

#define PIN 0

int inputPin = 1;               // choose the input pin (for PIR sensor)
int soundPin = 4;               // pin to trigger sound
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int loopTimes = 3;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(128); // 1/2 brightness
  pinMode(inputPin, INPUT);
  pinMode(soundPin, OUTPUT);
  digitalWrite(soundPin, HIGH);
  allOff();
}

void loop() {

  val = 0;
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) 
  {            // check if the input is HIGH
    for (int x=0; x< loopTimes; x++) {
      redRun(); 
    }
  } else {
    allOff();
  } 
}

void allOff() {
  int16_t numPix = 16;
  int16_t x;
  for (x=0; x<numPix; x++) {
        pixels.setPixelColor(x, 0, 0, 0);
      }
      pixels.show();
    }
void redRun() {

  int16_t numPix = 16;
  int16_t baseDelay = 50;
  int16_t deltaDelay = 0;
  int16_t delayMult = 15;

  int16_t x, y;
  for (x=0; x<numPix; x++) {

  if (x==0) {
    digitalWrite(soundPin, LOW);
    delay(100);
  } else {
    digitalWrite(soundPin, HIGH);
  }
    
    for (y=0; y<numPix; y++) {

      if (y==x) {
        pixels.setPixelColor(y, 255, 0, 0);
      } else if (y==x-1) {
        pixels.setPixelColor(y, 255-64, 0, 0);
      } else if (y==x-2) {
        pixels.setPixelColor(y, 255-128, 0, 0);
      } else if (y==x-3) {
        pixels.setPixelColor(y, 255-192, 0, 0);
      } else {
        pixels.setPixelColor(y, 0, 0, 0);
      }
      
    }
    pixels.show();
    deltaDelay = (abs(x - numPix/2))*delayMult;
    delay(baseDelay + deltaDelay);
  }
  for (x=numPix-1; x>=0; x--) {

  if (x==(numPix-1)) {
    digitalWrite(soundPin, LOW);
    delay(100);
  } else {
    digitalWrite(soundPin, HIGH);
  }
  
    for (y=0; y<numPix; y++) {

      if (y==x) {
        pixels.setPixelColor(y, 255, 0, 0);
      } else if (y==x+1) {
        pixels.setPixelColor(y, 255-64, 0, 0);
      } else if (y==x+2) {
        pixels.setPixelColor(y, 255-128, 0, 0);
      } else if (y==x+3) {
        pixels.setPixelColor(y, 255-192, 0, 0);
      } else {
        pixels.setPixelColor(y, 0, 0, 0);
      }
    }
    pixels.show();
    deltaDelay = (abs(x - numPix/2))*delayMult;
    delay(baseDelay + deltaDelay);
  }
}


