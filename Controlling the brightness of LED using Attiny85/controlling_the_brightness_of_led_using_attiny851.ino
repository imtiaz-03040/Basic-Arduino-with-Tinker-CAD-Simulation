/*
  Controlling LED Brightness with a Potentiometer using ATtiny85
  
  This code reads an analog input from a potentiometer connected to pin A3 (PB3),
  and uses that value to control the brightness of an LED connected to pin 0 (PB0)
  using Pulse-Width Modulation (PWM).

  Circuit Connections (ATtiny85):
  - VCC pin to 3V power supply.
  - GND pin to ground.
  - Pin 0 (PB0) -> Anode of the LED.
  - Pin A3 (PB3) -> Wiper (middle pin) of the potentiometer.
  
  LED Connections:
  - Anode -> ATtiny85 Pin 0 (PB0).
  - Cathode -> 47 Ohm Resistor -> Ground.
  
  Potentiometer Connections:
  - One outer pin -> 3V power supply.
  - Other outer pin -> Ground.
  - Wiper (middle pin) -> ATtiny85 Pin A3 (PB3).
*/

// Define the pins for the LED and the potentiometer (sensor).
const int ledPin = 0;      // ATtiny85 physical pin 5 (PB0), supports PWM
const int sensorPin = A3;  // ATtiny85 physical pin 2 (PB3/ADC3)

// Variable to store the value from the potentiometer.
int pot_value = 0;

void setup() {
  // Set the LED pin as an output.
  pinMode(ledPin, OUTPUT);
  
  // Set the potentiometer pin as an input. 
  // (This is not strictly necessary for analogRead but is good practice).
  pinMode(sensorPin, INPUT);
}

void loop() {
  // 1. Read the analog value from the potentiometer.
  // The value will be between 0 and 1023.
  pot_value = analogRead(sensorPin);
  
  // 2. Map the 10-bit analog input value (0-1023) to an 
  // 8-bit PWM output value (0-255).
  pot_value = map(pot_value, 0, 1023, 0, 255);
  
  // 3. Write the mapped value to the LED pin to control its brightness.
  // A value of 0 is off, 255 is full brightness.
  analogWrite(ledPin, pot_value);
}