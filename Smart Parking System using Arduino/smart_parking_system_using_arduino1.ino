// Include necessary libraries
#include <LiquidCrystal.h> // Library for LCD
#include <Servo.h>         // Library for Servo Motor

// Create Servo objects for the entry and exit gates
Servo S1; // Entry gate servo
Servo S2; // Exit gate servo

// Define the digital pins for the IR sensors
#define IR_Slot1 7   // Sensor for parking slot 1
#define IR_Slot2 8   // Sensor for parking slot 2
#define IR_entry 6   // Sensor at the entrance
#define IR_exit 13   // Sensor at the exit

// Variable to store the initial position of the servo motors (closed position)
int pos = 0;

// Initialize the LiquidCrystal library with the interface pins
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Attach the servo motors to their control pins
  S1.attach(10); // Attach entry servo to pin 10
  S2.attach(9);  // Attach exit servo to pin 9

  // Set the initial position of both servos to 0 degrees (closed)
  S1.write(pos);
  S2.write(pos);

  // Set the IR sensor pins as INPUT
  pinMode(IR_Slot1, INPUT);
  pinMode(IR_Slot2, INPUT);
  pinMode(IR_entry, INPUT);
  pinMode(IR_exit, INPUT);

  // Initialize the 16x2 LCD
  lcd.begin(16, 2);
  
  // Display a welcome message on the LCD
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1); // Move cursor to the second line
  lcd.print("System");
  delay(2000); // Wait for 2 seconds

  // Clear the screen and display the initial status of the parking slots
  lcd.clear();
  lcd.setCursor(0, 0); // Move cursor to the first line
  lcd.print("Slot 1 = A"); // A = Available
  lcd.setCursor(0, 1); // Move cursor to the second line
  lcd.print("Slot 2 = A"); // A = Available
  delay(2000); // Wait for 2 seconds
}

void loop() {
  // --- Check and Display Status for Parking Slot 1 ---
  if (digitalRead(IR_Slot1) == HIGH) { // HIGH means a car is detected
    lcd.setCursor(0, 0);
    lcd.print("Slot 1 = NA"); // NA = Not Available
  } else { // LOW means the slot is empty
    lcd.setCursor(0, 0);
    lcd.print("Slot 1 = A "); // A = Available (extra space to clear the 'NA')
  }

  // --- Check and Display Status for Parking Slot 2 ---
  if (digitalRead(IR_Slot2) == HIGH) { // HIGH means a car is detected
    lcd.setCursor(0, 1);
    lcd.print("Slot 2 = NA"); // NA = Not Available
  } else { // LOW means the slot is empty
    lcd.setCursor(0, 1);
    lcd.print("Slot 2 = A "); // A = Available (extra space to clear the 'NA')
  }

  // --- Control the Entry Gate ---
  if (digitalRead(IR_entry) == HIGH) { // If a car is at the entrance
    S1.write(pos + 90); // Rotate servo to 90 degrees to open the gate
  } else {
    S1.write(pos); // Keep the gate closed at 0 degrees
  }
  
  // --- Control the Exit Gate ---
  if (digitalRead(IR_exit) == HIGH) { // If a car is at the exit
    S2.write(pos + 90); // Rotate servo to 90 degrees to open the gate
  } else {
    S2.write(pos); // Keep the gate closed at 0 degrees
  }
}