//  This program reads an encoder and sends the position over serial and formats to display correctly on the DM49C04 display.  
//  The encoder is a 5-pin rotary type with A and B connected to the fast inputs (DI6 and DI7) on the ClearCore. 
//  And the encoder switch is attached to DI8. 
//  The clearcore encoder card is not neccessary. 
//  The DM49C04 Display is connected to the COM port via three pins. 
//  Clearcore COM Pins 4 (gnd to GND), 5(TX to RXD) and 6 (5v to VCC).
//  The other COM pins are not used. 


const int encoderPinA = DI6; // Encoder input pin A
const int encoderPinB = DI7; // Encoder input pin B
const int encoderSwitch = DI8; // Encoder Switch Input


const int ENCODER_POS_INCREMENT = 0b1101;
const int ENCODER_POS_DECREMENT = 0b1110;

volatile int encoderPos = 0; // Encoder position
int lastEncoded = 0; // Last encoded position

void setup() {
  Serial0.begin(9600); // Begin serial communication on Serial0
  Serial1.begin(9600); // Begin serial communication on Serial1

  pinMode(encoderPinA, INPUT_PULLUP); // Set encoder pins as inputs
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderSwitch, INPUT_PULLUP);
  

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE); // Attach interrupts to encoder pins
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderSwitch), resetEncoder, RISING);

}

void loop() {
  int encoderPosCorrected = encoderPos;

  char encoderPosStr[5]; // Create a character array to hold the encoder position string
  sprintf(encoderPosStr, "#%04d", encoderPosCorrected); // Format the encoder position string

  Serial1.print(encoderPosStr); // Print the encoder position to Serial1
}

void updateEncoder() {
  static int lastStateA = LOW; // Last state of channel A

  int stateA = digitalRead(encoderPinA); // Current state of channel A
  int stateB = digitalRead(encoderPinB); // Current state of channel B

  if (stateA != lastStateA && stateA == HIGH) { // Detect a rising edge on channel A
    if (stateB == LOW) {
      encoderPos++; // If channel B is low, increment position
    } else {
      encoderPos--; // If channel B is high, decrement position
    }
  }

  lastStateA = stateA; // Store this state for next time
}

void resetEncoder() {
  encoderPos = 0;
}


