// Include the Adafruit NeoPixel library to control the LEDs
#include <Adafruit_NeoPixel.h>

// Define the digital pin on the Arduino that the NeoPixel data line is connected to.
// In the video, this is pin D6.
#define PIN        6

// Define the number of LEDs on the NeoPixel strip.
// The video uses a strip with 4 LEDs.
#define N_LEDS     4

// Create an instance of the Adafruit_NeoPixel class.
// This object 'strip' will be used to control the LEDs.
// Arguments:
// 1. Number of LEDs in the strip (N_LEDS)
// 2. Arduino pin number (PIN)
// 3. Pixel type flags:
//    - NEO_GRB: The color order of the pixels (Green, Red, Blue).
//    - NEO_KHZ800: The data speed (800 KHz).
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// The setup() function runs once when you press reset or power the board.
void setup() {
  // Initialize the NeoPixel library. This must be called before any other
  // strip functions are used.
  strip.begin();
}

// The loop() function runs over and over again forever.
void loop() {
  // Call the 'chase' function with the color Red.
  // strip.Color(255, 0, 0) creates the color red (Red=255, Green=0, Blue=0).
  chase(strip.Color(255, 0, 0));
  
  // Call the 'chase' function with the color Green.
  chase(strip.Color(0, 255, 0));
  
  // Call the 'chase' function with the color Blue.
  chase(strip.Color(0, 0, 255));
}


// This function creates a "chasing" light effect.
// It takes a 32-bit color value as an argument.
static void chase(uint32_t c) {
  // Loop through each pixel one by one. The loop runs a few extra times
  // (numPixels() + 4) to make the light appear to run off the end of the strip.
  for(uint16_t i = 0; i < strip.numPixels() + 4; i++) {
      // Light up the current pixel with the specified color 'c'.
      // The library is smart enough to ignore requests for pixels that don't exist (e.g., pixel 5 on a 4-pixel strip).
      strip.setPixelColor(i, c);
      
      // Turn off the pixel that is 4 positions behind the current one.
      // This creates the effect of a single light moving along the strip.
      strip.setPixelColor(i - 4, 0); // '0' means the pixel is turned off.
      
      // Send the updated pixel colors to the hardware strip.
      // Without this, changes made with setPixelColor() won't be visible.
      strip.show();
      
      // Pause for a short duration to control the speed of the animation.
      delay(25);
  }
}