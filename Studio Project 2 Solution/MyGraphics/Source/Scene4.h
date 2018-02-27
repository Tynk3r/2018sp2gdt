#ifndef SCENE_4_H
#define SCENE_4_H

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
#include "NPC.h"
#include "Shop.h"
#include "Inventory.h"

#include <iostream>
#include <fstream>

class Scene4 : public Scene
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

		GEO_NPC_HUNTER,
		GEO_NPC_SHOP,

		GEO_TREE,
		GEO_FERN,
		GEO_PORTAL,

		GEO_PTERO1,
		GEO_PTERO2,
		GEO_PTERO3,
		GEO_PTERO4,

		///////////////////////////////////////////////////////// START OF INVENTORY MESH CODE /////////////////////////////////////////////////////////
		GEO_INV_REDFRUIT,
		GEO_INV_BLUFRUIT,
		GEO_INV_MEAT,
		GEO_INV_TRAP,
		GEO_INV_INCUBATOR,
		GEO_INV_CURRENCY,
		GEO_INV_INTERFACE,
		///////////////////////////////////////////////////////// END OF INVENTORY MESH CODE /////////////////////////////////////////////////////////

		GEO_PLACEHOLDER_NPC,
		GEO_PLACEHOLDER_TEXT_BOX1,
		GEO_PLACEHOLDER_TEXT_BOX2,

		GEO_SHOP_INTERFACE,
		GEO_SHOP_AMOUNT,

		GEO_TEXT,
		NUM_GEOMETRY,
	};
	Mesh* meshList[NUM_GEOMETRY];

	enum OBJECTS
	{
		NUM_OBJECTS,
	};

public:
	Scene4();
	~Scene4();

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
	int textBoxRender;

	Light light[4];
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(float, bool);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);

	bool collision(Vector3);
	void textCollision();

	NPC npc;
	void RenderNPC();
	void RenderTextBox();
	void RenderShopTextBox();
	void loadText(int npc_type, std::string text[3]);

	bool godlights = false;
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

	// For shop
	SHOP shop;
	bool clicked = false;
	int clickedDelay = 0;			// Prevent the double click buy/sell
	int itemAmount = 0;				// The quantity of a item that the player wants to buy/sell
	bool shopping = false;			// If the player is in the process of shopping (Switch to mouse controls)

	// For conversations
	int conversationStage;			// The stage of the conversation
	
	int jokeNpcNum;					// For randomizing jokes
	int racingNpcNum;				// For randomizing tips for racing
	
	int giantFactionQuest = 1;		// The quest number for the giant faction
	bool giantQuestDone = false;	// If the quest has been done for the giant faction
	bool giantChangedQuest = false;	// Used for faction quests dialogue, updates text based on ongoing quest for the giant faction

	int speedFactionQuest = 1;		// The quest status for the speed faction
	bool speedQuestDone = false;	// If the quest has been done for the speed faction
	bool speedChangedQuest = false;	// Used for faction quests dialogue, updates text based on ongoing quest for the speed faction

	int continueDelay;				// Prevent the double key press during conversations					
};
#endif