#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <iostream>
#include "Scene.h"
#include "timer.h"
class SceneManager
{
private:
	
	int currSceneID;
	int nextSceneID;
	bool bFirstUsage;
	static SceneManager *SM_Instance;
	SceneManager();
public:
	std::vector<Scene*> SC_SceneList;
	static SceneManager* instance(void);
	void AddScene(Scene *scene);
	void SetNextScene(int sceneID);
	void Update(StopWatch*, bool Exiting = false);
	int GetSceneID();
	enum SCENE_ID
	{
		SCENEID_MAIN,
		SCENEID_1,
		SCENEID_2,
		SCENEID_3,
		SCENEID_4,
		SCENEID_1_5,

		SCENEID_AMTOFSCENES,
	};
};
#endif