#ifndef RING_OBJECT_H
#define RING_OBJECT_H

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

#endif