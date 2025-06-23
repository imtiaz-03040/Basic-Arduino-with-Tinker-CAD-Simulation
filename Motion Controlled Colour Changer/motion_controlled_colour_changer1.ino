// Define the pins for the components
const int buzzer_pin = 3;       // Buzzer is connected to digital pin 3
const int pir_pin = 7;          // PIR sensor signal is connected to digital pin 7
const int red_light_pin = 9;    // Red pin of the RGB LED is connected to PWM pin 9
const int green_light_pin = 11; // Green pin of the RGB LED is connected to PWM pin 11
const int blue_light_pin = 10;  // Blue pin of the RGB LED is connected to PWM pin 10

void setup() {
  // Set the pin modes for each component
  pinMode(pir_pin, INPUT);         // PIR sensor is an input device
  pinMode(buzzer_pin, OUTPUT);       // Buzzer is an output device
  pinMode(red_light_pin, OUTPUT);    // Red LED is an output device
  pinMode(green_light_pin, OUTPUT);  // Green LED is an output device
  pinMode(blue_light_pin, OUTPUT);   // Blue LED is an output device
  
  // Initially, turn all outputs off (LOW)
  digitalWrite(buzzer_pin, LOW);
  digitalWrite(red_light_pin, LOW);
  digitalWrite(green_light_pin, LOW);
  digitalWrite(blue_light_pin, LOW);
}

void loop() {
  // Check the state of the PIR sensor
  if (digitalRead(pir_pin) == HIGH) {
    // If motion is detected...
    
    // Turn the buzzer on
    digitalWrite(buzzer_pin, HIGH);
    
    // Set the RGB LED color to Blue
    RGB_color(0, 0, 255); // R=0, G=0, B=255
    
    // This empty while loop holds the program here as long as motion is still detected.
    // The buzzer and blue light will remain on.
    while (digitalRead(pir_pin) == HIGH);
    
  } else {
    // If no motion is detected...
    
    // Turn the buzzer off
    digitalWrite(buzzer_pin, LOW);
    
    // Set the RGB LED color to Magenta
    RGB_color(255, 0, 255); // R=255, G=0, B=255
  }
}

// Helper function to set the RGB LED color
void RGB_color(int red_value, int green_value, int blue_value) {
  // Use analogWrite to set the intensity of each color (0-255)
  analogWrite(red_light_pin, red_value);
  analogWrite(green_light_pin, green_value);
  analogWrite(blue_light_pin, blue_value);
}