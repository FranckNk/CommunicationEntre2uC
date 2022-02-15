/*

TITRE          : Projet Communication I2C : uC Peripherique. MKR1010
AUTEUR         : Franck Nkeubou Awougang
DATE           : 13/02/2022
DESCRIPTION    : uC peripherique et utilisation du protocole I2C
				 pour communication entre deux uC. Gestion du Servo Moteur.
VERSION        : 0.0.1

*/

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h> // pour utilisaiton du servo moteur.
#include "Timer.h"

// Declaration des classes.
Servo ServoMoteur;  // Création d'un objet de type Servo (un servo moteur).
Timer Temp;


// Déclaration des constantes.
const int PIN_SERVO_MOTEUR = 2;

unsigned short int ValueGot     = 0; // Value got by I2C protocol.
unsigned short int TimeDelay    = 2000; // Wait time for serial monitor.
unsigned short int DelayAttente = 15; // Waiting time for set angle of servo.

// Declaration des fonctions.
void receiveEvent(int bytes);
void ResetServo();
void SetAngleServo();

void setup() {
	// Start the I2C Bus as Peripheral on address 10
	Wire.begin(10); 
	Serial.begin(9600);
	// Attach a function to trigger when something is received.
	Wire.onReceive(receiveEvent);
	// Configuration du mode des broches.
	ServoMoteur.attach(PIN_SERVO_MOTEUR);
	Temp.startTimer(2000); // Time to reset Servo.
}

void receiveEvent(int bytes) {
	ValueGot = Wire.read();    // read one character from the I2C
	ServoMoteur.write(ValueGot);              // Dit au servoMoteur la position dans la variable 'AngleServo'
	delay(DelayAttente);                       // Attendre le delay pour qu'il se positionne.
}

void loop() {
	if (Temp.isTimerReady())
	{
		Serial.print("\nMKR1010\nLa valeur obtenue est : ");
		Serial.println(ValueGot);
		Temp.startTimer(TimeDelay);		
	}
	
	
}
