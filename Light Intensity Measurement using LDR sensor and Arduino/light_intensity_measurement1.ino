// Light Intensity Measurement using LDR

const int ldrPin = A0;  // LDR connected to analog pin A0
int ldrValue = 0;       // Variable to store the LDR value

void setup() {
  Serial.begin(9600);   // Start serial communication at 9600 bps
}

void loop() {
  ldrValue = analogRead(ldrPin); // Read the analog value from the LDR
  Serial.print("Light Intensity: ");
  Serial.println(ldrValue);      // Print the value to Serial Monitor

  delay(500);  // Wait for half a second before next reading
}

