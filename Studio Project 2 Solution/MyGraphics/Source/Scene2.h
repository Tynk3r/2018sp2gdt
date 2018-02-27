#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "CameraFPV.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "Object.h"
#include "MyPtero.h"

class Scene2 : public Scene
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

		U_LIGHTENABLED,
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
		GEO_FRONT,
		GEO_BACK,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_QUAD,
		GEO_TEXT,
		GEO_DINOEGG,
		GEO_PTERO,
		GEO_FENCE,
		GEO_CAMPFIRE_BASE,
		GEO_CAMPFIRE_WOOD,
		GEO_SKELETON,
		GEO_INCUBATOR,
		GEO_HEART,
		GEO_NEST,
		GEO_MEAT,
		GEO_PORTAL,
		GEO_MONITOR,
		GEO_TREE,
		GEO_ROCK,

		///////////////////////////////////////////////////////// START OF INVENTORY MESH CODE /////////////////////////////////////////////////////////
		GEO_INV_REDFRUIT,
		GEO_INV_BLUFRUIT,
		GEO_INV_MEAT,
		GEO_INV_TRAP,
		GEO_INV_INCUBATOR,
		GEO_INV_CURRENCY,
		GEO_INV_INTERFACE,
		///////////////////////////////////////////////////////// END OF INVENTORY MESH CODE /////////////////////////////////////////////////////////

		NUM_GEOMETRY,
	};
	Mesh* meshList[NUM_GEOMETRY];

	enum OBJECTS
	{
		OBJ_FENCE,
		OBJ_CAMPFIRE,
		OBJ_SKELETON,
		OBJ_INCUBATOR,

		NUM_OBJECTS,
	};

public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	double framerate;
	bool godlights = true;
	float rotateMain = 0;
	bool feeding = false;
	float meatLocationX = 0;
	float meatLocationZ = 62.5;
	float meatLocationY = 0;
	int feedingDelay = 0;

	CameraFPV camera;
	MS modelStack, viewStack, projectionStack;
	Object objs[NUM_OBJECTS];
	Light light[2];

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(float, bool);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	bool collision(Vector3);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
};

#endif