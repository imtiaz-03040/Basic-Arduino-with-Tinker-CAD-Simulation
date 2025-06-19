float temp;
float vout;
float vout1;
int LED = 13;
int gasSensor;
int piezo = 7;

void setup()
{
  pinMode(A0, INPUT);   // Gas sensor
  pinMode(A1, INPUT);   // Temperature sensor
  pinMode(LED, OUTPUT);
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  vout = analogRead(A1);                    // Read analog voltage (0-1023)
  vout1 = (vout * 5000.0) / 1023.0;         // Convert to millivolts
  temp = (vout1 - 500) / 10.0;              // Convert to Celsius (for LM35 or similar sensor)

  gasSensor = analogRead(A0);               // Read gas sensor

  if (temp >= 80)
  {
    digitalWrite(LED, HIGH);                // Turn on LED
  }
  else
  {
    digitalWrite(LED, LOW);                 // Turn off LED
  }

  if (gasSensor >= 100)                     // Threshold for gas detection (adjust as needed)
  {
    digitalWrite(piezo, HIGH);              // Turn on buzzer
  }
  else
  {
    digitalWrite(piezo, LOW);               // Turn off buzzer
  }

  Serial.print("Temperature (°C): ");
  Serial.print(temp);
  Serial.print("\tGas Sensor Reading: ");
  Serial.println(gasSensor);               // Add println instead of print()

  delay(1000);
}

    
  
