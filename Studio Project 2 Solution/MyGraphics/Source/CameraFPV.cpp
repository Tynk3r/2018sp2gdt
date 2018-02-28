#include "CameraFPV.h"
#include "SceneManager.h"
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
	////////////////////          START OF WALKING CAMERA CODE          ////////////////////
	if (SceneManager::instance()->GetSceneID() == SceneManager::SCENEID_MAIN ||
		SceneManager::instance()->GetSceneID() == SceneManager::SCENEID_2 ||
		SceneManager::instance()->GetSceneID() == SceneManager::SCENEID_3 ||
		SceneManager::instance()->GetSceneID() == SceneManager::SCENEID_4)
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

		up = rotation * up;

		double pitch = (vertMove*dt) / 25.0f;
		target = target + Vector3(-up.x*pitch, -up.y*pitch, -up.z*pitch);

		if (target.y < (position.y - 0.7))
		{
			target = target - Vector3(-up.x*pitch, -up.y*pitch, -up.z*pitch);
		}
		if (target.y >(position.y + 0.7))
		{
			target = target - Vector3(-up.x*pitch, -up.y*pitch, -up.z*pitch);
		}
		//Basic WASD Movement
		if (Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D')) // right
		{
			position += right * (float)(MOVEMENT_SPEED * dt);
			target += right * (float)(MOVEMENT_SPEED * dt);
			if (SceneManager::instance()->SC_SceneList[SceneManager::instance()->GetSceneID()]->collision(position)) 
			{
				position -= right * (float)(MOVEMENT_SPEED * dt);
				target -= right * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')) // left
		{
			position -= right * (float)(MOVEMENT_SPEED * dt);
			target -= right * (float)(MOVEMENT_SPEED * dt);
			if (SceneManager::instance()->SC_SceneList[SceneManager::instance()->GetSceneID()]->collision(position))
			{
				position += right * (float)(MOVEMENT_SPEED * dt);
				target += right * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // front
		{
			Vector3 view1(view.x, 0, view.z);
			position += view1 * (float)(MOVEMENT_SPEED * dt);
			target += view1 * (float)(MOVEMENT_SPEED * dt);
			if (SceneManager::instance()->SC_SceneList[SceneManager::instance()->GetSceneID()]->collision(position))
			{
				position -= view1 * (float)(MOVEMENT_SPEED * dt);
				target -= view1 * (float)(MOVEMENT_SPEED * dt);
			}

		}
		if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // back
		{
			Vector3 view1(view.x, 0, view.z);
			position -= view1 * (float)(MOVEMENT_SPEED * dt);
			target -= view1 * (float)(MOVEMENT_SPEED * dt);
			if (SceneManager::instance()->SC_SceneList[SceneManager::instance()->GetSceneID()]->collision(position))
			{
				position += view1 * (float)(MOVEMENT_SPEED * dt);
				target += view1 * (float)(MOVEMENT_SPEED * dt);
			}
		}
		//Sprinting
		if (Application::IsKeyPressed(VK_LSHIFT))
		{
			switch (SceneManager::instance()->GetSceneID())
			{
			case SceneManager::SCENEID_2:
				MOVEMENT_SPEED = 50.0f;
				break;
			default:
				MOVEMENT_SPEED = 100.0f;
				break;
			}
		}
		else
		{
			switch (SceneManager::instance()->GetSceneID())
			{
			case SceneManager::SCENEID_2:
				MOVEMENT_SPEED = 25.0f;
				break;
			default:
				MOVEMENT_SPEED = 50.0f;
				break;
			}
		}
		//Reset
		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}

		if ((target.y < (position.y - 0.7)) || (target.y > (position.y + 0.7)))
		{
			Reset();
		}
		//Mouse Camera Control
		prevX = Application::GetCursorX();
		prevY = Application::GetCursorY();
	}
	////////////////////          END OF WALKING CAMERA CODE          ////////////////////

	////////////////////          START OF FLYING CAMERA CODE          ////////////////////
	else if (SceneManager::instance()->GetSceneID() == SceneManager::SCENEID_1 || 
			 SceneManager::instance()->GetSceneID() == SceneManager::SCENEID_1_5) 
	{
		//Set Camera Speed for Scene1
		static const float CAMERA_SPEED = 1.0f;
		static float MOVEMENT_SPEED = 30.0f;
		static float BASE_SPEED = 30.0f;

		//Set Camera Variables
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Vector3 front = right.Cross(up);
		front.Normalize();

		Mtx44 rotation;

		//Yawing
		double yaw = -horizMove*dt;
		rotation.SetToRotation(yaw, up.x, up.y, up.z);
		view = rotation*view;
		target = position + view;

		//Pitching
		double pitch = (vertMove*dt) / 25.0f;
		target = target + Vector3(-up.x*pitch, -up.y*pitch, -up.z*pitch);

		//Rolling
		double roll = rollMove*dt;
		rotation.SetToRotation(roll, view.x, view.y, view.z);

		//Auto Movement in Direction
		Vector3 view1(view.x, view.y, view.z);
		position += view1 * (float)(MOVEMENT_SPEED * dt);
		target += view1 * (float)(MOVEMENT_SPEED * dt);
		if (SceneManager::instance()->SC_SceneList[SceneManager::instance()->GetSceneID()]->collision(position))
		{
			position -= view1 * (float)(MOVEMENT_SPEED * dt);
			target -= view1 * (float)(MOVEMENT_SPEED * dt);
		}
		if (Application::IsKeyPressed('W'))
		{
			if (up.y > 0)
			{
				if (vertMove != 30)
					vertMove += (double)(2.0*CAMERA_SPEED);
				else
					vertMove = 30;
			}
		}
		if (Application::IsKeyPressed('S'))
		{
			if (vertMove != -20)
				vertMove -= (double)(2.0*CAMERA_SPEED);
			else
				vertMove = -20;
		}
		if (Application::IsKeyPressed('A'))
		{
			if (horizMove != -20)
				horizMove -= (double)(2.0*CAMERA_SPEED);
			else
				horizMove = -20;
		}
		if (Application::IsKeyPressed('D'))
		{
			if (horizMove != 20)
				horizMove += (double)(2.0*CAMERA_SPEED);
			else
				horizMove = 20;
		}
		if (Application::IsKeyPressed(VK_LSHIFT))
		{
			switch (MyPtero::instance()->pteroStage)
			{
			case MyPtero::P_BABY:
				MOVEMENT_SPEED = BASE_SPEED*(MyPtero::instance()->pteroSpeedModifier)*0.7;
			case MyPtero::P_ADOLESCENT:
				MOVEMENT_SPEED = BASE_SPEED*(MyPtero::instance()->pteroSpeedModifier + 0.75)*0.5;
			case MyPtero::P_ADULT:
				MOVEMENT_SPEED = BASE_SPEED*(MyPtero::instance()->pteroSpeedModifier + 1.25)*0.2;
			}
		}
		else
		{
			switch (MyPtero::instance()->pteroStage)
			{
			case MyPtero::P_BABY:
				MOVEMENT_SPEED = BASE_SPEED*(MyPtero::instance()->pteroSpeedModifier);
			case MyPtero::P_ADOLESCENT:
				MOVEMENT_SPEED = BASE_SPEED*(MyPtero::instance()->pteroSpeedModifier + 0.75);
			case MyPtero::P_ADULT:
				MOVEMENT_SPEED = BASE_SPEED*(MyPtero::instance()->pteroSpeedModifier + 1.25);
			}
		}

		//If not pressing Down, automatically pitch downwards
		if (!Application::IsKeyPressed('S'))
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
	}

	//////////////////            END OF FLYING CAMERA CODE          ////////////////////

	//////////////////            START OF DEFAULT CAMERA CODE          ////////////////////
	else {
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
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f)
			{
				position -= right * (float)(MOVEMENT_SPEED * dt);
				target -= right * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')) // left
		{
			position -= right * (float)(MOVEMENT_SPEED * dt);
			target -= right * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f)
			{
				position += right * (float)(MOVEMENT_SPEED * dt);
				target += right * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) // front
		{
			Vector3 view1(view.x, 0, view.z);
			position += view1 * (float)(MOVEMENT_SPEED * dt);
			target += view1 * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f)
			{
				position -= view1 * (float)(MOVEMENT_SPEED * dt);
				target -= view1 * (float)(MOVEMENT_SPEED * dt);
			}

		}
		if (Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) // back
		{
			Vector3 view1(view.x, 0, view.z);
			position -= view1 * (float)(MOVEMENT_SPEED * dt);
			target -= view1 * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f)
			{
				position += view1 * (float)(MOVEMENT_SPEED * dt);
				target += view1 * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(' ')) // +y
		{
			position += up * (float)(MOVEMENT_SPEED * dt);
			target += up * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f)
			{
				position -= up * (float)(MOVEMENT_SPEED * dt);
				target -= up * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(17)) // -y
		{
			position -= up * (float)(MOVEMENT_SPEED * dt);
			target -= up * (float)(MOVEMENT_SPEED * dt);
			if (position.x >= 200.0f || position.x <= -200.0f || position.z >= 200.0f || position.z <= -200.0f || target.x >= 200.0f || target.x <= -200.0f || target.z >= 200.0f || target.z <= -200.0f || position.y >= 200.0f || position.y <= -200.0f || target.y >= 200.0f || target.y <= -200.0f)
			{
				position += up * (float)(MOVEMENT_SPEED * dt);
				target += up * (float)(MOVEMENT_SPEED * dt);
			}
		}
		if (Application::IsKeyPressed(VK_LSHIFT))
		{
			MOVEMENT_SPEED = 80.0f;
		}
		else
		{
			MOVEMENT_SPEED = 30.0f;
		}
		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}

		prevX = Application::GetCursorX();
		prevY = Application::GetCursorY();
	}
	//////////////////            END OF DEFAULT CAMERA CODE          ////////////////////
}

void CameraFPV::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;

	horizMove = 0.0;
	vertMove = 0.0;
}