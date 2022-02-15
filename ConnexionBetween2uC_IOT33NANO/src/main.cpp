#include <Arduino.h>
#include <Wire.h>
#include "Timer.h"
// Declaration des classes.
// Servo ServoMoteur;  // Création d'un objet de type Servo (un servo moteur).
Timer Temp;

unsigned long TimeDelay = 2000;

unsigned short int ValueGot = 0;
void receiveEvent(int bytes);
void setup() {
	// Start the I2C Bus as Slave on address 10
	Wire.begin(33); 
	Serial.begin(9600);
	// Attach a function to trigger when something is received.
	Wire.onReceive(receiveEvent);
	Temp.startTimer(3000);
}
void receiveEvent(int bytes) {
	ValueGot = Wire.read();    // read one character from the I2C
}
void loop() {
	if (Temp.isTimerReady())
	{
		Serial.print("\nIOT 33\nLa valeur obtenue est : ");
		Serial.println(ValueGot);
		Temp.startTimer(TimeDelay);		
	}
}
