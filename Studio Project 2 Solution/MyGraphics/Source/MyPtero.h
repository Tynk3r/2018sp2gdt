#ifndef MY_PTERO_H
#define MY_PTERO_H

#include "Object.h"

class MyPtero : public Object
{
private:
	static MyPtero *Ptero_instance;
	MyPtero();

	float FlightSpeed;
	float FlightSteerSpeed;
	float FlightStability;
	float FlightStamina;
public:
	static MyPtero* instance(void);

	enum PTERO_STATE
	{
		P_EGG = 0,
		P_BABY,
		P_ADOLESCENT,
		P_ADULT,
	};

	enum PTERO_TYPE
	{
		T_RED = 0,
		T_GREEN,
		T_PURPLE,
	};

	//For Breeding/Raising
	bool hungry = true;
	bool incubating = false;

	int pteroStage;
	int pteroType;
	float pteroDirection;
	float pteroMovementSpeed;
	float pteroSpeedModifier;
	float pteroSize;
	float pteroLocationX = 0;
	float pteroLocationZ = 62.5;
	float pteroLocationY = 0;

	void newPtero(void);
	void setFlightSpeed(float);
	void setFlightSteerSpeed(float);
	void setFlightStability(float);
	void setFlightStamina(float);

	//For Flying
	float getSpeed(void);			//How fast ptero can fly
	float getSteerSpeed(void);		//How fast ptero can turn in air
	float getStability(void);		//How fast the ptero pitches downwards on its own
	float getStamina(void);			//How long you can hold down shift for speed boost
};

#endif