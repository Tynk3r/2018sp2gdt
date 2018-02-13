#ifndef CAMERA_FPV_H
#define CAMERA_FPV_H

#include "Camera.h"
#include "SceneManager.h"

class CameraFPV : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	CameraFPV();
	~CameraFPV();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
	double prevX;
	double prevY;

	//Variable for Scene1
	double horizMove;
	double vertMove;
	double SkyboxSize;
};

#endif