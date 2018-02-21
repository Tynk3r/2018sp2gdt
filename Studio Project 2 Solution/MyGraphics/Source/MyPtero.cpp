#include "MyPtero.h"

MyPtero * MyPtero::Ptero_instance = nullptr;

MyPtero::MyPtero()
{
	hungry = true;
	incubating = false;
	pteroStage = P_EGG;
	pteroDirection = 180.0f;
	pteroMovementSpeed = 0.0f;
	pteroSpeedModifier = 1.0f;
	pteroSize = 1;

	this->setPos(Vector3(0,0,62.5));
	this->setBox(this->getPos(), pteroSize);
}

MyPtero* MyPtero::instance(void)
{
	if (MyPtero::Ptero_instance == nullptr)
	{
		MyPtero::Ptero_instance = new MyPtero();
	}
	return MyPtero::Ptero_instance;
}

// Getters for Scene1
float MyPtero::getSpeed(void)
{
	return this->FlightSpeed;
}
float MyPtero::getSteerSpeed(void)
{
	return this->FlightSteerSpeed;
}
float MyPtero::getStability(void)
{
	return this->FlightStability;
}
float MyPtero::getStamina(void)
{
	return this->FlightStamina;
}

// Setters for Scene2 
void MyPtero::setFlightSpeed(float sped)
{
	this->FlightSpeed = sped;
}
void MyPtero::setFlightSteerSpeed(float ster)
{
	this->FlightSteerSpeed = ster;
}
void MyPtero::setFlightStability(float stab)
{
	this->FlightStability = stab;
}
void MyPtero::setFlightStamina(float stam)
{
	this->FlightStamina = stam;
}

void MyPtero::newPtero(void)
{
	srand(time(NULL));
	float r = ((float)(rand() % 21) + (float)10) / (float)10; // 1.0-3.0
	float s = ((float)(rand() % 31) + (float)10) / (float)10; // 1.0-4.0

	hungry = true;
	incubating = false;
	pteroStage = P_EGG;
	pteroDirection = 180.0f;
	pteroMovementSpeed = 0.0f;
	pteroSpeedModifier = s;
	pteroSize = r;
	pteroLocationX = 0;
	pteroLocationZ = 62.5;
}
