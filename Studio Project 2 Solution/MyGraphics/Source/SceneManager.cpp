#include "SceneManager.h"

SceneManager* SceneManager::SM_Instance = nullptr;

SceneManager::SceneManager()
{
	this->currSceneID = this->nextSceneID = 0;
	this->bFirstUsage = true;
}

SceneManager* SceneManager::instance(void)
{
	if (SceneManager::SM_Instance == nullptr)
	{
		SceneManager::SM_Instance = new SceneManager();
	}
	return SceneManager::SM_Instance;
}

void SceneManager::AddScene(Scene* scene)
{
	this->SC_SceneList.push_back(scene);
}

void SceneManager::SetNextScene(int sceneID)
{
	this->nextSceneID = sceneID;
}

void SceneManager::Update(StopWatch *m_timer,bool Exiting)
{
	if (Exiting)
	{
		this->SC_SceneList[this->currSceneID]->Exit();
		for (int i = 0; i < this->SC_SceneList.size(); i++)
		{
			Scene* tempsc = this->SC_SceneList[i];
			this->SC_SceneList.erase(this->SC_SceneList.begin() + i);
			delete tempsc;
			i--;
		}
		return;
	}
	else
	{
		if (this->bFirstUsage)
		{
			this->currSceneID = this->nextSceneID;
			this->SC_SceneList[this->currSceneID]->Init();
			this->bFirstUsage = false;
		}
		if (this->nextSceneID != this->currSceneID)
		{
			this->SC_SceneList[this->currSceneID]->Exit();
			this->currSceneID = this->nextSceneID;
			this->SC_SceneList[this->currSceneID]->Init();
		}
		this->SC_SceneList[this->currSceneID]->Update(m_timer->getElapsedTime());
		this->SC_SceneList[this->currSceneID]->Render();
	}
	if (this->SC_SceneList.size() != SCENEID_AMTOFSCENES)
	{
		std::cout << "WARNING! Amount of scenes in vector does not match up with amount of scenes in enum!" << std::endl;
		return;
	}
}

int SceneManager::GetSceneID()
{
	return this->nextSceneID;
}