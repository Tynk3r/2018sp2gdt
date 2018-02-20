#include "MyPtero.h"

MyPtero::MyPtero()
{
	hungry = true;
	incubating = false;
	pteroStage = P_EGG;
	pteroDirection = 180.0f;
	pteroMovementSpeed = 0.0f;
	pteroSize = 1;

	this->setPos(Vector3(0,0,62.5));
	this->setBox(this->getPos(), pteroSize);

	//Actual position setting expected in Scene
	//Collision expected to be updated in Scene
}

MyPtero::MyPtero(float spd, float steer, float stab, float stam, float size)
{
	hungry = true;
	incubating = false;
	pteroStage = P_EGG;
	pteroDirection = 180.0f;
	pteroMovementSpeed = 0.0f;
	pteroSize = size;

	FlightSpeed = spd;
	FlightSteerSpeed = steer;
	FlightStability = stab;
	FlightStamina = stam;

	this->setPos(Vector3(0, 0, 0));
	this->setBox(this->getPos(), pteroSize);

	//Actual position setting expected in Scene
	//Collision expected to be updated in Scene
}


MyPtero::~MyPtero()
{
}

// Getters for Scene1 pointer;
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
