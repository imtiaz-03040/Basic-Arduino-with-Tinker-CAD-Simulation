// Include the library for the LCD display
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// --- Variables ---
float voltage = 0.0;     // Variable to store the final calculated voltage
float temp = 0.0;        // Temporary variable to store the voltage read by the analog pin
float R1 = 90900.0;      // Value of the first resistor in the voltage divider (90.9kΩ)
float R2 = 10000.0;      // Value of the second resistor in the voltage divider (10kΩ)
int analog_value = 0;    // Variable to store the raw analog reading (0-1023)


// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize serial communication at 9600 bits per second for debugging
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("Digital voltmeter");
}


// The loop function runs over and over again forever
void loop() {
  // Read the input on analog pin 0
  analog_value = analogRead(A0);
  
  // Convert the analog value (from 0 - 1023) to a voltage (0 - 5V)
  temp = (analog_value * 5.0) / 1024.0;
  
  // Calculate the original voltage using the voltage divider formula
  // V_in = V_out * (R1+R2)/R2  which is equivalent to V_out / (R2/(R1+R2))
  voltage = temp / (R2 / (R1 + R2));
  
  // Set the cursor to column 0, line 1 (the second row)
  lcd.setCursor(0, 1);
  
  // Print the calculated voltage to the Serial Monitor
  Serial.println(voltage);
  
  // Print the calculated voltage to the LCD
  lcd.print(voltage);
  lcd.print(" V"); // Optional: add the unit "V" for Volts
  
  // Wait for 300 milliseconds before the next loop
  // to make the display more readable
  delay(300);
}