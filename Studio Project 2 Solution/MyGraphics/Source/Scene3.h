#ifndef SCENE_3_H
#define SCENE_3_H

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
#include "bush.h"
#include <time.h>
#include "Inventory.h"

//THIS IS THE SP FOLDER VERSION//
//THIS ONE IS TO BE MODIFIED FOR RELEASE//

class Scene3 : public Scene
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
		GEO_TRAPDEFAULT,
		GEO_TRAPCAUGHT,
		GEO_BUSH,
		GEO_REDFRUIT,
		GEO_BLUFRUIT,
		GEO_WHEELBARROW,
		GEO_EXPLAINTEXT,
		GEO_INSTRUCTIONS,
		
		///////////////////////////////////////////////////////// START OF INVENTORY MESH CODE /////////////////////////////////////////////////////////
		GEO_INV_REDFRUIT,
		GEO_INV_BLUFRUIT,
		GEO_INV_MEAT,
		GEO_INV_TRAP,
		GEO_INV_INCUBATOR,
		GEO_INV_CURRENCY,
		GEO_INV_INTERFACE,
		///////////////////////////////////////////////////////// END OF INVENTORY MESH CODE /////////////////////////////////////////////////////////
		
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	enum OBJECTS
	{
		OBJ_X,

		NUM_OBJECTS,
	};

	enum TRAP_STATE
	{
		TRAP_NONE,
		TRAP_PLACED,
		TRAP_TRAPPED,
		NUM_TRAP_STATE,
	};

	Mesh* meshList[NUM_GEOMETRY];

public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	//Classes for bushes//
	bush bush1;
	bush bush2;
	bush bush3;
	bush bush4;
	bush bush5;

	//Keep storage of all trap states//
	int trap1State;
	int trap2State;
	int trap3State;
	int trap4State;
	int trap5State;

	bool trappedBush1;
	bool trappedBush2;
	bool trappedBush3;
	bool trappedBush4;
	bool trappedBush5;

	//Toggle for Inv Overlay//
	bool showInventory = false;

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
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	bool collision(Vector3);
	float rotateMain = 0;

	bool getFruuts();

	bool godlights = false;
};
#endif