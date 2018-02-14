#ifndef OBJECT_H
#define OBJECT_H
#include "Vector3.h"

class Object {
private:
	Vector3 position;

	float sizeX;
	float sizeY;
	float sizeZ;
	float halfSizeX;
	float halfSizeY;
	float halfSizeZ;
public:
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	// Constructors
	Object();
	Object(Vector3 pos, float size);
	Object(Vector3 pos, float xSize, float ySize, float zSize);

	// Set function
	void setPos(Vector3 pos);
	void setSize(float size);
	void setSize(float xSize, float ySize, float zSize);
	void setBox(Vector3 pos, float size);
	void setBox(Vector3 pos, float xSize, float ySize, float zSize);

	// Get functions
	Vector3 getPos(void);
	float getSize(void);
	float getSizeX(void);
	float getSizeY(void);
	float getSizeZ(void);

	// Destructor
	~Object();

};

#endif