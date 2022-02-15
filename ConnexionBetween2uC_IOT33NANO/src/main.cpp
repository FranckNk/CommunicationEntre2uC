/*

TITRE          : Projet Communication I2C : uC Peripherique. IOT 33 NANO
AUTEUR         : Franck Nkeubou Awougang
DATE           : 13/02/2022
DESCRIPTION    : uC peripherique et utilisation du protocole I2C
				 pour communication entre deux uC. Gestion du speaker.
VERSION        : 0.0.1

*/

#include <Arduino.h>
#include <Wire.h>
#include "Timer.h"
#define FREQ_SON  3500 // Définition de la fréquence du son du Speaker.

// Declaration des classes.
// Servo ServoMoteur;  // Création d'un objet de type Servo (un servo moteur).
Timer Temp;

// Déclaration des constantes.
const int PIN_SPEAKER_MODULE = 2;
unsigned short int ValueGot  = 0;
unsigned short int TimeDelay = 2000;

// Declaration des fonctions.
void receiveEvent(int bytes);
void setup() {
	
	// Start the I2C Bus as Peripheral on address 33
	Wire.begin(33); 
	Serial.begin(9600);
	// Attach a function to trigger when something is received.
	Wire.onReceive(receiveEvent);
	Temp.startTimer(3000);
}

void receiveEvent(int bytes) {
	ValueGot = Wire.read();    // read one character from the I2C
	if (ValueGot >= 180 || ValueGot <= 0)
	{
		tone(PIN_SPEAKER_MODULE, FREQ_SON, 500);
		delay(2);
		noTone(PIN_SPEAKER_MODULE);
	}
	
}

void loop() {
	if (Temp.isTimerReady())
	{
		Serial.print("\nIOT 33\nLa valeur obtenue est : ");
		Serial.println(ValueGot);
		Temp.startTimer(TimeDelay);		
	}
}
