
// 
// Define pins for the three shift register control lines.
//
const byte LATCH_PIN = 2; // labeled "strobe"
const byte DATA_PIN  = 3;
const byte CLOCK_PIN = 4;

//
// Define the bit patterns for the 7-segment display. 
//
// MSB           LSB
//  x g f e d c b a
//
// a-g = segment name
// x   = decimal point
//
const byte ALL_ON = 0xff;
const byte ZERO   = 0x3f;
const byte ONE    = 0x06;
const byte TWO    = 0x5b;
const byte THREE  = 0x4f;
const byte FOUR   = 0x66;
const byte FIVE   = 0x6d;
const byte SIX    = 0x7d;
const byte SEVEN  = 0x07;
const byte EIGHT  = 0x7f;
const byte NINE   = 0x6f;

//
// Clock a pin (Toggle it on and off)
//
// The Arduino was clocking the line
// too fast for the shift register, so
// I added dummy operations to insert
// a small delay. 
//
// 16MHz Arduino = 62.5nS per clock tick. 
//
void clock(byte aPinNumber)
{
    byte i=0; 
    
    i++; // delay
    digitalWrite(aPinNumber, HIGH);
    i++; // delay 
    digitalWrite(aPinNumber, LOW);
}

//
// Send a bit pattern to the shift register, 
// most significant byte first.
//
void send_byte(byte aValue)
{
  // Present the value to the shift register,
  // then cycle the clock line to push it.
  for(byte i=0; i<8; i++)
  {
    digitalWrite(DATA_PIN, aValue & 0x80 ? HIGH : LOW);
    clock(CLOCK_PIN);
    aValue <<= 1;
  }

  // Latch the eight bits that were sent. 
  clock(LATCH_PIN);
}

//
// Send the right bit pattern to the
// shift register. 
//
void send_decimal_digit(byte aValue)
{
  // The % 10 here is for safety.
  switch(aValue % 10)
  {
    case 0: send_byte(ZERO); break;
    case 1: send_byte(ONE); break;
    case 2: send_byte(TWO); break;
    case 3: send_byte(THREE); break;
    case 4: send_byte(FOUR); break;
    case 5: send_byte(FIVE); break;
    case 6: send_byte(SIX); break;
    case 7: send_byte(SEVEN); break;
    case 8: send_byte(EIGHT); break;
    case 9: send_byte(NINE); break;
  }
}

void setup()
{
  // Initialize the shift register pins.
  pinMode(LATCH_PIN, OUTPUT);   
  pinMode(DATA_PIN, OUTPUT);   
  pinMode(CLOCK_PIN, OUTPUT); 
  
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);    
}

// The value to display.
byte display_value = 0;

// Count one number per second.
void loop()
{
  send_decimal_digit(display_value % 10);
  display_value++;
  delay(1000);
}

