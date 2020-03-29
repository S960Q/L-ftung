
unsigned long previousMillis = 0;
int Timer(unsigned long Interval)
{
	unsigned long currentMillis = millis(); 
	if (currentMillis - previousMillis >= Interval)
	{
		previousMillis = currentMillis;
		return (1);
	}
	else return (0);
}

int TimerReset()
{
	previousMillis = millis();
}


void doEncoderA()
{
	if (rotating) delay(1);  // wait a little until the bouncing is done
	if (digitalRead(encoderPinA) != A_set) {  // debounce once more
		A_set = !A_set;
		// adjust counter + if A leads B
		if (A_set && !B_set)
			PWMFan += 1;
		if (PWMFan >= upperPWMLimit) PWMFan = upperPWMLimit;
		rotating = false;  // no more debouncing until loop() hits again
	}
}

// Interrupt on B changing state, same as A above
void doEncoderB() {
	if (rotating) delay(1);
	if (digitalRead(encoderPinB) != B_set) {
		B_set = !B_set;
		//  adjust counter - 1 if B leads A
		if (B_set && !A_set)
			PWMFan -= 1;
		if (PWMFan <= lowerPWMlimit) PWMFan = lowerPWMlimit;
		rotating = false;
	}
}

int getPWM()
{
	char buffer[6];

	if (pwmReader.available())
	{
		pwmReader.read();
	}
}