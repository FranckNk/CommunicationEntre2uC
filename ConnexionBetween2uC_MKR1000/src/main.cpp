#include <Arduino.h>
#include <Wire.h>
#include "Timer.h"

Timer Temp;
// Déclaration des constantes.
const int PIN_TOUCH_SENSOR = 3;
const int PIN_PUSH_BUTTON = 1;

unsigned short int ValueAngleServo = 90;        // Valeur envoyee dans le servo moteur.
unsigned short int RotationSensorValue = 0;        // Valeur lue par le capteur de roation.
unsigned short int LastValueAngleServo = 90; 		// Derniere valeur de l'angle du servo moteur.


unsigned long TimeDelay = 2000;

void setup() {
	// Configuration du mode des broches.
	pinMode(PIN_TOUCH_SENSOR, INPUT);
	pinMode(PIN_PUSH_BUTTON, INPUT);
	// Start the I2C Bus as Master
	Serial.begin(9600);
	Wire.begin(); 
	Temp.startTimer(3000);
}
void loop() {
	
	bool ReadingPinButton = digitalRead(PIN_PUSH_BUTTON);
	bool ReadingPinTouch = digitalRead(PIN_TOUCH_SENSOR);

	if (ReadingPinButton && !ReadingPinTouch){
		// On a détecté l'approche du mouvement dans le capteur. On peut alors modifier l'angle.
		if (ValueAngleServo >= 180){
			// On envoie le signal via le protocole I2C.
			// Ajout d'un nouvel composant I2C avec pour addresse 33.
			Wire.beginTransmission(33);
			Wire.write(ValueAngleServo); 
			Wire.endTransmission();    // stop transmitting
			delay(2); // wait time to play tone.
			ValueAngleServo = 180;
		}	
		else{
			ValueAngleServo += 1;			// On augmente l'angle
			Wire.beginTransmission(10); 
			Wire.write(ValueAngleServo);  
			Wire.endTransmission();    // stop transmitting
			LastValueAngleServo = ValueAngleServo; // On sauvegarde la derniere variation.
								// Attendre le delay pour qu'il se positionne.
			delay(15); // wait time to positionne the Servo Motor.
		}
	}
	else if (!ReadingPinButton && ReadingPinTouch){
		// On a détecté l'approche du mouvement dans le capteur. On peut alors modifier l'angle.
		if (ValueAngleServo <= 0){
			// On envoie le signal via le protocole I2C.
			// Ajout d'un nouvel composant I2C avec pour addresse 33.
			Wire.beginTransmission(33);
			Wire.write(ValueAngleServo); 
			Wire.endTransmission();    // stop transmitting
			delay(2); // wait time to play tone.
			ValueAngleServo = 0;
		}	
		else{
			ValueAngleServo -= 1;			// On augmente l'angle
			Wire.beginTransmission(10); 
			Wire.write(ValueAngleServo);  
			Wire.endTransmission();    // stop transmitting
			// Attendre le delay pour qu'il se positionne.
			delay(15); // wait time to positionne the Servo Motor.
		}
	}
	else{
		// on ne fait rien. C'est vrai je pouvais ne pas mettre, 
		// mais c'est pour ne pas oublier le raisonnement.
	}
}