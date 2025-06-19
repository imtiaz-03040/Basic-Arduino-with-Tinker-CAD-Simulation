#include <IRremote.h>

// Define the pins for the IR receiver and the LEDs
int IR_Recv = 12;      // IR Receiver Pin
int bluePin = 2;
int orangePin = 3;
int greenPin = 4;

// Create an instance of the IRrecv class
IRrecv irrecv(IR_Recv);

// Create an object to store the decoded results
decode_results results;

void setup()
{
  Serial.begin(9600);   // Start serial communication for debugging
  irrecv.enableIRIn();  // Start the receiver
  
  // Set the LED pins as outputs
  pinMode(bluePin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // Check if an IR signal has been received and decoded
  if (irrecv.decode(&results)) {
    
    // Print the received code to the Serial Monitor (for debugging)
    Serial.println(results.value); 
    
    // Use a switch statement to perform actions based on the received code
    switch (results.value) {
      case 16582903: // When you press the 1 button (Turn Blue LED ON)
        digitalWrite(bluePin, HIGH);
        break;
      case 16615543: // When you press the 2 button (Turn Blue LED OFF)
        digitalWrite(bluePin, LOW);
        break;
      case 16599223: // When you press the 3 button (Turn Orange LED ON)
        digitalWrite(orangePin, HIGH);
        break;
      case 16591063: // When you press the 4 button (Turn Orange LED OFF)
        digitalWrite(orangePin, LOW);
        break;
      case 16623703: // When you press the 5 button (Turn Green LED ON)
        digitalWrite(greenPin, HIGH);
        break;
      case 16607383: // When you press the 6 button (Turn Green LED OFF)
        digitalWrite(greenPin, LOW);
        break;
    }
    
    // Resume receiving the next value
    irrecv.resume(); 
  }
  
  // A small delay to prevent bouncing issues
  delay(10); 
}