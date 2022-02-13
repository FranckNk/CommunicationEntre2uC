#include <Arduino.h>
#include <Wire.h>
#include "Timer.h"

Timer Temp;
// Include the required Wire library for I2C<br>#include 
const int PIN_ROTATION_SENSOR = A0;

unsigned short int ValueAngleServo = 0;        // Valeur envoyee dans le servo moteur.
unsigned short int RotationSensorValue = 0;        // Valeur lue par le capteur de roation.
unsigned short int LastValueAngleServo = 90; 		// Derniere valeur de l'angle du servo moteur.


unsigned long TimeDelay = 2000;

void setup() {
	// Start the I2C Bus as Master
	Serial.begin(9600);
	pinMode(PIN_ROTATION_SENSOR, INPUT);
	Wire.begin(); 
	Temp.startTimer(3000);
}
void loop() {
	RotationSensorValue = analogRead(PIN_ROTATION_SENSOR);
	ValueAngleServo = map(RotationSensorValue, 0, 1023, 0, 180);
	if (ValueAngleServo != LastValueAngleServo){
		// On a obtenu une variation de 02 degres soit de plus ou soit de moins.
		if (Temp.isTimerReady())
		{
			Serial.print("\n\nVariation OBTENUE.\n\n = ");
			Serial.println(ValueAngleServo);
			Temp.startTimer(TimeDelay);		
		}
		// On envoie le signal via le protocole I2C.
		Wire.beginTransmission(9); // transmit to device #9
		Wire.beginTransmission(10); // transmit to device #9
		Wire.write(ValueAngleServo);              // sends x 
		Wire.endTransmission();    // stop transmitting
		LastValueAngleServo = ValueAngleServo; // On sauvegarde la derniere variation.
		} 
		// // print the results to the serial monitor:
	Serial.print("sensor = ");
	Serial.print(RotationSensorValue);
	Serial.print("\t output = ");
	Serial.println(ValueAngleServo);
	delay(200);
}