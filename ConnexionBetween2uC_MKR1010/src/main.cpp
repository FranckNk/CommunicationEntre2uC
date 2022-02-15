#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include "Timer.h"
// Declaration des classes.
Servo ServoMoteur;  // Création d'un objet de type Servo (un servo moteur).
Timer Temp;

unsigned short int TimeDelay = 2000;

// Déclaration des constantes.
const int PIN_SERVO_MOTEUR = 2;

unsigned short int ValueGot = 0;
unsigned short int LastValueGot = 0;
unsigned short int DelayAttente = 15;

void receiveEvent(int bytes);
void ResetServo();
void SetAngleServo();

void setup() {
	// Start the I2C Bus as Slave on address 9
	Wire.begin(10); 
	Serial.begin(9600);
	// Attach a function to trigger when something is received.
	Wire.onReceive(receiveEvent);
	// Configuration du mode des broches.
	ServoMoteur.attach(PIN_SERVO_MOTEUR);
	LastValueGot = ServoMoteur.read();
	Temp.startTimer(3000);
}

void receiveEvent(int bytes) {
	ValueGot = Wire.read();    // read one character from the I2C
	ServoMoteur.write(ValueGot);              // Dit au servoMoteur la position dans la variable 'AngleServo'
	delay(DelayAttente);                       // Attendre le delay pour qu'il se positionne.
}

void ResetServo(){
	LastValueGot = ServoMoteur.read();
	while (LastValueGot > 0)
	{
		LastValueGot -= 1;
		ServoMoteur.write(LastValueGot);  
		delay(DelayAttente);
	}
	LastValueGot = 0;
}

void SetAngleServo(){
	short int Value = LastValueGot;
	bool State = ValueGot > Value;
		Serial.print("SetAngle = ");
		Serial.println(State);
	while (ValueGot != Value)
	{
		if (State)
		{
			Serial.println("SetAngle State True = ");
			ServoMoteur.write(Value);  
			delay(DelayAttente); // Attendons que le servo moteur se positionne.
			Value++;
		}
		else{
			Serial.println("SetAngle State False = ");
			ServoMoteur.write(Value);  
			delay(DelayAttente); // Attendons que le servo moteur se positionne.
			Value--;
		}		
	}
}

void loop() {
	
	if (Temp.isTimerReady())
	{
		Serial.print("Last = ");
		Serial.print(LastValueGot);
		Serial.print("\nMKR1010\nLa valeur obtenue est : ");
		Serial.println(ValueGot);
		Temp.startTimer(TimeDelay);		
	}
	
	
}
