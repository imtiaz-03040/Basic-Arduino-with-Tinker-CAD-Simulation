// Initialize a variable to store the sensor's value
int sensorValue = 0;

void setup()
{
  // Set pin A0 as an input to read from the photoresistor (LDR)
  pinMode(A0, INPUT);
  
  // Start serial communication at 9600 bits per second for monitoring
  Serial.begin(9600);
  
  // Set digital pin 9 as an output to control the LED
  pinMode(9, OUTPUT);
}

void loop()
{
  // Read the analog value from the photoresistor connected to pin A0
  sensorValue = analogRead(A0);
  
  // Print the raw sensor value to the Serial Monitor
  Serial.println(sensorValue);
  
  // Map the sensor's input range (0-1023) to the LED's output range (0-255)
  // and write this value to the LED to control its brightness
  analogWrite(9, map(sensorValue, 0, 1023, 0, 255));
  
  // Wait for 100 milliseconds before the next reading
  delay(100);
}
