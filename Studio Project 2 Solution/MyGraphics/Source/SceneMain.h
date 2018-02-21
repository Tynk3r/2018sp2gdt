#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

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

#include "Inventory.h"


class SceneMain : public Scene
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
		GEO_TREE,
		GEO_FERN,
		GEO_ROCK,
		GEO_FIREBASE,
		GEO_FIREWOOD,
		GEO_BORDER,
		GEO_EASTER1,
		
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
		OBJ_DINOEGG = 0,
		OBJ_TREE1,
		OBJ_TREE2,
		OBJ_TREE3,
		OBJ_ROCK1,
		OBJ_ROCK2,
		OBJ_ROCK3,
		OBJ_CAMPFIRE,

		NUM_OBJECTS,
	};

public:
	SceneMain();
	~SceneMain();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	double framerate;
	float rotateMain = 0;
	bool godlights = true;

	CameraFPV camera;
	MS modelStack, viewStack, projectionStack;
	Object objs[NUM_OBJECTS];
	Light light[3];

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(float, bool);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	bool collision(Vector3);
};
#endif