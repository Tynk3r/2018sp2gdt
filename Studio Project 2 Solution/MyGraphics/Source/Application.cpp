
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneMain.h"
#include "Scene1.h"
#include "Scene4.h"
#include "SceneManager.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

double Application::CursorX = 0.0;
double Application::CursorY = 0.0;
int Application::WindowWidth = 2;
int Application::WindowHeight = 2;
void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1200, 800, "Computer Graphics", NULL, NULL);
	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowSizeCallback(m_window, resize_callback);
	//GLFWimage imgs[2];
	//imgs[0] = load_icon("Image//mybaby.png");
	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
	SceneManager::instance()->AddScene(new SceneMain());
	SceneManager::instance()->AddScene(new Scene1());
	SceneManager::instance()->AddScene(new Scene4());
}

void Application::Run()
{
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		SceneManager::instance()->Update(&m_timer);
		//Swap buffers
		glfwSwapBuffers(m_window);
		glfwGetCursorPos(m_window, &CursorX, &CursorY);
		//std::cout << CursorX << " " << CursorY << std::endl;
		glfwGetWindowSize(m_window, &WindowWidth, &WindowHeight);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	SceneManager::instance()->Update(&m_timer, true);
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::SetCursorVisible(bool yett)
{
	if (!yett)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

double Application::GetCursorX(void)
{
	return (Application::CursorX);
}
double Application::GetCursorY(void)
{
	return (Application::CursorY);
}
int Application::GetWindowWidth(void)
{
	return (Application::WindowWidth);
}
int Application::GetWindowHeight(void)
{
	return (Application::WindowHeight);
}