#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6     //data output pin on Arduino

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int numLED = 71;   //number of LEDs in the strand
//LED#17 - LED#61 should be faster
int lowBeat = 17;
int highBeat = 61;
int fasterFactor = 5;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLED, PIN, NEO_GRB + NEO_KHZ800);
int pulseSpeed = 10;   //pulseSpeed: smaller number faster pulses scroll
int pulseRate = 500;  //pulseRate: time delay until the next pulse
int pulseTrailLength = 4;
int maxWhite = 255;     //maximum intensity for WHITE light, 0 <= maxWhite <= 255
int maxRed = 255;       //maximum intensity for RED light, 0 <= maxRed <= 255
int maxGreen = 255;     //maximum intensity for GREEN light, 0 <= maxGreen <= 255
int maxBlue = 255;      //maximum intensity for BLUE light, 0 <= maxBlue <= 255
int allianceColor = 2;   //allianceColor:  0=RED, 1=GREEN, 2=BLUE

//int waitTime = 1000;                    // WAIT WAIT WAIT WAIT WAIT WAIT WAIT WAIT WAIT 
//int waitTime2 = 1000;
//int skip = 10;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

//setup an array to store LED values
//set pixel pattern
//int* pixel = new int[numLED];
//int* pixelTemp = new int[numLED];
//int highPoint = numLED;
//int lowPoint = 0;
//int red = 10;
//int green = 10;
//int blue = 10;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  //#if defined (__AVR_ATtiny85__)
  //  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  //#endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  //The following section is designed for CPR3663 pulses           
  switch (allianceColor) {
    case 0:
      //RED
      leadingTrailRGB(maxRed, 0, 0, pulseSpeed);    //Red (parameters: r, g, b, delay)
      break;
    case 1:
      //GREEN
      leadingTrailRGB(0, maxGreen, 0, pulseSpeed);    //Green (parameters: r, g, b, delay)
      break;
    case 2:
      //BLUE
      leadingTrailRGB(0, 0, maxBlue, pulseSpeed);    //Blue (parameters: r, g, b, delay)
      break;
  }
  delay(pulseRate);
/*
//=====
  //red = random(10, 255);
  //green = random(10, 255);
  //blue = random(10, 255);
  //waitTime = random(15);
  //skip = random(4);
*/

/*
  //===== Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), waitTime); // Red
  colorWipe(strip.Color(0, 255, 0), waitTime); // Green
  colorWipe(strip.Color(0, 0, 255), waitTime); // Blue
  colorWipe(strip.Color(127, 127, 127), waitTime); //White
  colorWipe(strip.Color(0, 0, 0, 255), waitTime); // White RGBW

  //===== Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), waitTime); // White
  theaterChase(strip.Color(127, 0, 0), waitTime); // Red
  theaterChase(strip.Color(0, 0, 127), waitTime); // Blue
  //=====
  rainbow(waitTime2);
  rainbowCycle(waitTime2);
  theaterChaseRainbow(waitTime);
*/


}

//Bright leading light with a trailing tail <<< RGB RGB RGB RGB RGB RGB RGB RGB RGB RGB RGB  RGB RGB RGB RGB RGB RGB RGB RGB RGB RGB RGB  RGB RGB RGB RGB RGB RGB RGB RGB RGB RGB RGB 
void leadingTrailRGB(int red, int green, int blue, uint8_t wait) {
  //strip.setPixelColor(ledPos, color)
  for (int i = pulseTrailLength; i < numLED + pulseTrailLength; i++) {
    strip.setPixelColor(i, maxWhite, maxWhite, maxWhite);      //leading white light
    for (int p = 1; p < pulseTrailLength; p++) {
      strip.setPixelColor(i - p, red / pulseTrailLength * (pulseTrailLength - p) , 
                                green / pulseTrailLength * (pulseTrailLength - p) ,  
                                blue / pulseTrailLength * (pulseTrailLength - p) );
    }
    strip.setPixelColor(i - pulseTrailLength, 0);    //turn LED off
    strip.show();
    //LED#17 - LED#61 should be faster
    if (i < lowBeat || i > highBeat) {
      delay(wait);
    } else {
      delay(wait / fasterFactor);    //faster factor
    }
  }  
}

/*
////turn all LEDs off  OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF OFF 
void ledOff() {
  for (int i = 0; i < numLED; i++) {
    strip.setPixelColor(i, 0);        //turn all off
  }
  strip.show();
}
*/

/*
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
*/

/*
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
*/

/*
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
*/

/*
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
*/

/*
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
*/ 


/*
//Bright leading light with a trailing tail <<<AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void leadingTrailA(uint32_t c, uint8_t wait) {
  //strip.setPixelColor

  highPoint = random(numLED);
  if (highPoint <= lowPoint) {
    highPoint = numLED;
  }
  
  for (int i = lowPoint; i < highPoint; i++) {
    for (int blank = 0; blank < i; blank++) {
      strip.setPixelColor(blank, 0);
    }
    strip.setPixelColor(i, c);      //turn LED on
    strip.show();
    delay(wait);
  }
  
  ledOff();
  
  lowPoint = random(numLED);
  if(lowPoint >= highPoint) {
    lowPoint = 0;
  }
  for (int i = highPoint; i > lowPoint; i--) {
    for (int blank = numLED; blank > i; blank--) {
      strip.setPixelColor(blank, 0);
    }
    strip.setPixelColor(i, c);      //turn LED on
    strip.show();
    delay(wait);
  }

  ledOff();
}
*/

/*
//Bright leading light with a trailing tail <<< BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
void leadingTrailB(uint8_t wait) {
  //strip.setPixelColor(ledPos, color)
  int trailLength = 10;
  for (int i = trailLength; i < numLED + trailLength; i++) {
    strip.setPixelColor(i, 127, 127, 127);
    for (int p = 1; p < trailLength; p++) {
      strip.setPixelColor(i - p, 0, 0,  255 / pow(2, p-1) );
    }
    strip.setPixelColor(i - trailLength, 0);    //turn LED off
    strip.show();
    delay(wait);
  }
}
*/

/*
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
*/
