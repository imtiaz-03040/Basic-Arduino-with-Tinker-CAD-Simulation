/*
  ===================================================================
  ==     Creating Voltmeter with ATtiny85 & 7-Segment Display      ==
  ===================================================================
  
  This code reads an analog voltage using the ATtiny85's ADC, scales
  the reading, and displays it on three 7-segment displays. A 74HC595 
  shift register is used to reduce the number of pins required to drive 
  the displays.
  
  This code is transcribed from the video and includes a logical correction
  in the main loop to ensure the display updates as intended.
*/

// Define a No-Operation instruction for creating very small delays.
#define NOP() asm("nop")

// Global variable to store the scaled voltage value.
long V = 0;

// Array for 7-segment display patterns (for Common Cathode displays).
// The value at each index corresponds to the segments needed to show that number.
// Segments are mapped as: (dp, g, f, e, d, c, b, a)
const unsigned char DIGS[11] = {
  // 0,    1,    2,    3,    4,    5,    6,    7,    8,    9,   (blank)
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00
};

// Array to hold the three digits that will be displayed.
unsigned char DISP[3] = {0, 0, 0};

// A volatile boolean flag used to signal the main loop to take a new reading.
// It's set by the timer interrupt.
volatile boolean flag = false;

// A counter to help time the flag signal.
volatile unsigned char period = 0;


// ------ FUNCTION: Transmit Data to Shift Register ------
// Sends one byte of data serially to the 74HC595.
void transmitByte(unsigned char bt) {
  // Loop through all 8 bits of the byte, sending the Most Significant Bit first.
  for (unsigned char j = 0; j < 8; j++) {
    // Set the data pin (PB0) high or low based on the current bit.
    if (bt & 0x80) { // Check if the MSB is 1.
      PORTB |= (1 << PB0);
    } else {
      PORTB &= ~(1 << PB0);
    }
    
    // Pulse the clock pin (PB1) to shift the bit into the register.
    PORTB |= (1 << PB1);
    NOP(); // A tiny delay to ensure the clock pulse is registered.
    PORTB &= ~(1 << PB1);

    // Shift the byte left to make the next bit the new MSB.
    bt <<= 1;
  }
}

// ------ FUNCTION: Read ADC Value ------
// Reads a 10-bit analog value from the specified ADC channel.
int adcRead(unsigned char ch) {
  // Select the ADC channel. Here it's always channel 0 (PB5).
  ADMUX = (ADMUX & 0xF0) | (ch & 0x0F);
  
  // Start a single ADC conversion.
  ADCSRA |= (1 << ADSC);

  // Wait until the conversion is complete (ADSC bit goes back to 0).
  while (ADCSRA & (1 << ADSC));

  // Return the 10-bit result.
  return ADC;
}


// ------ INTERRUPT SERVICE ROUTINE (ISR) ------
// This function runs automatically every time Timer0 compare match occurs (every ~4.8ms).
// It handles the multiplexing of the three 7-segment displays.
ISR(TIM0_COMPA_vect) {
  static unsigned char p = 0; // Remembers which display to light up next (0, 1, or 2).
  unsigned char s;

  // Turn off all displays by setting their driver pins (PB2, PB3, PB4) high.
  // This also latches the previously sent data into the 74HC595's storage.
  PORTB |= (1 << PB2) | (1 << PB3) | (1 << PB4);

  // Prepare the byte to send: get the pattern for the current digit.
  // Also, add the decimal point (0x80) if it's the middle display (p==1).
  s = DIGS[DISP[p]] | ((p == 1) ? 0x80 : 0x00);
  
  // Send the complete segment pattern to the shift register.
  transmitByte(s);
  
  // Turn on only the current display by pulling its driver pin low.
  PORTB &= ~(1 << (p + 2)); 

  // Move to the next display for the next interrupt cycle.
  p++;
  if (p == 3) {
    p = 0; // Loop back to the first display.
  }

  // This counter creates a longer time base. Every 25 interrupts (~120ms),
  // it sets the 'flag' to true, telling the main loop to perform a new voltage reading.
  period++;
  if (period == 25) {
    period = 0;
    flag = true;
  }
}


// ------ SETUP FUNCTION ------
// This runs once when the ATtiny85 powers on or is reset.
void setup() {
  // Set the system clock to its full speed by removing the prescaler.
  CLKPR = (1 << CLKPCE);
  CLKPR = 0x00;
  
  // --- Port B Pin Configuration ---
  // Set PB0, PB1, PB2, PB3, PB4 as outputs. PB5 remains an input for the ADC.
  DDRB = 0x1F; 
  // Set the initial state of output pins to low.
  PORTB = 0x00;

  // --- Timer/Counter 0 Configuration ---
  // Configure Timer0 for display multiplexing.
  // Mode: CTC (Clear Timer on Compare Match), with OCR0A defining the top value.
  TCCR0A = (1 << WGM01);
  // Set clock prescaler to 256. For an 8MHz clock, this is 31.25 kHz.
  TCCR0B = (1 << CS02);
  // Set the compare match value to 149 (0x95).
  // This results in an interrupt frequency of ~209 Hz, or a period of ~4.8 ms.
  OCR0A = 0x95;
  // Enable the Timer Compare A match interrupt.
  TIMSK |= (1 << OCIE0A);

  // --- ADC (Analog-to-Digital Converter) Configuration ---
  // Select ADC channel 0 (which corresponds to pin PB5).
  ADMUX = 0b00000000;
  // Enable the ADC and set its clock prescaler to 64.
  // This gives an ADC clock of 125 kHz from an 8MHz system clock, which is ideal.
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); 

  // Enable global interrupts to allow the timer ISR to run.
  sei();
}


// ------ MAIN LOOP ------
// This runs continuously after the setup function is complete.
void loop() {
  // Do nothing and wait until the ISR sets the flag.
  // This makes the main loop run only once every ~120ms.
  if (!flag) {
    return;
  }
  
  // Read the 10-bit value from the potentiometer (0-1023).
  V = adcRead(0);
  
  // Scale the 0-1023 ADC reading to a 0-159 value.
  // This represents the voltage from 0.0V to 15.9V.
  // We use 160L (long) to prevent overflow during the calculation.
  V = (V * 160L) / 1023L;
  
  // Break the scaled value into three separate digits for display.
  DISP[2] = V / 100;         // Tens digit (e.g., 1 in 15.9)
  DISP[1] = (V / 10) % 10;   // Ones digit (e.g., 5 in 15.9)
  DISP[0] = V % 10;          // Tenths digit (e.g., 9 in 15.9)

  // Reset the flag. The code will now wait for the ISR to set it again.
  flag = false;
}