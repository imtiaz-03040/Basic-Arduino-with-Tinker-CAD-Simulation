/*
  Thermometer using ATtiny85 and TMP36 Sensor

  This code reads the temperature from a TMP36 sensor, converts the reading to
  Fahrenheit, and blinks an LED at different speeds to indicate the temperature range.

  - Cold (< 68°F): Fast blink
  - Normal (70-116°F): Medium blink
  - Hot (122-238°F): Slow blink
  - Very Hot (> 238°F) or in gaps: LED stays on solid

  This code is an accurate and functional representation of the code shown in the video.
*/

// --- Pin Definitions ---
// The LED is connected to digital pin 0 (PB0 on ATtiny85)
const int ledPin = 0;

// The TMP36 sensor's Vout pin is connected to analog pin A1 (PB2 on ATtiny85)
const int sensorPin = A1;

// --- Global Variables ---
// Variable to store the final temperature in Fahrenheit
double realdegree;

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 1. Read the raw analog value from the sensor (0-1023)
  int degree = analogRead(sensorPin);

  // 2. Convert the raw value to a voltage (0-5V).
  // We use 1024.0 to ensure floating-point math for accuracy.
  // The video's code assumes a 5V reference, which we replicate here.
  realdegree = (degree / 1024.0) * 5.0;

  // 3. Convert voltage to temperature in Celsius.
  // The TMP36 has a 0.5V offset at 0°C and a scale factor of 10mV/°C.
  // Formula: Temp (°C) = (Vout - 0.5) * 100
  realdegree = (realdegree - 0.5) * 100.0;

  // 4. Convert temperature from Celsius to Fahrenheit.
  // Formula: Temp (°F) = (Temp (°C) * 9/5) + 32
  realdegree = (realdegree * 9.0 / 5.0) + 32.0;

  // 5. Control the LED's blink rate based on the temperature in Fahrenheit.
  // The ranges and delays are taken directly from the video's code.

  // If the temperature is in the "cold" range...
  if (realdegree > -40 && realdegree < 68) {
    // ...blink the LED quickly.
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  // If the temperature is in the "normal" range...
  else if (realdegree > 70 && realdegree < 116) {
    // ...blink the LED at a medium speed.
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  // If the temperature is in the "hot" range...
  else if (realdegree > 122 && realdegree < 238) {
    // ...blink the LED slowly.
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
  // For all other temperatures (in the gaps or very hot)...
  else {
    // ...keep the LED on solid.
    digitalWrite(ledPin, HIGH);
  }
}