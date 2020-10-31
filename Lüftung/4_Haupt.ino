
int menu = 0;
bool BleStatus = 0;
unsigned long menuTimeout = 5000;
bool hitHundred = false;
void loop() {


    if (!digitalRead(Knob)) menu++;

    switch (menu) {
    
    case 0://Lüfter

        oled.clear();
        oled.setFont(Arial_bold_14);
        oled.print(PWMFan);
        while (digitalRead(Knob)) //Hauptloop?
        {
            rotating = true;
            if (lastReportedPos != PWMFan)
            {

                //Serial.print("Index:");
                oled.setCursor(0, 0);
                oled.print(PWMFan);
                oled.print("  ");
                if (PWMFan >= 100) hitHundred = true;
                if (PWMFan < 100 && hitHundred == true)
                {
                    oled.clear();
                    oled.setCursor(0, 0);
                    oled.print(PWMFan);
                    hitHundred = false;
                }
                if (PWMFan < 10)
                {
                    oled.clear();
                    oled.setCursor(0, 0);
                    oled.print(PWMFan);
                }
                Serial.println(PWMFan, DEC);
                lastReportedPos = PWMFan;
                analogWrite(FanPin, PWMFan);
            }
            //delay(50);
            BLE.listen();  // listen the BLE port
            String buffer = "";
            if (BLE.available()) //Wurden Daten vom SIM Modul gesendet?
            {
                char c;
                int charCount = 0;
                while (BLE.available()) {
                    c = BLE.read();
                    buffer.concat(c);
                    delay(1);
                }
            }
            
            if (buffer[0] == 'h') Serial.println("Hallo");

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
