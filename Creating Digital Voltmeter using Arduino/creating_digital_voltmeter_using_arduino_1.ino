// Include the LiquidCrystal library to control the LCD
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(RS, Enable, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define the values for the voltage divider resistors
// r1 is the resistor connected to the positive input voltage
// r2 is the resistor connected to ground
float r1 = 1000000.0; // 1 M-ohm resistor
float r2 = 10000.0;   // 10 K-ohm resistor

// Variable to store the final calculated input voltage
float input_voltage = 0.0;

// A temporary variable to hold the voltage reading at the Arduino's analog pin
float temp = 0.0;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Print a welcome message to the LCD.
  lcd.print("DIGITAL VOLTMETER");
  
  // (Optional) Initialize serial communication for debugging purposes
  Serial.begin(9600); 
}

void loop() {
  // Read the raw analog value (0-1023) from the A0 pin
  float analog_value = analogRead(A0);

  // --- Voltage Calculation ---

  // 1. Convert the raw analog value to the voltage at the A0 pin (0-5V)
  //    (raw_value * 5.0V_reference) / 1024_steps
  temp = (analog_value * 5.0) / 1024.0;
  
  // 2. Use the voltage divider formula to calculate the original input voltage
  //    V_in = V_out * (R1 + R2) / R2
  //    Here, V_out is 'temp' and V_in is 'input_voltage'.
  //    The formula is rearranged as: V_in = V_out / (R2 / (R1 + R2))
  input_voltage = temp / (r2 / (r1 + r2));

  // A small check to prevent showing tiny, erratic values when there's no input
  // If the voltage is very close to zero, just make it zero.
  if (input_voltage < 0.1) {
    input_voltage = 0.0;
  }
  
  // --- Displaying the Result ---

  // (Optional) Print the calculated voltage to the Serial Monitor for debugging
  Serial.print("Voltage = ");
  Serial.println(input_voltage);
  
  // Set the cursor to the first column of the second row (0-indexed)
  lcd.setCursor(0, 1);
  
  // Print the label "Voltage= " on the LCD
  lcd.print("Voltage= ");

  // Print the calculated voltage value
  lcd.print(input_voltage);
  
  // Add a small space to clear any leftover characters from previous readings
  lcd.print(" ");

  // Wait for 1000 milliseconds (1 second) before the next reading
  delay(1000);
}