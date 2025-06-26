// Define the pins for the RGB LED
int rp = 11; // Red pin
int bp = 10; // Blue pin
int gp = 9;  // Green pin

void setup() {
  // Set the R, G, and B pins as outputs
  pinMode(rp, OUTPUT);
  pinMode(bp, OUTPUT);
  pinMode(gp, OUTPUT);
}

void loop() {
  // Display Red
  color(255, 0, 0); 
  delay(1000);

  // Display Green
  color(0, 255, 0); 
  delay(1000);

  // Display Blue
  color(0, 0, 255); 
  delay(1000);

  // Display White
  color(255, 255, 255); 
  delay(1000);
  
  // Turn the LED off
  color(0, 0, 0); 
  delay(1000);
}

// Custom function to set the color of the RGB LED
void color(unsigned char red, unsigned char green, unsigned char blue) {
  // Use analogWrite to set the PWM value for each color
  analogWrite(rp, red);
  analogWrite(gp, green);
  analogWrite(bp, blue);
}