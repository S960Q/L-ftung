#define encoderPinA 2
#define encoderPinB 3

volatile unsigned int encoderPos = 0;  // a counter for the dial
unsigned int lastReportedPos = 1;   // change management
static boolean rotating = false;      // debounce management

// interrupt service routine vars
boolean A_set = false;
boolean B_set = false;


void setup() {

    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);

    digitalWrite(encoderPinA, HIGH);  // turn on pullup resistors
    digitalWrite(encoderPinB, HIGH);  // turn on pullup resistors

    attachInterrupt(0, doEncoderA, CHANGE); // encoder pin on interrupt 0 (pin 2)
    attachInterrupt(1, doEncoderB, CHANGE); // encoder pin on interrupt 1 (pin 3)

    Serial.begin(9600);  // output
}

void loop()
{
    rotating = true;  // reset the debouncer

    if (lastReportedPos != encoderPos)
    {
        Serial.print("Index:");
        Serial.println(encoderPos, DEC);
        lastReportedPos = encoderPos;
    }
}

// Interrupt on A changing state
void doEncoderA()
{
    if (rotating) delay(1);  // wait a little until the bouncing is done
    if (digitalRead(encoderPinA) != A_set) {  // debounce once more
        A_set = !A_set;
        // adjust counter + if A leads B
        if (A_set && !B_set)
            encoderPos += 1;
        rotating = false;  // no more debouncing until loop() hits again
    }
}

// Interrupt on B changing state, same as A above
void doEncoderB() {
    if (rotating) delay(1);
    if (digitalRead(encoderPinB) != B_set) {
        B_set = !B_set;
        //  adjust counter - 1 if B leads A
        if (B_set && !A_set)
            encoderPos -= 1;
        rotating = false;
    }
}