#include <Wire.h>
#include <SoftwareSerial.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "DHT.h"
#define I2C_ADDRESS 0x3C

//*************Pin Definitions
#define BLEPower 4
#define SIMPower 5
#define Knob 7
#define KnobTurn1 2
#define KnobTurn2 3
#define DhtInnenK 7
#define DhtAusenK 8
#define FanPin 11
//************Other Definitiions
#define DHTTYPE DHT22
DHT dhtInnen(DhtInnenK, DHTTYPE);
DHT dhtAusen(DhtAusenK, DHTTYPE);
//Encoder
#define upperPWMLimit 255
#define lowerPWMlimit 0
#define knobStep 15
const byte encoderPinA = 2;
const byte encoderPinB = 3;
volatile int PWMFan = lowerPWMlimit;
unsigned int lastReportedPos = 1;   
static boolean rotating = false;      

boolean A_set = false;
boolean B_set = false;

//SoftwareSerial pwmReader(2, 3);
SoftwareSerial BLE(10, 11); // RX = 2, TX = 3 //Rx vom BLE geht auf 11
char appData;
String inData = "";


SSD1306AsciiWire oled;

void setup() 
{
    Wire.begin();

    dhtInnen.begin();
    dhtAusen.begin();

    oled.begin(&Adafruit128x64, I2C_ADDRESS);
    oled.set400kHz();
    oled.setContrast(255);



    pinMode(FanPin, OUTPUT);
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    pinMode(Knob, INPUT_PULLUP);
    digitalWrite(encoderPinA, HIGH);  // turn on pullup resistors
    digitalWrite(encoderPinB, HIGH);  // turn on pullup resistors

    attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE); // encoder pin on interrupt 0 (pin 2)
    attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, CHANGE); // encoder pin on interrupt 1 (pin 3)
    analogWrite(FanPin, 0);
    Serial.begin(9600);
    Serial.println("Hello");
    //pwmReader.begin(4800);
    oled.setFont(TimesNewRoman16);
    oled.println("finished");
    Serial.println("Setup done");

    BLE.begin(9600); // set BLE serial at 9600 baud rate
    BLE.println("Hallo");
}
