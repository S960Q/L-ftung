

void loop() {

    rotating = true;  // reset the debouncer

    if (lastReportedPos != PWMFan)
    {
        Serial.print("Index:");
        Serial.println(PWMFan, DEC);
        lastReportedPos = PWMFan;
    }

}
