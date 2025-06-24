/*
  Interfacing TMP36 with ATtiny85
  ---------------------------------
  This code reads the temperature from a TMP36 sensor connected to an ATtiny85.
  It then controls an RGB LED to display different colors based on the temperature.

  Circuit Connections:
  - ATtiny85 Pin 1 (PB5/RESET)
  - ATtiny85 Pin 2 (PB3)
  - ATtiny85 Pin 3 (PB4/A2) -> TMP36 Vout
  - ATtiny85 Pin 4 (GND)    -> TMP36 GND, RGB LED Cathode (via resistor), Battery (-)
  - ATtiny85 Pin 5 (PB0)    -> RGB LED Red Pin
  - ATtiny85 Pin 6 (PB1)    -> RGB LED Blue Pin
  - ATtiny85 Pin 7 (PB2)    -> RGB LED Green Pin
  - ATtiny85 Pin 8 (VCC)    -> TMP36 Power, Battery (+)
  - A 3V power source (like a coin cell) is used.
*/

// --- Global Constants and Variables ---

// Reference temperature (not actively used in the main logic, but good practice)
const float baselineTem = 20.0; 

// Pin assignments for ATtiny85
const int sensorPin = A2;     // TMP36 Vout is connected to Analog Pin 2 (PB4)
const int redPin = 0;         // RGB Red leg to Pin 0 (PB0)
const int bluePin = 1;        // RGB Blue leg to Pin 1 (PB1)
const int greenPin = 2;       // RGB Green leg to Pin 2 (PB2)

// Variable to store the temperature reading
float temp;

// --- Color Arrays ---
// Defines colors as boolean arrays [R, G, B]. 1 = ON, 0 = OFF.
bool yellow[] = {1, 1, 0};
bool red[]    = {1, 0, 0};
bool green[]  = {0, 1, 0};
bool blue[]   = {0, 0, 1};
bool white[]  = {1, 1, 1};
bool cyan[]   = {0, 1, 1};
bool off[]    = {0, 0, 0}; // Represents the LED being off

// --- Setup Function ---
// This runs once when the ATtiny85 is powered on or reset.
void setup() {
  // Set the R, G, B pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Note: The following lines are in the video's code but are unusual.
  // Pin 5 on ATtiny85 is the RESET pin. Using it as an output can
  // disable your ability to reprogram the chip via ISP.
  // It's included here for full accuracy with the video.
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH); 
}

// --- Main Loop ---
// This function runs repeatedly after setup() is finished.
void loop() {
  readSensor();       // Read the temperature from the sensor
  colorConditions();  // Set the LED color based on the temperature
}

// --- Custom Functions ---

// Function to set the LED color based on temperature conditions
void colorConditions() {
  if (temp <= 9)                  ledControlBlink(white); // Blink white if very cold
  if (temp >= 10 && temp <= 14.0) ledControl(white);      // Solid white for cold
  if (temp >= 15.0 && temp <= 20.0) ledControl(cyan);     // Solid cyan for cool
  if (temp >= 21 && temp <= 24)   ledControl(green);      // Solid green for comfortable
  if (temp >= 25 && temp <= 29)   ledControl(yellow);     // Solid yellow for warm
  if (temp >= 30)                 ledControl(red);        // Solid red for hot
}

// Takes a boolean array and sets the RGB pins accordingly
void ledControl(bool color[]) {
  digitalWrite(redPin,   color[0]);
  digitalWrite(greenPin, color[1]);
  digitalWrite(bluePin,  color[2]);
}

// Blinks the LED with a given color
void ledControlBlink(bool color[]) {
  ledControl(color); // Turn LED on to the specified color
  delay(500);
  ledControl(off);   // Turn LED off
  delay(500);
}

// Reads data from the TMP36 sensor and converts it to degrees Celsius
void readSensor() {
  // Read the analog value from the sensor (0-1023)
  int sensorVal = analogRead(sensorPin); 

  // Convert the analog reading to voltage.
  // Using 3.0V as the reference voltage from the coin cell battery.
  float voltage = (sensorVal / 1024.0) * 3.0;

  // Convert voltage to temperature in Celsius.
  // The formula for TMP36 is (Voltage - 0.5) * 100.
  temp = (voltage - 0.5) * 100;
}