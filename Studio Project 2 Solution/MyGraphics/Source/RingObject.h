#pragma once
#include "Object.h"

class RingObject : public Object
{
private:
	int RingID;
public:
	RingObject();
	~RingObject();

	void setID(int);
	int getID();
};

