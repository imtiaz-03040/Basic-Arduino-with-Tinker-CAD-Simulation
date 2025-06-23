/*
  This program blinks the LEDs in a traffic light sequence when a pushbutton is pressed.
  It is based on the "Traffic Light Demo Project on Arduino" video.

  Circuit Connections:
  - Red LED: Digital Pin 13 -> 220 Ohm Resistor -> LED -> GND
  - Yellow LED: Digital Pin 12 -> 220 Ohm Resistor -> LED -> GND
  - Green LED: Digital Pin 8 -> 220 Ohm Resistor -> LED -> GND
  - Pushbutton:
    - One leg to 5V
    - Other leg to Digital Pin 2
    - A 1000 Ohm (1k) pull-down resistor from Digital Pin 2 to GND
*/

// Global variable to store the current state of the button
int buttonState = 0;

// Define constants for the pin numbers. This makes the code easier to read.
const int buttonPin = 2;    // The pin the pushbutton is connected to
const int ledOne = 13;      // The pin for the first LED (Red)
const int ledTwo = 12;      // The pin for the second LED (Yellow)
const int ledThree = 8;     // The pin for the third LED (Green)

// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize the LED pins as outputs
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  
  // Initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  
  // Start serial communication at 9600 bits per second for printing messages
  Serial.begin(9600);
}

// The loop function runs over and over again forever
void loop() {
  // Read the state of the pushbutton (HIGH or LOW)
  buttonState = digitalRead(buttonPin);

  // Check if the pushbutton is pressed.
  // If buttonState is 1 (HIGH), it means the button is being pressed.
  if (buttonState == 1) {
    
    // --- Red Light Sequence ---
    digitalWrite(ledOne, 1);        // Turn the red LED on (1 is the same as HIGH)
    Serial.print("STOP\n");         // Print "STOP" to the serial monitor followed by a new line
    delay(2000);                    // Wait for 2000 milliseconds (2 seconds)
    digitalWrite(ledOne, 0);        // Turn the red LED off (0 is the same as LOW)
    delay(500);                     // Wait for 500 milliseconds

    // --- Yellow Light Sequence ---
    digitalWrite(ledTwo, 1);        // Turn the yellow LED on
    Serial.print("GET READY\n");    // Print "GET READY"
    delay(2000);                    // Wait for 2 seconds
    digitalWrite(ledTwo, 0);        // Turn the yellow LED off
    delay(500);                     // Wait for 500 milliseconds

    // --- Green Light Sequence ---
    digitalWrite(ledThree, 1);      // Turn the green LED on
    Serial.print("BYE\n");          // Print "BYE" (as shown in the video's code)
    delay(2000);                    // Wait for 2 seconds
    digitalWrite(ledThree, 0);      // Turn the green LED off
  }
}