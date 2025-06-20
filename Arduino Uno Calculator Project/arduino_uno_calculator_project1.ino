#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// LCD RS, E, D4–D7 connected to pins 13, 12, 11, 10, 9, 8
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; 
byte colPins[COLS] = {3, 2, 1, 0};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Calculator state
String input = "";
long first = 0, second = 0;
char operation = '\0';
bool waitingForSecond = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Calculator");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '0' && key <= '9') {
      input += key;
      lcd.print(key);
    }
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (input.length() > 0) {
        first = input.toInt();
        input = "";
        operation = key;
        waitingForSecond = true;
        lcd.print(operation);
      }
    }
    else if (key == '=') {
      if (waitingForSecond && input.length() > 0) {
        second = input.toInt();
        input = "";
        double result = 0.0;
        bool valid = true;

        switch (operation) {
          case '+': result = first + second; break;
          case '-': result = first - second; break;
          case '*': result = first * second; break;
          case '/':
            if (second != 0) {
              result = (double)first / (double)second;
            } else {
              lcd.clear();
              lcd.print("Error: Div by 0");
              delay(2000);
              clearAll();
              return;
            }
            break;
          default:
            valid = false;
        }

        if (valid) {
          lcd.setCursor(0, 1);
          lcd.print("= ");
          lcd.print(result);
          delay(3000);
          clearAll();
        }
      }
    }
    else if (key == 'C') {
      clearAll();
    }
  }
}

void clearAll() {
  lcd.clear();
  input = "";
  first = 0;
  second = 0;
  operation = '\0';
  waitingForSecond = false;
}
