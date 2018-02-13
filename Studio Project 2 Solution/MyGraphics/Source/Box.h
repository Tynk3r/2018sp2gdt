#ifndef BOX_H
#define BOX_H

#include "Vector3.h"

class Box
{
public:
	Vector3 position;
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	Box();
	Box(Vector3 position, float _size);
	Box(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void Set(Vector3 position, float _size);
	void Set(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	bool Box::IsPointInsideAABB(Vector3 point, Box box);
	bool Box::IsBoxInsideAABB(Box box1, Box box2);
	~Box();
};

#endif