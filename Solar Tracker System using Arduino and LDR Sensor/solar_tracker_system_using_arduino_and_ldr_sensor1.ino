// Include the Servo library to control the servo motors
#include <Servo.h> 

// --- Servo Definitions ---

// Horizontal Servo
Servo horizontal;         // Create a servo object for horizontal movement
int servoh = 180;         // Initial horizontal servo position (degrees)
int servohLimitHigh = 175; // Upper limit for horizontal servo
int servohLimitLow = 5;   // Lower limit for horizontal servo

// Vertical Servo
Servo vertical;           // Create a servo object for vertical movement
int servov = 45;          // Initial vertical servo position (degrees)
int servovLimitHigh = 60; // Upper limit for vertical servo
int servovLimitLow = 1;   // Lower limit for vertical servo

// --- LDR Pin Definitions ---
// Assign analog pins to each LDR sensor
int ldrlt = A0; // LDR top-left
int ldrrt = A2; // LDR top-right
int ldrld = A1; // LDR down-left
int ldrrd = A3; // LDR down-right

void setup() {
  // Attach the servo objects to their corresponding digital PWM pins
  horizontal.attach(9);
  vertical.attach(10);
  
  // Set the servos to their initial positions
  horizontal.write(servoh);
  vertical.write(servov);
  
  // Wait for 2.5 seconds to allow servos to reach their initial position
  delay(2500);
}

void loop() {
  // --- Read LDR Sensor Values ---
  // Read the analog value from each of the four LDRs
  int lt = analogRead(ldrlt); // top-left
  int rt = analogRead(ldrrt); // top-right
  int ld = analogRead(ldrld); // down-left
  int rd = analogRead(ldrrd); // down-right
  
  // --- Define Control Parameters ---
  int dtime = 10; // delay time in milliseconds for smooth movement
  int tol = 90;   // tolerance value to prevent jittering when light is balanced

  // --- Calculate Light Averages and Differences ---
  // Calculate the average light values for each side
  int avt = (lt + rt) / 2; // average of top LDRs
  int avd = (ld + rd) / 2; // average of down LDRs
  int avl = (lt + ld) / 2; // average of left LDRs
  int avr = (rt + rd) / 2; // average of right LDRs

  // Calculate the difference in light between opposite sides
  int dvert = avt - avd;   // difference between top and down
  int dhoriz = avl - avr; // difference between left and right

  // --- Vertical Servo Control ---
  // Check if the vertical light difference is outside the tolerance range
  if ((-1*tol > dvert || dvert > tol)) {
    // If the top is brighter than the bottom
    if (avt > avd) {
      servov = ++servov; // Increment vertical servo position
      // Constrain the servo to its upper limit
      if (servov > servovLimitHigh) { 
        servov = servovLimitHigh;
      }
    }
    // If the bottom is brighter than the top
    else if (avd > avt) {
      servov = --servov; // Decrement vertical servo position
      // Constrain the servo to its lower limit
      if (servov < servovLimitLow) {
        servov = servovLimitLow;
      }
    }
    vertical.write(servov); // Move the vertical servo to the new position
  }

  // --- Horizontal Servo Control ---
  // Check if the horizontal light difference is outside the tolerance range
  if ((-1*tol > dhoriz || dhoriz > tol)) {
    // If the left is brighter than the right
    if (avl > avr) {
      servoh = --servoh; // Decrement horizontal servo position
      // Constrain the servo to its lower limit
      if (servoh < servohLimitLow) {
        servoh = servohLimitLow;
      }
    }
    // If the right is brighter than the left
    else if (avr > avl) {
      servoh = ++servoh; // Increment horizontal servo position
      // Constrain the servo to its upper limit
      if (servoh > servohLimitHigh) {
        servoh = servohLimitHigh;
      }
    }
    // If the light is perfectly balanced horizontally, wait for 5 seconds
    else if (avl == avr) {
      delay(5000);
    }
    horizontal.write(servoh); // Move the horizontal servo to the new position
  }
  
  // Add a small delay for smoother operation
  delay(dtime); 
}