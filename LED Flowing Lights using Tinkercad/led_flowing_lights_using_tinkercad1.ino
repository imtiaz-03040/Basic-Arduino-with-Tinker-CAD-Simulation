/*
  LED Flowing Lights
  ------------------

  This program lights up 8 LEDs connected to digital pins 1 through 8
  in a sequential "filling" pattern. First, it turns each LED on one by one
  with a delay. After all are on, it turns them off one by one in the
  same order. This cycle repeats continuously.

  The circuit:
  - 8 LEDs connected from digital pins 1-8 to GND.
  - The positive leg (anode) of each LED is connected to a digital pin (1-8).
  - The negative leg (cathode) of each LED is connected to a 220-ohm resistor.
  - The other end of each resistor is connected to the Arduino's GND pin.

  As shown in the video.
*/

// The setup function runs once when you press reset or power the board
void setup() {
  // Declare a variable to hold the pin number.
  // Using a 'for' loop to initialize each pin as an output.
  unsigned char ledPin;
  for (ledPin = 1; ledPin <= 8; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
}

// The loop function runs over and over again forever
void loop() {
  // Declare a variable to hold the pin number.
  unsigned char ledPin;

  // Loop from pin 1 to 8, turning each LED ON.
  // This creates the "filling" effect.
  for (ledPin = 1; ledPin <= 8; ledPin++) {
    digitalWrite(ledPin, HIGH); // Turn the LED on
    delay(300);                 // Wait for 300 milliseconds
  }

  // Loop from pin 1 to 8, turning each LED OFF.
  // This creates the "emptying" effect.
  for (ledPin = 1; ledPin <= 8; ledPin++) {
    digitalWrite(ledPin, LOW);  // Turn the LED off
    delay(300);                 // Wait for 300 milliseconds
  }
}