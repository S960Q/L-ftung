#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#define I2C_ADDRESS 0x3C

//*************Pin Definitions
#define BLEPower 4
#define SIMPower 5
#define Knob 6
#define KnobTurn1 5
#define KnobTurn2 6

//************Other Definitiions

//Encoder
#define upperPWMLimit 255
#define lowerPWMlimit 10
#define encoderPinA 64
#define encoderPinB 65
volatile int PWMFan = lowerPWMlimit;
unsigned int lastReportedPos = 1;   
static boolean rotating = false;      

boolean A_set = false;
boolean B_set = false;



SSD1306AsciiWire oled;

void setup() 
{
    Wire.begin();
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
    oled.set400kHz();

    oled.setFont(Arial_bold_14);


    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);

    digitalWrite(encoderPinA, HIGH);  // turn on pullup resistors
    digitalWrite(encoderPinB, HIGH);  // turn on pullup resistors

    attachInterrupt(0, doEncoderA, CHANGE); // encoder pin on interrupt 0 (pin 2)
    attachInterrupt(1, doEncoderB, CHANGE); // encoder pin on interrupt 1 (pin 3)

    Serial.begin(9600);
    
    oled.setFont(TimesNewRoman16);
    oled.print(" ");
    oled.println("Setup finished");
}
