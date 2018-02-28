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
#include <time.h>
#include "Inventory.h"

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
		GEO_PORTAL,

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

		GEO_PLACEHOLDER_UI_WHITE,
		GEO_PLACEHOLDER_UI_BLACK,
		GEO_PLACEHOLDER_GETTING_FRUITS_GAME_OBJECT,

		GEO_FERN,
		GEO_TREE,
		GEO_ROCK,
		GEO_BORDER,
		GEO_PTERO1,
		GEO_PTERO2,
		GEO_PTERO3,
		GEO_PTERO4,

		NUM_GEOMETRY,
	};

	enum OBJECTS
	{
		OBJ_WHEELBARROW,
		OBJ_TREE1,
		OBJ_TREE2,
		OBJ_TREE3,
		OBJ_ROCK1,
		OBJ_ROCK2,
		OBJ_ROCK3,

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
	bool isLoading;

	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	bool bushesHarvested[5];

	// Keep storage of all trap states //
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

	// Toggle for Inv Overlay //
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
	
	float ptero1LocationX = 0;
	float ptero1LocationZ = 0;
	float ptero1Direction = 0;
	float ptero2LocationX = 0;
	float ptero2LocationZ = 0;
	float ptero2Direction = 90;
	float ptero3LocationX = 0;
	float ptero3LocationZ = 0;
	float ptero3Direction = 180;
	float ptero4LocationX = 0;
	float ptero4LocationZ = 0;
	float ptero4Direction = 270;

	int fruitsWon = 0;					// Number of fruits won in a game
	int gameStartDelay = 0;				// Stop instant press at the start
	int fruitMovingPosition = 0;		// The moving position of the object 
	int fruitsGameDifficulty = 1;		// Difficulty of the getting fruits game
	void RenderGettingFruitsGameUI();	// To render the UI for the getting fruits game
	bool inGettingFruitsGame = false;	// Check if the player is in the getting fruits game
	bool fruitMoveTowardsLeft = false;	// If true, the object will move left until the edge then it will swap

	bool getFruuts(int fruitsWon);

	bool godlights = false;
};
#endif