/*
 Name:		PWM.ino
 Created:	20.04.2020 22:07:40
 Author:	Simon
*/
#include <Arduino.h>
#define pin 6
#define pwm 0
// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(pin, OUTPUT);
    Serial.begin(9600);
}
int i = 0;
// the loop function runs over and over again until power down or reset
void loop() {
    
    analogWrite(pin, i);
    i++;
    if (i > 240) i = 0;
    delay(10);
    Serial.println(i);

}
