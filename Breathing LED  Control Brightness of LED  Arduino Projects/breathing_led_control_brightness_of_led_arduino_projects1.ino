// Define the pin the LED is connected to.
// Pin 11 is a PWM (Pulse Width Modulation) pin.
int ledPin = 11;

void setup() {
  // Set the ledPin as an output.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Fade the LED from off to full brightness.
  // The loop iterates from 0 to 255.
  for (int a = 0; a <= 255; a++) {
    // Set the brightness of the LED using analogWrite.
    // 'a' represents the PWM duty cycle.
    analogWrite(ledPin, a);
    // Wait for 20 milliseconds to make the fade smooth.
    delay(20);
  }

  // Fade the LED from full brightness to off.
  // The loop iterates from 255 down to 0.
  for (int a = 255; a >= 0; a--) {
    // Set the brightness of the LED.
    analogWrite(ledPin, a);
    // Wait for 20 milliseconds.
    delay(20);
  }

  // Add a small pause when the LED is completely off.
  delay(200);
}