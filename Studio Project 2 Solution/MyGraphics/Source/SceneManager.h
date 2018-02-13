#pragma once
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <iostream> //to print out errors/warnings
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
	void AddScene(Scene *scene); //SCENE POINTER HAS TO ALREADY BE NEWED
	void SetNextScene(int sceneID);
	void Update(StopWatch*, bool Exiting = false);
	int GetSceneID();
	enum SCENE_ID
	{
		SCENEID_MAIN,
		SCENEID_1,

		SCENEID_AMTOFSCENES //dont remove dis
	};
};

//a.It uses a private std::vector(or std::map) to store the scenes
//b.It has private variables int currSceneID, nextSceneID which are initialized to 0
//c.It uses a public method AddScene(Scene *scene) to add pointer to a scene
//d.It has a public method SetNextScene(int sceneID) to set nextSceneID
//e.It has a public method Update(), that does what Application::Run() while loop was doing
//f.Call SceneManager::Update() in Application::Run()
//e. henlo i wuzz here\

/* ####################################### instructions for any1 #######################################
//git gud
//add into the SCENE_ID enum ur scenes ur GONNA USE in the game (ex. im usin sceneassign2 so i put in SCENEID_ASSIGN2)
//call AddScene at Application::Init() preferably at the last few codes, and add in the scenes IN THE ORDER YOU PUT YOUR ENUMS (i call AddScene(new SceneAssign2()) first becuz its the first thing in the enum)
//scene pointer arguement for AddScene() has to already be "newed" with that specific scene child class (ex. Scene* sceneassign2 = new SceneAssign2();) (or u can do AddScene(new SceneAssign2());)

// $$$important i guess$$$
//Main Loop
---Scene *scene = new SceneAssign2();
---scene->Init();
m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
{
---scene->Update(m_timer.getElapsedTime());
---scene->Render();
+++SceneManager::instance()->Update(&m_timer);
//Swap buffers
glfwSwapBuffers(m_window);
//Get and organize events, like keyboard and mouse input, window resizing, etc...
glfwPollEvents();
m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.

} //Check if the ESC key had been pressed or if the window had been closed
---scene->Exit();
---delete scene;
+++SceneManager::instance()->Update(&m_timer, true);

//above is the Application::Run(),
//change the stuff so the --- is commented out and +++ is added in

//reminder that SceneManager is singleton designed, so only one object of scenemanager exists, and you access that via SceneManager::instance()
//also reminder that this thing has very little capability of tellin u when u did somethin wrong, but
//if u did do somethin wrong, it could possibly warn you in the black console output
//any other enquiries jus ask me i guess
//hav fun l0l

//coded by coen
*/
#endif