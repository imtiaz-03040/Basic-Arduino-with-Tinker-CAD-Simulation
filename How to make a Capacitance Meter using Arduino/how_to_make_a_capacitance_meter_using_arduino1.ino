/*
 *  Capacitance Meter
 *  Measures capacitance by timing the charge of an RC circuit.
 *  The time it takes for the capacitor to charge to 63.2% of the
 *  supply voltage is the RC time constant (τ).
 *  Capacitance (C) is then calculated as C = τ / R.
 */

// -- Initialize Pins --
// Pin to read the capacitor's voltage
int analogPin = 0;      
// Pin to charge the capacitor (connects to the charging resistor)
int chargePin = 8;      
// Pin to discharge the capacitor (connects to the discharge resistor)
// This pin helps speed up the discharging process.
int dischargePin = 9;   

// -- Initialize Resistor --
// Value of the KNOWN charging resistor in Ohms.
int resistorValue = 10000;

// -- Initialize Timer --
unsigned long startTime;
unsigned long elapsedTime;

// -- Initialize Capacitance Variables --
float microFarads;
float nanoFarads;

void setup() {
  // Set the chargePin as an OUTPUT
  pinMode(chargePin, OUTPUT);
  // Initially, make sure the capacitor is not charging
  digitalWrite(chargePin, LOW);

  // Initialize serial communication to print data to the serial monitor
  Serial.begin(9600); 
}

void loop() {
  // Start charging the capacitor by setting the charge pin to HIGH
  digitalWrite(chargePin, HIGH); 
  // Record the starting time in milliseconds
  startTime = millis();

  // Wait until the capacitor's voltage reaches 63.2% of its total voltage.
  // Arduino's analogRead() maps 0-5V to an integer of 0-1023.
  // 63.2% of 1023 is ~648. A value of 610 is used here to compensate for small delays.
  while(analogRead(analogPin) < 610) { 
    // Do nothing until the capacitor reaches the threshold voltage
  }

  // Determine how much time it took to charge the capacitor (this is our time constant, τ)
  elapsedTime = millis() - startTime;
  
  // Calculate the capacitance in microFarads using the formula C = τ / R.
  // We use (float) to ensure floating-point division for accuracy.
  // We multiply by 1000 because elapsedTime is in milliseconds.
  microFarads = ((float)elapsedTime / resistorValue) * 1000;
  
  // Print the results to the Serial Monitor
  Serial.print(elapsedTime);
  Serial.print(" mS   ");

  // Determine if the units should be microFarads or nanoFarads and print accordingly
  if (microFarads > 1) {
    Serial.print((long)microFarads);
    Serial.println(" microFarads");
  } else {
    // If the value is less than 1 µF, convert to nanoFarads for better readability
    nanoFarads = microFarads * 1000.0;
    Serial.print((long)nanoFarads);
    Serial.println(" nanoFarads");
  }
  
  delay(500); // A small delay before the next measurement cycle

  // Stop charging the capacitor
  digitalWrite(chargePin, LOW); 
  
  // Allow the capacitor to discharge through the discharge resistor
  pinMode(dischargePin, OUTPUT); 
  digitalWrite(dischargePin, LOW); 
  while(analogRead(analogPin) > 0) {
    // Do nothing until the capacitor is fully discharged
  }
  
  // Set the discharge pin to INPUT to prevent it from interfering with the next charge cycle
  pinMode(dischargePin, INPUT); 
}
