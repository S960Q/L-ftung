/*
 Name:		reciverArduino.ino
 Created:	01.11.2020 11:51:33
 Author:	Simon
*/
#include <SoftwareSerial.h>
#include <Wire.h>

#define pumpenPin 5
#define wbusPin 6

#define pwmOut 9
#define pwmOut2 5
#define en1 6
#define en2 5

void analogWrite25k(int pin, int value)
{
    switch (pin) {
    case 9:
        OCR1A = value;
        break;
    case 10:
        OCR1B = value;
        break;
    default:
        // no other pin will work
        break;
    }
}
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(4800);
    while (!Serial) {
        ;
    }
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(pumpenPin, OUTPUT);
    pinMode(wbusPin, OUTPUT);


    //////////////////////////////////////PWM
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);

    //Serial.begin(9600);
    digitalWrite(en1, 1);
    digitalWrite(en2, 1);
    // Configure Timer 1 for PWM @ 25 kHz.
    TCCR1A = 0;           // undo the configuration done by...
    TCCR1B = 0;           // ...the Arduino core library
    TCNT1 = 0;           // reset timer
    TCCR1A = _BV(COM1A1)  // non-inverted PWM on ch. A
        | _BV(COM1B1)  // same on ch; B
        | _BV(WGM11);  // mode 10: ph. correct PWM, TOP = ICR1
    TCCR1B = _BV(WGM13)   // ditto
        | _BV(CS10);   // prescaler = 1
    ICR1 = 320;         // TOP = 320

    // Set the PWM pins as output.
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    /////////////////////////////////////
}
int incomingByte;      // a variable to read incoming serial data into
String inputString = "l: 10";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int fanPWM = 0;
int pumpe = 0;
// the loop function runs over and over again until power down or reset



void heizen() 
{
    digitalWrite(pumpenPin, 1);
    digitalWrite(wbusPin, 1);
}

void heizungDeaktivieren()
{
    digitalWrite(pumpenPin, 0);
    digitalWrite(wbusPin, 0);
}



void loop() {

    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag so the main loop can
        // do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
    
    if (inputString[0] == 'l')
    {
        Serial.print("Lueftung: ");
        
        char buf[60];
        inputString.toCharArray(buf, 60);
        sscanf(buf, "l: %i", &fanPWM);
        Serial.println(fanPWM);
        analogWrite25k(9, fanPWM);
        inputString = "";
    }
    else if (inputString[0] == 'h') //pumpe wird aktiviert
    {
        Serial.print("heizen: ");

        char buf[60];
        int tmpI;
        inputString.toCharArray(buf, 60);
        sscanf(buf, "p: %i", &tmpI);
        Serial.println(tmpI);
        if (tmpI == 1) heizen();
        else if (tmpI == 0) heizungDeaktivieren();
        inputString = "";
    }
   
   
    delay(1000);
    //Serial.println("alive");
    
}
