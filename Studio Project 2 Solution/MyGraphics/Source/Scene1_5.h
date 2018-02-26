#ifndef SCENE_1_5_H
#define SCENE_1_5_H

#include "Scene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "CameraFPV.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "RingObject.h"
#include "timer.h"
#include "Scene2.h"

#include <stdlib.h>
#include <time.h>

class Scene1_5 : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,

	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_2DQUAD,
		GEO_SPHERE1,
		GEO_LIGHTBALL,
		GEO_KNUCKL,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		//Scene1_5 Models
		GEO_GOAL,
		GEO_DINO,
		GEO_TREE,
		GEO_CLIFF,
		GEO_BORDER,
		GEO_CLOUD,
		GEO_TEXT,

		NUM_GEOMETRY
	};

	enum OBJECTS
	{
		//Cloud Obstacles
		OBJ_CLOUD0,
		OBJ_CLOUD1,
		OBJ_CLOUD2,
		OBJ_CLOUD3,
		OBJ_CLOUD4,
		OBJ_CLOUD5,
		OBJ_CLOUD6,
		OBJ_CLOUD7,
		OBJ_CLOUD8,
		OBJ_CLOUD9,
		OBJ_CLOUD10,
		OBJ_CLOUD11,
		OBJ_CLOUD12,
		OBJ_CLOUD13,
		OBJ_CLOUD14,
		OBJ_CLOUD15,
		OBJ_CLOUD16,
		OBJ_CLOUD17,
		OBJ_CLOUD18,
		OBJ_CLOUD19,
		OBJ_CLOUD20,

		OBJ_GOAL, //Put at last

		NUM_OBJECTS,
	};

	Mesh* meshList[NUM_GEOMETRY];

public:
	Scene1_5();
	~Scene1_5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	double framerate;

	CameraFPV camera;
	MS modelStack, viewStack, projectionStack;
	RingObject objs[NUM_OBJECTS];

	Light light[4];
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(float, bool);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey, float, float);

	bool collision(Vector3);
	bool godlights;
	bool reachedGoal;

	void collideRing(Vector3);
	int points;
	int totalTime;

	float SkyboxSize;

	Vector3 goalpos;

	StopWatch timer;
};
#endif