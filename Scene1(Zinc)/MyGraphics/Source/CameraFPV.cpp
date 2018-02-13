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

	//Init for Scene1
	horizMove = 0.0;
	vertMove = 0.0;
	SkyboxSize = 500.0f;
}

void CameraFPV::Update(double dt)
{
	
	//Temp Var
	bool PrintInfo = true;

	if (SceneManager::instance()->GetSceneID() != SceneManager::SCENEID_1)
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

		if (Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D')) // right
		{
			position += right * (float)(MOVEMENT_SPEED * dt);
			target += right * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
				position -= right * (float)(MOVEMENT_SPEED * dt);
				target -= right * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')) // left
		{
			position -= right * (float)(MOVEMENT_SPEED * dt);
			target -= right * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
				position += right * (float)(MOVEMENT_SPEED * dt);
				target += right * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // front
		{
			Vector3 view1(view.x, 0, view.z);
			position += view1 * (float)(MOVEMENT_SPEED * dt);
			target += view1 * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
				position -= view1 * (float)(MOVEMENT_SPEED * dt);
				target -= view1 * (float)(MOVEMENT_SPEED * dt);
			}

		}
		if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // back
		{
			Vector3 view1(view.x, 0, view.z);
			position -= view1 * (float)(MOVEMENT_SPEED * dt);
			target -= view1 * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
				position += view1 * (float)(MOVEMENT_SPEED * dt);
				target += view1 * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(' ')) // +y
		{
			position += up * (float)(MOVEMENT_SPEED * dt);
			target += up * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
				position -= up * (float)(MOVEMENT_SPEED * dt);
				target -= up * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(17)) // -y
		{
			position -= up * (float)(MOVEMENT_SPEED * dt);
			target -= up * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f) {
				position += up * (float)(MOVEMENT_SPEED * dt);
				target += up * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_LSHIFT))
		{
			MOVEMENT_SPEED = 60.0f;
		}
		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}
		else
		{
			MOVEMENT_SPEED = 30.0f;
		}

		prevX = Application::GetCursorX();
		prevY = Application::GetCursorY();
	}
	else
	{
		static const float CAMERA_SPEED = 1.0f;
		static float MOVEMENT_SPEED = 20.0f;

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

		Vector3 view1(view.x, view.y, view.z);
		position += view1 * (float)(MOVEMENT_SPEED * dt);
		target += view1 * (float)(MOVEMENT_SPEED * dt);
		if (position.x >= SkyboxSize || position.x <= -SkyboxSize || position.z >= SkyboxSize || position.z <= -SkyboxSize || target.x >= SkyboxSize || target.x <= -SkyboxSize || target.z >= SkyboxSize || target.z <= -SkyboxSize || position.y >= SkyboxSize || position.y <= -SkyboxSize || target.y >= SkyboxSize || target.y <= -SkyboxSize) {
			position -= view1 * (float)(MOVEMENT_SPEED * dt);
			target -= view1 * (float)(MOVEMENT_SPEED * dt);
		}

		if (Application::IsKeyPressed(VK_UP))
		{
			if (up.y > 0)
			{
				if (vertMove != 30)
					vertMove += (double)(2.0*CAMERA_SPEED);
				else
					vertMove = 30;
			}
		}
		if (Application::IsKeyPressed(VK_DOWN))
		{
			if (vertMove != -20)
				vertMove -= (double)(2.0*CAMERA_SPEED);
			else
				vertMove = -20;
		}
		if (Application::IsKeyPressed(VK_LEFT))
		{
			if (horizMove != -20)
				horizMove -= (double)(2.0*CAMERA_SPEED);
			else
				horizMove = -20;
		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			if (horizMove != 20)
				horizMove += (double)(2.0*CAMERA_SPEED);
			else
				horizMove = 20;
		}
		if (Application::IsKeyPressed(VK_LSHIFT))
		{
			MOVEMENT_SPEED = 50.0f;
		}

		//If not pressing Down, automatically pitch downwards
		if (!Application::IsKeyPressed(VK_DOWN))
		{
			if (up.y > 0)
			{
				if (!Application::IsKeyPressed(VK_UP))
				{
					if (vertMove < 10)
						vertMove += (double)(2.0*CAMERA_SPEED);
				}
			}
			else
			{
				vertMove = 0;
			}
		}

		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}
		if (Application::IsKeyPressed('I'))
		{
			PrintInfo = false;
		}


		//Print out camera info in console
		if (PrintInfo)
		{
			std::cout << "Position : " << position << std::endl;
			std::cout << "Target : " << target << std::endl;
			std::cout << "Up : " << up << std::endl;
			std::cout << "View : " << view << std::endl;
		}
	}
}

void CameraFPV::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;

	horizMove = 0.0;
	vertMove = 0.0;
}




//Code Snippet For Rotation//
//Mtx44 rotation;
//Vector3 view = (target - position).Normalized();
//rotation.SetToRotation(-rotateAngle, 0, 1, 0);
//view = rotation * view;
//target = position + view;