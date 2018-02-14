#ifndef OBJECT_H
#define OBJECT_H
#include "Vector3.h"

class Object {
private:
	Vector3 pos;

	float size;
	float halfSize;
public:
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	// Constructors
	Object();
	Object(Vector3 p, float s);

	// Set function
	void setPos(Vector3 p);
	void setSize(float s);
	void setBox(Vector3 p, float s);

	// Get functions
	Vector3 getPos(void);
	float getSize(void);

	// Destructor
	~Object();

};

#endif