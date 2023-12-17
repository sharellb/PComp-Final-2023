#include <Adafruit_NeoPixel.h>
#define LED_PIN 2
#define LED_COUNT 8 //NeoPixel stick size
int incomingByte;


// 255,225,53 banana
// 


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN); // NEOPIXEL setup for stick

void setup() {
  strip.begin(); // INITIALIZE NeoPixel strip object
  Serial.begin(9600); // INITIALIZE serial for communication of midi

  for(int i=0; i<LED_COUNT; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // green

    strip.show();   // Send the updated pixel colors to the hardware.
  }
  Serial.println("start");
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    int r = 255;
    int g = 255;
    int b = 255;
  
    if (incomingByte == 'F') {
      r = 76;
      g = 153;
      b = 0;

    }  else if (incomingByte == 'G')  {
      r = 255;
      g = 233;
      b = 84;
    }  else if (incomingByte == 'D')  {
      r = 255;
      g = 128;
      b = 0;
    }  else if (incomingByte == 'A')  {
      r = 204;
      g = 0;
      b = 0;
    } else {
      int colorValues[3] = {255, 10, 127};
      r = colorValues[random(0,2)];
      b = colorValues[random(0,2)];
      g = colorValues[random(0,2)];
    }

    for(int i=0; i<LED_COUNT; i++) { // For each pixel...
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      strip.setPixelColor(i, strip.Color(r, g, b)); 
    }

    strip.show();   // Send the updated pixel colors to the hardware.

    // print the results:
    Serial.print(incomingByte);
  }
}
