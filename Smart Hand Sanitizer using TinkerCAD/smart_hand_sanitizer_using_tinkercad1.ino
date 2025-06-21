// Include the library for the servo motor
#include <Servo.h>

// Define the pins for the Ultrasonic Sensor
const int trigPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

// Create a servo object to control the servo motor
Servo Myservo; 

void setup() {
  // Start the serial communication at 9600 baud rate
  Serial.begin(9600); 

  // Attach the servo on pin 5 to the servo object
  Myservo.attach(5); // Signal Pin of Servo

  // Set the trigger pin as an OUTPUT
  pinMode(trigPin, OUTPUT); 
  // Set the echo pin as an INPUT
  pinMode(echoPin, INPUT); 

  // Print a starting message to the Serial Monitor
  Serial.print(" Distance ");
  Serial.print(" Measurement ");
  delay(2000);
}

void loop() {
  // Declare variables for duration and distance in centimeters
  long duration, cm; 

  // --- Generate the trigger pulse ---
  // Set the trigger pin to LOW for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set the trigger pin to HIGH for 10 microseconds to send the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Keep the trig pin high for 10us
  // Set the trigger pin back to LOW
  digitalWrite(trigPin, LOW);
  // --- Trigger pulse ends ---

  // Read the echo pin. pulseIn() returns the duration of the pulse in microseconds.
  duration = pulseIn(echoPin, HIGH); // Taking input from echo pin

  // Convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  // Print the distance to the Serial Monitor
  Serial.print("Distance:");
  Serial.print(cm);
  Serial.print("cm");
  delay(100);
  
  // Check if an object is within 10cm
  if (cm >= 10) { // If distance is more than or equal to 10cm
    Myservo.write(0); // Set servo to neutral position (0 degrees)
  } 
  else { // If distance is less than 10cm
    Myservo.write(90); // Turn the servo to dispense sanitizer (90 degrees)
  }

  Serial.println();
  delay(100);
}

// Custom function to convert the pulse duration (microseconds) to distance (centimeters)
long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so we divide by 2 to get the distance to the object.
  return microseconds / 29 / 2; 
}