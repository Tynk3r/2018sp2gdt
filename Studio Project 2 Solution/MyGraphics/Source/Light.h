#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"
struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	//add these after existing parameters 
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
	Light()
	{
		color.Set(1, 1, 1);
		power = 1.0f;
		kC = 1.0f;
		kL = 0.0f;
		kQ = 0.0f;
		//type = LIGHT_POINT;
		spotDirection.Set(0, 0, 0);
		cosCutoff = 2.0f;
		cosInner = 4.0f;
		exponent = 2.0f;
	}
};

#endif