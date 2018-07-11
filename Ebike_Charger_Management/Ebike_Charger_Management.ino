#include "Averager.h"

const int LED = 13;
const int LED_BLUE = 4;
const int LED_RED = 6;
const int LED_GREEN = 5;
const int RELAY = 2;
const int BATTERY = A0;

enum Color { red, green, blue, dark};
enum Relay { on, off };

const double VOLTAGE_MULTIPLIER = 0.0569;
const int HVC = 57.3;
const int DELAY = 500;					  
	

void setLedColor(enum Color input);
double getBatteryVoltage();
void turnRelay(enum Relay input);
void charge();
Averager aveg;


void setup() {
	pinMode(LED, OUTPUT);
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_GREEN, OUTPUT);
	pinMode(LED_BLUE, OUTPUT);

	pinMode(RELAY, OUTPUT);

	pinMode(BATTERY, INPUT);
	Serial.begin(9600);
}


void loop() {
  

	charge();

	while (true)
	{
		Serial.println(getBatteryVoltage(), 3);
		delay(DELAY);
		//wait.
	}

	
}


void setLedColor(enum Color input)
{
	// clearing the previous color.
	digitalWrite(LED_RED, LOW);
	digitalWrite(LED_GREEN, LOW);
	digitalWrite(LED_BLUE, LOW);

	//setting color.
	switch (input)
	{
	case red:   digitalWrite(LED_RED, HIGH);   break;
	case green: digitalWrite(LED_GREEN, HIGH); break;
	case blue:  digitalWrite(LED_BLUE, HIGH); break;
	case dark:   break;
	}
}



double getBatteryVoltage()
{
	double batteryReading = analogRead(BATTERY);

	aveg.addNum(batteryReading * VOLTAGE_MULTIPLIER);
	
	return aveg.getAverage();

}


void turnRelay(enum Relay input)
{
	switch (input)
	{
	case on: digitalWrite(RELAY, HIGH); break;
	case off: digitalWrite(RELAY, LOW); break;
	}
}



void charge()
{
	turnRelay(on);

	while (getBatteryVoltage() < HVC)
	{
		Serial.println(getBatteryVoltage(), 3);

		for (int i = 0; i < 10; i++)
		{
			getBatteryVoltage();
			delay(10);
		}

		//blinking while charging.
		setLedColor(red);
		delay(DELAY);
		setLedColor(dark);
		delay(DELAY - 100);

	}

	turnRelay(off);
	setLedColor(green);

	//while (true)
	//{
	//	Serial.println(getBatteryVoltage(), 3);
	//	delay(DELAY);
	//	//wait.
	//}

}