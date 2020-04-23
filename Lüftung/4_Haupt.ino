
int menu = 0;
bool BleStatus = 0;
unsigned long menuTimeout = 5000;

void loop() {


    if (!digitalRead(Knob)) menu++;

    switch (menu) {
    
    case 0://Lüfter

        oled.clear();
        oled.setFont(Arial_bold_14);
        oled.print(PWMFan);
        while (digitalRead(Knob))
        {
            rotating = true;
            if (lastReportedPos != PWMFan)
            {

                Serial.print("Index:");
                oled.setCursor(0, 0);
                oled.print(PWMFan);
                oled.print("  ");
                Serial.println(PWMFan, DEC);
                lastReportedPos = PWMFan;
                analogWrite(FanPin, PWMFan);
            }
        }
        menu++;
        delay(500);
    
    case 1:
        int PWMFanSave = PWMFan;
        bool tmpStatus = 0;
        bool timeout = 0;
        TimerReset();
        oled.setFont(TimesNewRoman16);
        oled.clear();
        oled.print("Bluethooth:");


        if (BleStatus == 0)
            oled.print("Off");
        else oled.print("On");
        
        while (digitalRead(Knob))
        {
           // Serial.println(PWMFan);
            rotating = true;
            if (lastReportedPos < PWMFan)
            {
                oled.clear();
                oled.print("Bluethooth:");
                oled.print("Off");
                tmpStatus = 0;
                lastReportedPos = PWMFan;
                TimerReset();
            }
            else if (lastReportedPos > PWMFan)
            {
                oled.clear();
                oled.print("Bluethooth:");
                oled.print("On");
                tmpStatus = 0;
                lastReportedPos = PWMFan;
                //Serial.println("pop");
                TimerReset();
            }
            if (Timer(menuTimeout)) {
                timeout = 1;
                break;
            }
        }
        PWMFan = PWMFanSave;
        if (!timeout) BleStatus = tmpStatus;

        menu = 0;
        delay(600);
        Serial.println(BleStatus);
    }

    if (menu > 1) menu = 0;
    if (menu < 0) menu = 1;
   // Serial.println(menu);
}
