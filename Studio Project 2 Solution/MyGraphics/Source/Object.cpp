#include "Object.h"

Object::Object()
{
	position = Vector3(0, 0, 0);
	
	sizeX = 0;
	sizeY = 0;
	sizeZ = 0;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}

Object::Object(Vector3 pos, float size)
{
	position = pos;
	
	sizeX = size;
	sizeY = size;
	sizeZ = size;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}

Object::Object(Vector3 pos, float xSize, float ySize, float zSize)
{
	position = pos;

	sizeX = xSize;
	sizeY = ySize;
	sizeZ = zSize;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}

void Object::setPos(Vector3 pos)
{
	position = pos;
}

void Object::setSize(float size)
{
	sizeX = size;
	sizeY = size;
	sizeZ = size;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}

void Object::setSize(float xSize, float ySize, float zSize)
{
	sizeX = xSize;
	sizeY = ySize;
	sizeZ = zSize;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}

void Object::setBox(Vector3 pos, float size)
{
	position = pos;

	sizeX = size;
	sizeY = size;
	sizeZ = size;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}


void Object::setBox(Vector3 pos, float xSize, float ySize, float zSize)
{
	position = pos;

	sizeX = xSize;
	sizeY = ySize;
	sizeZ = zSize;
	halfSizeX = sizeX / 2;
	halfSizeY = sizeY / 2;
	halfSizeZ = sizeZ / 2;

	minX = (position.x * sizeX) - halfSizeX;
	maxX = (position.x * sizeX) + halfSizeX;
	minY = (position.y * sizeY) - halfSizeY;
	maxY = (position.y * sizeY) + halfSizeY;
	minZ = (position.z * sizeZ) - halfSizeZ;
	maxZ = (position.z * sizeZ) + halfSizeZ;
}

Vector3 Object::getPos(void)
{
	return position;
}

float Object::getSize(void)
{
	return sizeX;
}

float Object::getSizeX(void)
{
	return sizeX;
}

float Object::getSizeY(void)
{
	return sizeY;
}

float Object::getSizeZ(void)
{
	return sizeZ;
}

Object::~Object()
{

}