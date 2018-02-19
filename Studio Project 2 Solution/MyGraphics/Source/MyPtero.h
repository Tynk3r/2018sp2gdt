#ifndef MY_PTERO_H
#define MY_PTERO_H

#include "Object.h"

class MyPtero : public Object
{
private:
	enum PTERO_STATE {
		P_EGG = 0,
		P_BABY,
		P_ADOLESCENT,
		P_ADULT,
	};

	int pteroStage;

	float pteroDirection;
	float pteroMovementSpeed;
	float pteroSize;

	float FlightSpeed;
	float FlightSteerSpeed;
	float FlightStability;
	float FlightStamina;

public:
	MyPtero(); //For default ptero
	MyPtero(float spd, float steer, float stab, float stam, float size); //For new pteros
	~MyPtero();

	//For Breeding/Raising
	bool hungry;
	bool incubating;

	//For Flying
	float getSpeed(void);
	float getSteerSpeed(void);
	float getStability(void);
	float getStamina(void);
	
};

#endif