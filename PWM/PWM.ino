/*
 Name:		PWM.ino
 Created:	20.04.2020 22:07:40
 Author:	Simon
*/
#include <Arduino.h>
#define pwmOut 9
#define pwmOut2 5
#define en1 6
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


    TCCR1A = 0;
    TCCR1B = 0;



    //Modus Fast PWM-Mode 10 Bit einstellen
    TCCR1A |= (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12);



    //Vorteiler auf 8 setzen

    TCCR1B |= (1 << CS10) | (0 << CS11) | (0 << CS12);



    //Nichtinvertiertes PWM-Signal setzen
    TCCR1A |= (1 << COM1A1);


    //PWM-Pin 9 als Ausgang definieren
    DDRB |= (1 << DDB1);



}
int i = 0;

void loop() {
   

    OCR1A = i;
    i++;
    if (i > 200) i = 0;
    delay(100);
    

}
