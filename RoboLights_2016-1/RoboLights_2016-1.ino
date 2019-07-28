/* SparkFun WS2812 Breakout Board Example
  SparkFun Electronics
  date: July 25, 2013
  license: GNU GENERAL PUBLIC LICENSE
  
  Requires the Adafruit NeoPixel library. It's awesome, go get it.
  https://github.com/adafruit/Adafruit_NeoPixel
  
  This simple example code runs three sets of animations on a group of WS2812
  breakout boards. The more boards you link up, the better these animations
  will look. 
  
  For help linking WS2812 breakouts, checkout our hookup guide:
  https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide
  
  Before uploading the code, make sure you adjust the two defines at the
  top of this sketch: PIN and LED_COUNT. Pin should be the Arduino pin
  you've got connected to the first pixel's DIN pin. By default it's
  set to Arduino pin 4. LED_COUNT should be the number of breakout boards
  you have linked up.
*/
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

 //pin 5 is on the left, pin 3 is on the right
#define LED_COUNT 60
int brightness = 0;
int fadeAmount = 10;

// creates the names and sets up the pins used to define the LED strips
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, 5, NEO_GRB + NEO_KHZ800);


//setup 
void setup()
{
  leds.begin();  //starts LED strip
  clearLEDs ();  //defined below, turns all LEDs off
  leds.show();  //updates the LEDs so they show the color
}


void loop()
{
  chaseCycle(5);
  clearLEDs();
}

// Sets all LEDs to off, but DOES NOT update the display;
// call leds.show() to actually turn them off after this.
void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
  }
}

void chaseCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< leds.numPixels(); i++) {
      leds.setPixelColor(i, Wheel(((i * 256 / LED_COUNT) + j) & 255));
    }
    leds.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 16) {
   return leds.Color(128, 0, 128);
  } else if(WheelPos < 64) {
   WheelPos -= 16;
   return leds.Color(0, 0, 0);
  } else if(WheelPos < 80) {
   WheelPos -= -64;
   return leds.Color(0, 128, 0);
  } else if(WheelPos < 128) {
    WheelPos -= -80;
    return leds.Color(0, 0, 0);
  } else if(WheelPos < 144) {
    WheelPos -= 128;
    return leds.Color(128, 0, 128);
  } else if(WheelPos < 192) {
    WheelPos -= 144;
    return leds.Color(0, 0, 0);
  } else if(WheelPos < 208) {
    WheelPos -= 192;
    return leds.Color(0, 128, 0);
  } else{
  WheelPos -=208;
  return leds.Color(0, 0, 0);
  }
}


