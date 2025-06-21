#include <Servo.h> // Correct case

Servo myservo;

#define trigPin 2
#define echoPin 3

float duration;
float distance;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  if (distance >= 4 || distance <= 2) {
    Serial.println("OutOfRange");
    myservo.detach();
  } else {
    myservo.attach(9); 
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(1000);
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(500);
    Serial.print("Distance:");
    Serial.println(distance);
    myservo.detach();
  }

  delay(50);
}
