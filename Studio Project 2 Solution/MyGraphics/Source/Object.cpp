#include "Object.h"

Object::Object()
{
	pos = Vector3(0, 0, 0);
	
	size = 0;
	halfSize = size / 2;

	minX = pos.x - halfSize;
	maxX = pos.x + halfSize;
	minY = pos.y - halfSize;
	maxY = pos.y + halfSize;
	minZ = pos.z - halfSize;
	maxZ = pos.z + halfSize;
}

Object::Object(Vector3 p, float s)
{
	pos = p;
	
	size = s;
	halfSize = size / 2;

	minX = pos.x - halfSize;
	maxX = pos.x + halfSize;
	minY = pos.y - halfSize;
	maxY = pos.y + halfSize;
	minZ = pos.z - halfSize;
	maxZ = pos.z + halfSize;
}

void Object::setPos(Vector3 p)
{
	pos = p;
}

void Object::setSize(float s)
{
	size = s;
	halfSize = size / 2;

	minX = pos.x - halfSize;
	maxX = pos.x + halfSize;
	minY = pos.y - halfSize;
	maxY = pos.y + halfSize;
	minZ = pos.z - halfSize;
	maxZ = pos.z + halfSize;
}

void Object::setBox(Vector3 p, float s)
{
	pos = p;
	size = s;

	halfSize = size / 2;

	minX = pos.x - halfSize;
	maxX = pos.x + halfSize;
	minY = pos.y - halfSize;
	maxY = pos.y + halfSize;
	minZ = pos.z - halfSize;
	maxZ = pos.z + halfSize;
}

Vector3 Object::getPos(void)
{ 
	return pos;
}

float Object::getSize(void)
{
	return size;
}


Object::~Object()
{

}