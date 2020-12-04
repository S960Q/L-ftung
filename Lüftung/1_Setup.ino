#include <Wire.h>
#include <SoftwareSerial.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "DHT.h"
#include <PWM.h>
#define I2C_ADDRESS 0x3C

//*************Pin Definitions
#define BLEPower 4
#define SIMPower 5
#define Knob 7
#define KnobTurn1 2
#define KnobTurn2 3
#define DhtInnenK 5
#define DhtAusenK 8
#define FanPin 9
#define FanPinHinten 10
#define piPin A0
#define hiPin A1
//************Other Definitiions
#define DHTTYPE DHT22
DHT dhtInnen(DhtInnenK, DHTTYPE);
DHT dhtAusen(DhtAusenK, DHTTYPE);
//Encoder
#define upperPWMLimit 320
#define lowerPWMlimit 0
#define knobStep 15
const byte encoderPinA = 2;
const byte encoderPinB = 3;
volatile int PWMFan = lowerPWMlimit;
volatile int PWMFanHinten = lowerPWMlimit;
unsigned int lastReportedPos = 1;   
static boolean rotating = false;      

boolean A_set = false;
boolean B_set = false;

SoftwareSerial pwmReader(2, 3);
SoftwareSerial BLE(12, 11); // RX = 2, TX = 3 //Rx vom BLE geht auf 11
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

    //analogWrite(FanPin, 0);
    Serial.begin(9600);
    // Set the PWM pins as output.
    pinMode(FanPin, OUTPUT);
    pinMode(FanPinHinten, OUTPUT);
    InitTimersSafe();
    int32_t frequency = 50; //frequency (in Hz)
    //analogWrite25k(FanPinHinten, 0);
    bool success = SetPinFrequencySafe(FanPin, frequency);
    Serial.println(success);
    success = SetPinFrequencySafe(FanPinHinten, frequency);
    Serial.println(success);
    pwmWrite(FanPinHinten, 200);

    pinMode(6, OUTPUT);
    success = SetPinFrequencySafe(6, frequency);
    Serial.println(success);
    pwmWrite(6, 200);


    pinMode(hiPin, OUTPUT);
    pinMode(piPin, OUTPUT);
    digitalWrite(hiPin, 1);
    digitalWrite(piPin, 1);
    pwmWrite(FanPin, 100);
    pwmWrite(FanPinHinten, 200);

    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    pinMode(Knob, INPUT_PULLUP);
    digitalWrite(encoderPinA, HIGH);  // turn on pullup resistors
    digitalWrite(encoderPinB, HIGH);  // turn on pullup resistors

    attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE); // encoder pin on interrupt 0 (pin 2)
    attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, CHANGE); // encoder pin on interrupt 1 (pin 3)

    Serial.println("Hello");
    //pwmReader.begin(4800);
    oled.setFont(TimesNewRoman16);
    oled.println("finished");
    Serial.println("Setup done");

    BLE.begin(9600); // set BLE serial at 9600 baud rate
    BLE.println("Hallo");
}
