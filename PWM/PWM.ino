/*
 Name:		PWM.ino
 Created:	20.04.2020 22:07:40
 Author:	Simon
*/
#include <Arduino.h>
#define pwmOut 6
#define pwmOut2 5
#define en1 9
#define en2 10


#define pwm 0
// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(pwmOut, OUTPUT);
    pinMode(en1, OUTPUT);
    pinMode(en2, OUTPUT);

    Serial.begin(9600);
    digitalWrite(en1, 1);
    digitalWrite(en2, 1);

}
int i = 0;

void loop() {
   

    analogWrite(pwmOut, i);
    i++;
    if (i > 100) i = 0;
    delay(100);
    

}
