#include "MIDIUSB.h"
// Adapted from: 
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#define LED_PIN 2
#define LED_COUNT 8 //NeoPixel stick size

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN); // NEOPIXEL setup for stick

void setup() {
  strip.begin(); // INITIALIZE NeoPixel strip object
  Serial.begin(9600); // INITIALIZE serial for communication of midi

  for(int i=0; i<LED_COUNT; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // green

    strip.show();   // Send the updated pixel colors to the hardware.
  }
}

void loop() {
 
}
