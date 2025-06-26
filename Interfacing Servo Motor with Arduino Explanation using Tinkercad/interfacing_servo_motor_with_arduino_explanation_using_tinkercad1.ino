#include<Servo.h>

// Create a servo object to control a servo
Servo Myservo;

// Variable to store the servo position
int pos;

void setup() {
  // Attaches the servo on pin 7 to the servo object
  Myservo.attach(7);
}

void loop() {
  // Goes from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos++) {
    Myservo.write(pos); // Tell servo to go to position in variable 'pos'
    delay(15);          // Waits 45ms for the servo to reach the position
  }
  
  delay(3000); // Wait for 3 seconds
  
  // Goes from 180 degrees back to 0 degrees
  for (pos = 180; pos >= 0; pos--) {
    Myservo.write(pos); // Tell servo to go to position in variable 'pos'
    delay(15);          // Waits 15ms for the servo to reach the position
  }
  
  delay(1000); // Wait for 1 second
}