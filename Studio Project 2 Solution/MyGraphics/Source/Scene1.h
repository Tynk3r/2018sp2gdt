#ifndef SCENE_1_H
#define SCENE_1_H

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
//#include <irrKlang.h>

class Scene1 : public Scene
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
		
		//Scene1 Models
		GEO_RING,
		GEO_SMALLRING,
		GEO_DINO,
		GEO_TREE,
		GEO_CLIFF,

		GEO_TEXT,

		NUM_GEOMETRY
	};

	enum OBJECTS
	{
		//Red Rings
		OBJ_RING0,
		OBJ_RING1,
		OBJ_RING2,
		OBJ_RING3,
		OBJ_RING4,
		OBJ_RING5,
		OBJ_RING6,
		OBJ_RING7,
		OBJ_RING8,
		OBJ_RING9,
		OBJ_RING10,
		OBJ_RING11,
		OBJ_RING12,
		OBJ_RING13,
		OBJ_RING14,
		OBJ_RING15,
		OBJ_RING16,
		OBJ_RING17,
		OBJ_RING18,
		OBJ_RING19,
		//Blue Ring
		OBJ_RING20,

		NUM_OBJECTS,
	};

	Mesh* meshList[NUM_GEOMETRY];

public:
	Scene1();
	~Scene1();

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
	void HandleRingCollide(int);

	bool collision(Vector3);

	int collideRing(Vector3);

	bool godlights = false;

	int currentRing;
	int points;
	int totalTime;

	Vector3 ringpos;
	StopWatch timer;
};
#endif