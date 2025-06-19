// Declare variables
int temp = A0;              // The temperature sensor is connected to analog pin A0
float temp_celsius;         // Variable to store temperature in Celsius
float Voltage;              // Variable to store the voltage reading from the sensor
float analog_reading;       // Variable to store the raw analog value (0-1023)
float temp_far;             // Variable to store temperature in Fahrenheit

// The setup function runs once when you press reset or power the board
void setup()
{
  pinMode(A0, INPUT);       // Set the temperature sensor pin as an input
  Serial.begin(9600);       // Initialize serial communication at 9600 baud rate
}

// The loop function runs over and over again forever
void loop()
{
  // 1. Read the raw analog value from the sensor
  analog_reading = analogRead(A0);
  Serial.print("Analog reading:"); // Print a label to the Serial Monitor
  Serial.println(analog_reading);  // Print the raw analog value

  // 2. Convert the analog reading to a voltage reading
  // converting analog reading to voltage
  // We divide by 1024 because the analog reading is between 0 and 1023
  // 5 because the supply is 5 Volts;
  Voltage = analog_reading * 5.0 / 1024.0;
  Serial.print("Voltage reading:"); // Display Voltage
  Serial.println(Voltage);

  // 3. Convert voltage to temperature in Celsius
  // reading in celsius;
  // converting from 10 mv per degree with 0.5V offset
  temp_celsius = 100 * (Voltage - 0.5);
  Serial.print("Celsius reading: ");
  Serial.print(temp_celsius);
  Serial.println(" C");
  
  // 4. Convert Celsius to Fahrenheit
  temp_far = (temp_celsius * 9.0 / 5.0) + 32;
  Serial.print("Fahrenheit reading: ");
  Serial.print(temp_far);
  Serial.println(" F");

  // Give a delay of 3 seconds before repeating the loop
  delay(3000); 
  Serial.println(); // Add a blank line for readability
}