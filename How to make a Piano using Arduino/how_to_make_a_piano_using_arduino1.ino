// Define the pins for the 8 pushbuttons
int but1 = 2;
int but2 = 3;
int but3 = 4;
int but4 = 5;
int but5 = 6;
int but6 = 7;
int but7 = 8;
int but8 = 9;

// Define the pin for the buzzer (piezo)
int buzzer = 13;

void setup() {
  // Set all the button pins as INPUTs
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);
  pinMode(but4, INPUT);
  pinMode(but5, INPUT);
  pinMode(but6, INPUT);
  pinMode(but7, INPUT);
  pinMode(but8, INPUT);

  // Set the buzzer pin as an OUTPUT
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Read the digital value from each button
  int b1 = digitalRead(but1);
  int b2 = digitalRead(but2);
  int b3 = digitalRead(but3);
  int b4 = digitalRead(but4);
  int b5 = digitalRead(but5);
  int b6 = digitalRead(but6);
  int b7 = digitalRead(but7);
  int b8 = digitalRead(but8);

  // Check if the first button is pressed and play a tone
  if (b1 == 1) {
    tone(buzzer, 300, 100);
  }

  // Check if the second button is pressed and play a tone
  if (b2 == 1) {
    tone(buzzer, 400, 100);
  }

  // Check if the third button is pressed and play a tone
  if (b3 == 1) {
    tone(buzzer, 500, 100);
  }

  // Check if the fourth button is pressed and play a tone
  if (b4 == 1) {
    tone(buzzer, 600, 100);
  }

  // Check if the fifth button is pressed and play a tone
  if (b5 == 1) {
    tone(buzzer, 700, 100);
  }

  // Check if the sixth button is pressed and play a tone
  if (b6 == 1) {
    tone(buzzer, 800, 100);
  }

  // Check if the seventh button is pressed and play a tone
  if (b7 == 1) {
    tone(buzzer, 900, 100);
  }

  // Check if the eighth button is pressed and play a tone
  if (b8 == 1) {
    tone(buzzer, 1000, 100);
  }

  // Add a small delay to prevent multiple readings from a single press
  delay(10);
}