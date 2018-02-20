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
		GEO_PTERO,
		GEO_FENCE,
		GEO_REDINV,
		GEO_BLUINV,
		GEO_TRAPINV,
		GEO_INVINTERFACE,
		GEO_CAMPFIRE_BASE,
		GEO_CAMPFIRE_WOOD,
		GEO_SKELETON,
		GEO_INCUBATOR,
		
		NUM_GEOMETRY,
	};
	Mesh* meshList[NUM_GEOMETRY];

	enum OBJECTS
	{
		OBJ_DINOEGG,
		OBJ_PTERO_BABY,
		OBJ_PTERO_ADOLESCENT, 
		OBJ_PTERO_ADULT,
		OBJ_FENCE,
		OBJ_CAMPFIRE,
		OBJ_SKELETON,
		OBJ_INCUBATOR,

		NUM_OBJECTS,
	};

	//enum PTERO_STATE {
	//	P_EGG = 0,
	//	P_BABY,
	//	P_ADOLESCENT,
	//	P_ADULT,
	//};

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

	CameraFPV camera;
	MS modelStack, viewStack, projectionStack;
	Object objs[NUM_OBJECTS];

	Light light[3];
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(float, bool);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	bool collision(Vector3);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	float rotateMain = 0;

	float pteroLocationX = 0;
	float pteroLocationZ = 62.5;
	
	bool godlights = false;
};
#endif