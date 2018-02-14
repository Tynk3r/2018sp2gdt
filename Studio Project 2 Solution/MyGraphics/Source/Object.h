#pragma once
#include "Vector3.h"

class Object {
private:
	Vector3 pos;
	float size;
	float halfSize;
public:
	Object() { pos = { 0,0,0 }; size = 0; };
	Object(Vector3 p, float s) { pos = p; size = s; halfSize = size / 2; }
	~Object() {};
	void setBox(float x, float y, float z, float s) { pos.x = x; pos.y = y; pos.z = z; size = s; halfSize = s / 2; };
	float getSize(void) { return size; }
	float getHalfSize(void) { return halfSize; }
	Vector3 getPos(void) { return pos; }
};