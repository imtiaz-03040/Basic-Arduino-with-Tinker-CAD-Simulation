/*
  LED Pattern Project - Controlled by a Potentiometer
  
  This code reads an analog value from a potentiometer and lights up
  LEDs in a sequence based on the potentiometer's position.
  
  Hardware Setup:
  - 1 Potentiometer: Middle pin to A5, outer pins to 5V and GND.
  - 2 Green LEDs: Pins 9 and 8.
  - 2 Yellow LEDs: Pins 11 and 10.
  - 2 Red LEDs: Pins 13 and 12.
  - Each LED is connected in series with a 220-ohm resistor to its respective pin.
  - All LED cathodes are connected to GND.
*/

// Define the pins for the potentiometer and LEDs for clarity
const int potPin = A5;      // Potentiometer connected to analog pin A5

const int redLed1    = 13;
const int redLed2    = 12;
const int yellowLed1 = 11;
const int yellowLed2 = 10;
const int greenLed1  = 9;
const int greenLed2  = 8;

// Variable to store the value read from the potentiometer
int potValue = 0;

void setup() {
  // Initialize serial communication to view the potentiometer values
  Serial.begin(9600);

  // Set all the LED pins to be outputs
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(yellowLed1, OUTPUT);
  pinMode(yellowLed2, OUTPUT);
  pinMode(greenLed1, OUTPUT);
  pinMode(greenLed2, OUTPUT);
  
  // Analog pins are set as inputs by default, but declaring it is good practice.
  pinMode(potPin, INPUT);
}

void loop() {
  // Read the analog value from the potentiometer (range: 0 to 1023)
  potValue = analogRead(potPin);

  // Print the current value to the Serial Monitor for debugging
  Serial.println(potValue);
  
  // --- LED Control Logic ---
  // The logic turns on more LEDs as the potentiometer value increases.

  if (potValue <= 5) {
    // If the value is very low, turn all LEDs off.
    digitalWrite(greenLed1, LOW);
    digitalWrite(greenLed2, LOW);
    digitalWrite(yellowLed1, LOW);
    digitalWrite(yellowLed2, LOW);
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
  } 
  else if (potValue > 5 && potValue <= 341) {
    // First level: Turn on only the green LEDs.
    digitalWrite(greenLed1, HIGH);
    digitalWrite(greenLed2, HIGH);
    digitalWrite(yellowLed1, LOW);
    digitalWrite(yellowLed2, LOW);
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
  } 
  else if (potValue > 341 && potValue <= 682) {
    // Second level: Turn on the green and yellow LEDs.
    digitalWrite(greenLed1, HIGH);
    digitalWrite(greenLed2, HIGH);
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(yellowLed2, HIGH);
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
  } 
  else if (potValue > 682) {
    // Third level: Turn on all LEDs.
    digitalWrite(greenLed1, HIGH);
    digitalWrite(greenLed2, HIGH);
    digitalWrite(yellowLed1, HIGH);
    digitalWrite(yellowLed2, HIGH);
    digitalWrite(redLed1, HIGH);
    digitalWrite(redLed2, HIGH);
  }

  // A small delay to prevent the loop from running too fast,
  // making the serial output readable and stabilizing the response.
  delay(100);
}