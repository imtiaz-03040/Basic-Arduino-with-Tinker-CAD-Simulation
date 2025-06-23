// Include the LiquidCrystal library to interact with the LCD
#include <LiquidCrystal.h>

// Initialize the LiquidCrystal library with the numbers of the interface pins
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Declare variables to store temperature readings
int degree;         // Stores the raw analog reading from the sensor (0-1023)
double realdegree;  // Stores the calculated temperature value

// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Print a startup message to the LCD on the first line
  lcd.setCursor(0, 0);
  lcd.print("Today's Temp:");
}

// The loop function runs repeatedly
void loop() {
  // Read the analog input from the temperature sensor on pin A0
  degree = analogRead(A0);

  // --- Convert the analog reading to a temperature value ---
  realdegree = (double)degree / 1024.0; 
  realdegree = realdegree * 5.0; // Convert to voltage
  realdegree = realdegree - 0.5; // Subtract offset
  realdegree = realdegree * 100.0; // Convert to Celsius

  // Convert Celsius to Fahrenheit
  double fahrenheit = (realdegree * 9.0 / 5.0) + 32.0;

  // --- Display the temperature on the LCD ---

  // Clear the second line first
  lcd.setCursor(0, 1);
  lcd.print("                ");  // Clear all 16 characters

  // Move cursor back and print the temperature
  lcd.setCursor(0, 1);
  String output = String(fahrenheit, 2); // Two decimal places
  output += (char)223; // Degree symbol
  output += "F";

  lcd.print(output);

  // Wait a moment before the next reading
  delay(1000); // 1 second delay
}
