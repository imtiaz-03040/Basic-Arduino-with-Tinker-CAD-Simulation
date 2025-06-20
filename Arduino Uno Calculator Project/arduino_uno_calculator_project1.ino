#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

long first = 0;
long second = 0;
double total = 0;

char customKey;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

// Connect to the row and column pinouts of the keypad
byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {3, 2, 1, 0}; 

// Initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin(16, 2);       // Start LCD
  for (int i = 0; i < 3; i++); // This loop does nothing, likely a mistake in the original code
  lcd.setCursor(0, 0);
  lcd.print("Calculator");
  lcd.setCursor(0, 1);
  lcd.print("enter numbers");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
  customKey = customKeypad.getKey();
  switch (customKey) {
    case '0'...'9': // This keeps collecting the first value until an operator is pressed
      lcd.setCursor(0, 0);
      first = first * 10 + (customKey - '0');
      lcd.print(first);
      break;

    case '+':
      first = (total == 0 ? total : first); // Note: This logic is likely incorrect for the first operation.
      lcd.setCursor(0, 1);
      lcd.print("+");
      second = SecondNumber(); // Get the second number
      total = first + second;
      lcd.setCursor(0, 3);
      lcd.print(total);
      first = 0, second = 0; // Reset values for the next calculation
      break;

    case '-':
      first = (total == 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("-");
      second = SecondNumber();
      total = first - second;
      lcd.setCursor(0, 3);
      lcd.print(total);
      first = 0, second = 0;
      break;

    case '*':
      first = (total == 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("*");
      second = SecondNumber();
      total = first * second;
      lcd.setCursor(0, 3);
      lcd.print(total);
      first = 0, second = 0;
      break;

    case '/':
      first = (total == 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("/");
      second = SecondNumber();
      lcd.setCursor(0, 3);
      // Note: This ternary operator usage is unconventional and likely bugged.
      second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;
      lcd.print(total);
      first = 0, second = 0;
      break;

    case 'C':
      total = 0;
      lcd.clear();
      break;
  }
}

long SecondNumber() {
  while (1) {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(7, 0);
      lcd.print(second);
    }
    if (customKey == '=') {
      break;
    }
  }
  return second;
}