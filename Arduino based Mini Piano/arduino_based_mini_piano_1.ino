// Frequencies of different keys
#define T_C 262
#define T_D 294
#define T_E 329
#define T_F 392
#define T_G 440
#define T_A 493
#define T_B 523

// Connect to the pins of the Arduino
const int C = 2;
const int D = 4;
const int E = 6;
const int F = 7;
const int G = 9;
const int A = 11;
const int B = 12;

// Connect Speaker
const int Buzz = 13;

void setup() {
  // Pull-Up for the push button
  pinMode(C, INPUT);
  digitalWrite(C, HIGH); 
  
  pinMode(D, INPUT);
  digitalWrite(D, HIGH);
  
  pinMode(E, INPUT);
  digitalWrite(E, HIGH);
  
  pinMode(F, INPUT);
  digitalWrite(F, HIGH);
  
  pinMode(G, INPUT);
  digitalWrite(G, HIGH);
  
  pinMode(A, INPUT);
  digitalWrite(A, HIGH);
  
  pinMode(B, INPUT);
  digitalWrite(B, HIGH);
}

void loop() {
  // To get the desired tone from the speaker
  while (digitalRead(C) == LOW) {
    tone(Buzz, T_C);
  }

  while (digitalRead(D) == LOW) {
    tone(Buzz, T_D);
  }

  while (digitalRead(E) == LOW) {
    tone(Buzz, T_E);
  }

  while (digitalRead(F) == LOW) {
    tone(Buzz, T_F);
  }

  while (digitalRead(G) == LOW) {
    tone(Buzz, T_G);
  }

  while (digitalRead(A) == LOW) {
    tone(Buzz, T_A);
  }

  while (digitalRead(B) == LOW) {
    tone(Buzz, T_B);
  }

  noTone(Buzz);
}

// Notes for Twinkle Twinkle Little Star
// CC GG AA G
// FF EE DD C
// G G FF E E D
// G G FF E E D
// CC GG AA G
// FF EE DD C