#include "MyPtero.h"

MyPtero * MyPtero::Ptero_instance = nullptr;

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

MyPtero* MyPtero::instance(void)
{
	if (MyPtero::Ptero_instance == nullptr)
	{
		MyPtero::Ptero_instance = new MyPtero();
	}
	return MyPtero::Ptero_instance;
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
