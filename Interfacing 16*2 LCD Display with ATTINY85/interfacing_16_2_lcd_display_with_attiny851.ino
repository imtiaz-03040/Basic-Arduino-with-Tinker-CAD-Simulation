#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins.
// The pins correspond to the ATtiny85's physical pins used in the simulation.
// LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
// ATtiny Pins:     PB0,PB1,PB2,PB3,PB4,PB5
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD. This will appear on the first line.
  lcd.print("I am Imtiaz");
  
  // Set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0).
  lcd.setCursor(0, 1);
  
  // Print a message on the second line.
  lcd.print("hello");
}

void loop() {
  // Set the cursor to column 14 on line 1 (the second line).
  lcd.setCursor(14, 1);
  
  // Print the time in seconds since the simulation started.
  lcd.print(millis() / 1000);
  
  // A small delay to improve simulation performance.
  delay(100); 
}