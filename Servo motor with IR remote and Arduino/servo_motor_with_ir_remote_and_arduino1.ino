#include <IRremote.h>
#include <Servo.h>

// Define the pin for the IR receiver
int RECV_PIN = 5;

// Create an IR receiver object
IRrecv irrecv(RECV_PIN);

// Create an object to store the decoded results
decode_results results;

// Create a servo object
Servo myservo;

// Variable to store the servo position, initialized to 0
int pos = 0;

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  
  // Start the IR receiver
  irrecv.enableIRIn(); 
  Serial.println("Enabled IRin");
  
  // Attach the servo to digital pin 3
  myservo.attach(3);
  
  // Set the servo to its initial position
  myservo.write(pos);
}

void loop() {
  // Check if an IR signal has been received and decoded
  if (irrecv.decode(&results)) {
    
    // Print the decoded value to the Serial Monitor (in decimal format)
    Serial.println(results.value, DEC);

    // --- Control logic based on the received IR code ---

    // If button '1' is pressed (code: 16682903)
    if (results.value == 16682903) {
      myservo.write(45);  // Move servo to 45 degrees
      delay(1000);        // Wait for 1 second
    } 
    // If button '2' is pressed (code: 16615543)
    else if (results.value == 16615543) {
      myservo.write(90);  // Move servo to 90 degrees
      delay(1000);        // Wait for 1 second
    } 
    // If button '3' is pressed (code: 16599223)
    else if (results.value == 16599223) {
      myservo.write(135); // Move servo to 135 degrees
      delay(2000);        // Wait for 2 seconds
    } 
    // If button '4' is pressed (code: 16591063)
    else if (results.value == 16591063) {
      myservo.write(180); // Move servo to 180 degrees
      delay(2000);        // Wait for 2 seconds
    } 
    else {
      // This block is for any other button press (currently does nothing)
    }

    // After the delay, return the servo to the initial position (0 degrees)
    myservo.write(0);
    
    // Resume listening for the next IR signal
    irrecv.resume();
    
    // A small delay before the next loop
    delay(100);
  }
}