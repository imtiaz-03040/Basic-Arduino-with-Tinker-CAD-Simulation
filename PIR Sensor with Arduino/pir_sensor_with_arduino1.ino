// Define the pins for the PIR sensor and the LED
#define pir 13
#define led 12

// A boolean variable to store the reading from the PIR sensor
bool pir_val = 0;

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Set the LED pin as an output
  pinMode(led, OUTPUT);
  
  // Set the PIR sensor pin as an input
  pinMode(pir, INPUT);
}

void loop() {
  // Read the state of the PIR sensor
  pir_val = digitalRead(pir);

  // Check if the sensor has detected motion (output is HIGH)
  if (pir_val == HIGH) {
    // Print a message to the Serial Monitor
    Serial.println("Motion Detected");
    // Turn the LED on
    digitalWrite(led, HIGH);
  }
  else {
    // Print a different message if no motion is detected
    Serial.println("No Motion Detected");
    // Turn the LED off
    digitalWrite(led, LOW);
  }
}