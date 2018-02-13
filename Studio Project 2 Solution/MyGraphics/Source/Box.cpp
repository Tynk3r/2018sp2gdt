#include "Box.h"


Box::Box()
{
}

Box::Box(Vector3 position, float _size)
{
	this->position = position;
	minX = position.x - _size;
	maxX = position.x + _size;
	minY = position.y - _size;
	maxY = position.y + _size;
	minZ = position.z - _size;
	maxZ = position.z + _size;
}

Box::Box(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
	this->minZ = minZ;
	this->maxZ = maxZ;
}

void Box::Set(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
	this->minZ = minZ;
	this->maxZ = maxZ;
}

void Box::Set(Vector3 position, float _size)
{
	this->position = position;
	minX = position.x - _size;
	maxX = position.x + _size;
	minY = position.y - _size;
	maxY = position.y + _size;
	minZ = position.z - _size;
	maxZ = position.z + _size;
}


bool Box::IsPointInsideAABB(Vector3 point, Box box)
{
	if ((point.x >= box.minX && point.x <= box.maxX) &&
		(point.y >= box.minY && point.y <= box.maxY) &&
		(point.z >= box.minZ && point.z <= box.maxZ))
	{
		return true;
	}
	else
		return false;
}

bool Box::IsBoxInsideAABB(Box box1, Box box2)
{
	if (((box1.minX >= box2.maxX && box1.minX <= box2.minX) && (box1.minY >= box2.maxY && box1.minY <= box2.minY) && (box1.minZ >= box2.maxZ && box1.minZ <= box1.minZ)) ||
		((box1.minX >= box2.maxX && box1.minX <= box2.minX) && (box1.minY >= box2.maxY && box1.minY <= box2.minY) && (box1.maxZ >= box2.maxZ && box1.maxZ <= box1.minZ)) ||
		((box1.minX >= box2.maxX && box1.minX <= box2.minX) && (box1.maxY >= box2.maxY && box1.maxY <= box2.minY) && (box1.minZ >= box2.maxZ && box1.minZ <= box1.minZ)) ||
		((box1.minX >= box2.maxX && box1.minX <= box2.minX) && (box1.maxY >= box2.maxY && box1.maxY <= box2.minY) && (box1.maxZ >= box2.maxZ && box1.maxZ <= box1.minZ)) ||
		((box1.maxX >= box2.maxX && box1.maxX <= box2.minX) && (box1.minY >= box2.maxY && box1.minY <= box2.minY) && (box1.minZ >= box2.maxZ && box1.minZ <= box1.minZ)) ||
		((box1.maxX >= box2.maxX && box1.maxX <= box2.minX) && (box1.minY >= box2.maxY && box1.minY <= box2.minY) && (box1.maxZ >= box2.maxZ && box1.maxZ <= box1.minZ)) ||
		((box1.maxX >= box2.maxX && box1.maxX <= box2.minX) && (box1.maxY >= box2.maxY && box1.maxY <= box2.minY) && (box1.minZ >= box2.maxZ && box1.minZ <= box1.minZ)) ||
		((box1.maxX >= box2.maxX && box1.maxX <= box2.minX) && (box1.maxY >= box2.maxY && box1.maxY <= box2.minY) && (box1.maxZ >= box2.maxZ && box1.maxZ <= box1.minZ))
		)
	{
		return true;
	}
	else
		return false;
}

Box::~Box()
{
}
