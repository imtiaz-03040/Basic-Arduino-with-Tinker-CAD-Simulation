// This is an example code for the Adafruit NeoPixel library.
// It is designed for a 7-pixel NeoPixel Jewel connected to pin 6 of an Arduino.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Define the pin the NeoPixel is connected to
#define PIN 6

// Create an instance of the Adafruit_NeoPixel class called 'strip'
// Parameter 1: Number of pixels in the strip (7 for the NeoPixel Jewel)
// Parameter 2: Arduino pin number
// Parameter 3: Pixel type flags (NEO_GRB for Green-Red-Blue order + NEO_KHZ800 for 800KHz speed)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the NeoPixel strip
  strip.begin();
  // Turn all pixels off initially
  strip.show(); 
}

void loop() {
  // Run the colorWipe function for Red, Green, and Blue
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue

  // Run the theaterChase function for White, Red, and Blue
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50);     // Red
  theaterChase(strip.Color(0, 0, 127), 50);     // Blue

  // Run the rainbow animation functions
  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

// Fills the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Creates a flowing rainbow effect across all pixels
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j = 0; j < 256; j++) {
    for(i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Creates a cycling rainbow that is distributed across the pixels
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Creates a "theater marquee" chasing light effect
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {  // do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c); // turn every third pixel on
      }
      strip.show();
      delay(wait);
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0); // turn every third pixel off
      }
    }
  }
}

// A theater-style chase with rainbow colors
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) { // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255));
      }
      strip.show();
      delay(wait);
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);
      }
    }
  }
}

// Helper function to generate a color from a position on a color wheel (0-255)
// Input a value 0 to 255 to get a color value.
// The colors are a transition from Red -> Green -> Blue -> Red.
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