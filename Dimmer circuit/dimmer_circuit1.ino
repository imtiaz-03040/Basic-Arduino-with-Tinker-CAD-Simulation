/*
  LED Dimmer Circuit
  Controls the brightness of an LED using a potentiometer.
*/

// Declare the pins used for the potentiometer and the LED
int potPin = A0;      // Potentiometer is connected to analog pin A0
int LEDPin = 9;       // LED is connected to digital pin 9 (a PWM pin)

// Declare variables to store the values from the potentiometer and for the LED
int readValue;        // Stores the raw analog value from the potentiometer (0-1023)
int writeValue;       // Stores the mapped value for the LED brightness (0-255)

void setup() {
  // Set the potentiometer pin as an input
  pinMode(potPin, INPUT);
  
  // Set the LED pin as an output
  pinMode(LEDPin, OUTPUT);
  
  // Initialize serial communication at 9600 bits per second for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the potentiometer
  readValue = analogRead(potPin);
  
  // Map the input value (0-1023) to the PWM output range (0-255)
  // The formula used is: (output_max / input_max) * input_value
  writeValue = (255. / 1023.) * readValue;
  
  // Write the mapped value to the LED pin to set its brightness
  analogWrite(LEDPin, writeValue);
  
  // Print the current brightness value to the Serial Monitor for debugging
  Serial.print("You are writing a value of ");
  Serial.println(writeValue);
}