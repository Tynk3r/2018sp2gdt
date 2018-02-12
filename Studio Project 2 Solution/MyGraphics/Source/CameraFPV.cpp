#include "CameraFPV.h"
#include "Application.h"
#include "Mtx44.h"
#include <iostream>

CameraFPV::CameraFPV()
{
}

CameraFPV::~CameraFPV()
{
}

void CameraFPV::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	Application::SetCursorVisible(false);
	prevX = Application::GetCursorX();
	prevY = Application::GetCursorY();
}

void CameraFPV::Update(double dt)
{
	static const float CAMERA_SPEED = 4.0f;
	static float MOVEMENT_SPEED = 30.0f;

	double horizMove = (Application::GetCursorX() - prevX)*10.0;
	double vertMove = (Application::GetCursorY() - prevY)*10.0;

	double yaw = -horizMove*dt;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(yaw, up.x, up.y, up.z);
	view = rotation*view;
	target = position + view;
	double pitch = (vertMove*dt) / 25.0f;
	target = target + Vector3(-up.x*pitch, -up.y*pitch, -up.z*pitch);
	
	if(Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D')) // right
	{
		position += right * (float)(MOVEMENT_SPEED * dt);
		target += right * (float)(MOVEMENT_SPEED * dt);
		if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f) {
			position -= right * (float)(MOVEMENT_SPEED * dt);
			target -= right * (float)(MOVEMENT_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')) // left
	{
		position -= right * (float)(MOVEMENT_SPEED * dt);
		target -= right * (float)(MOVEMENT_SPEED * dt);
		if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f) {
			position += right * (float)(MOVEMENT_SPEED * dt);
			target += right * (float)(MOVEMENT_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // front
	{
		Vector3 view1(view.x, 0, view.z);
		position += view1 * (float)(MOVEMENT_SPEED * dt);
		target += view1 * (float)(MOVEMENT_SPEED * dt);
		if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f) {
			position -= view1 * (float)(MOVEMENT_SPEED * dt);
			target -= view1 * (float)(MOVEMENT_SPEED * dt);
		}

	}
	if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // back
	{
		Vector3 view1(view.x, 0, view.z);
		position -= view1 * (float)(MOVEMENT_SPEED * dt);
		target -= view1 * (float)(MOVEMENT_SPEED * dt);
		if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f) {
			position += view1 * (float)(MOVEMENT_SPEED * dt);
			target += view1 * (float)(MOVEMENT_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed(' ')) // +y
	{
		position += up * (float)(MOVEMENT_SPEED * dt);
		target += up * (float)(MOVEMENT_SPEED * dt);
		if (position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
			position -= up * (float)(MOVEMENT_SPEED * dt);
			target -= up * (float)(MOVEMENT_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed(17)) // -y
	{
		position -= up * (float)(MOVEMENT_SPEED * dt);
		target -= up * (float)(MOVEMENT_SPEED * dt);
		if (position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
			position += up * (float)(MOVEMENT_SPEED * dt);
			target += up * (float)(MOVEMENT_SPEED * dt);
		}
	}
	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	if (Application::IsKeyPressed(VK_LSHIFT))
	{
		MOVEMENT_SPEED = 60.0f;
	}
	else
	{
		MOVEMENT_SPEED = 30.0f;
	}
	prevX = Application::GetCursorX();
	prevY = Application::GetCursorY();
}

void CameraFPV::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}