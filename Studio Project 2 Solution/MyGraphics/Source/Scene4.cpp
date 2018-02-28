#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	framerate = 0.0f;
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);

	camera.Init(Vector3(0, 20, 20), Vector3(0, 0, 1), Vector3(0, 1, 0)); // Init camera

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 10, 3);
	light[0].color.Set(0.898, 0.627, 0.125);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(2, 2, 2);
	light[1].color.Set(0.898, 0.627, 0.125);
	light[1].power = 2;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	light[2].type = Light::LIGHT_DIRECTIONAL;
	light[2].position.Set(-1, -1, -1);
	light[2].color.Set(0.823, 0.466, 0.058);
	light[2].power = 2;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init VBO here
	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_FRONT] = MeshBuilder::Generate2DQuad("front", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//mainfront.tga");
	meshList[GEO_BACK] = MeshBuilder::Generate2DQuad("back", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//mainback.tga");
	meshList[GEO_LEFT] = MeshBuilder::Generate2DQuad("left", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//mainleft.tga");
	meshList[GEO_RIGHT] = MeshBuilder::Generate2DQuad("right", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//mainright.tga");
	meshList[GEO_TOP] = MeshBuilder::Generate2DQuad("top", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//maintop.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::Generate2DQuad("bottom", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//mainbottom.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//tree.tga");

	meshList[GEO_FERN] = MeshBuilder::GenerateOBJ("fern", "OBJ//fern.obj");
	meshList[GEO_FERN]->textureID = LoadTGA("Image//fern.tga");

	meshList[GEO_BORDER] = MeshBuilder::GenerateOBJ("border", "OBJ//border.obj");
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//rock1.tga");

	meshList[GEO_PORTAL] = MeshBuilder::Generate2DQuad("portal", 1.0f, 1.0f, 0.f, 0.f, 0.f);
	meshList[GEO_PORTAL]->textureID = LoadTGA("Image//portal1.tga");

	///////////////////////////////////////////////////////// START OF INVENTORY MESH CODE /////////////////////////////////////////////////////////
	meshList[GEO_INV_REDFRUIT] = MeshBuilder::GenerateText("invRedFruit", 16, 16);
	meshList[GEO_INV_REDFRUIT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_BLUFRUIT] = MeshBuilder::GenerateText("invBluFruit", 16, 16);
	meshList[GEO_INV_BLUFRUIT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_MEAT] = MeshBuilder::GenerateText("invMeat", 16, 16);
	meshList[GEO_INV_MEAT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_TRAP] = MeshBuilder::GenerateText("invTrap", 16, 16);
	meshList[GEO_INV_TRAP]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_INCUBATOR] = MeshBuilder::GenerateText("invIncubator", 16, 16);
	meshList[GEO_INV_INCUBATOR]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_CURRENCY] = MeshBuilder::GenerateText("invCurrency", 16, 16);
	meshList[GEO_INV_CURRENCY]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_INTERFACE] = MeshBuilder::Generate2DQuad("InvInterface", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	meshList[GEO_INV_INTERFACE]->textureID = LoadTGA("Image//invInterface.tga");
	///////////////////////////////////////////////////////// END OF INVENTORY MESH CODE /////////////////////////////////////////////////////////

	meshList[GEO_NPC_HUNTER] = MeshBuilder::GenerateOBJ("npc_hunter", "OBJ//NPC_Hunter.obj");
	meshList[GEO_NPC_HUNTER]->textureID = LoadTGA("Image//NPC_Hunter.tga");
	meshList[GEO_NPC_SHOP] = MeshBuilder::GenerateOBJ("npc_shop", "OBJ//NPC_Shop.obj");
	meshList[GEO_NPC_SHOP]->textureID = LoadTGA("Image//NPC_Shop.tga");
	meshList[GEO_NPC_LORE] = MeshBuilder::GenerateOBJ("npc_lore", "OBJ//NPC_Lore.obj");
	meshList[GEO_NPC_LORE]->textureID = LoadTGA("Image//NPC_Lore.tga");
	meshList[GEO_NPC_JOKER] = MeshBuilder::GenerateOBJ("npc_joker", "OBJ//NPC_Joker.obj");
	meshList[GEO_NPC_JOKER]->textureID = LoadTGA("Image//NPC_Joker.tga");

	meshList[GEO_PTERO1] = MeshBuilder::GenerateOBJ("ptero1", "OBJ//pterodactyl.obj");
	meshList[GEO_PTERO1]->textureID = LoadTGA("Image//greendino.tga");
	meshList[GEO_PTERO2] = MeshBuilder::GenerateOBJ("ptero2", "OBJ//pterodactyl.obj");
	meshList[GEO_PTERO2]->textureID = LoadTGA("Image//reddino.tga");
	meshList[GEO_PTERO3] = MeshBuilder::GenerateOBJ("ptero3", "OBJ//pterodactyl.obj");
	meshList[GEO_PTERO3]->textureID = LoadTGA("Image//purpledino.tga");
	meshList[GEO_PTERO4] = MeshBuilder::GenerateOBJ("ptero4", "OBJ//pterodactyl.obj");
	meshList[GEO_PTERO4]->textureID = LoadTGA("Image//reddino.tga");

	meshList[GEO_PLACEHOLDER_NPC] = MeshBuilder::GenerateCube("placeholderNPC", Color(1, 1, 1), 1, 5, 1);
	meshList[GEO_PLACEHOLDER_TEXT_BOX1] = MeshBuilder::Generate2DQuad("placeholderTextBox", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_PLACEHOLDER_TEXT_BOX2] = MeshBuilder::Generate2DQuad("placeholderTextBox", 1.0f, 1.0f, 0.f, 0.f, 0.f);

	meshList[GEO_SHOP_INTERFACE] = MeshBuilder::Generate2DQuad("shopInterface", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_SHOP_INTERFACE]->textureID = LoadTGA("Image//shopInterface.tga");

	meshList[GEO_SHOP_AMOUNT] = MeshBuilder::GenerateText("shopAmount", 16, 16);
	meshList[GEO_SHOP_AMOUNT]->textureID = LoadTGA("Image//calibri.tga");
}

void Scene4::Update(double dt)
{
	framerate = 1.0 / dt;
	Inventory::instance()->Update();
	npc.UpdateAll();
	shop.Update();

	////////////////////////////////////////////////////////////////// START OF QUEST CODE //////////////////////////////////////////////////////////////////
	switch (speedFactionQuest)
	{
	case 2: 
		if (Inventory::instance()->items[ITEMS_REDFRUIT] >= 30)
		{
			speedQuestDone = true;
		}
		break;
	case 3:
		if (Inventory::instance()->items[ITEMS_MEAT] >= 50)
		{
			speedQuestDone = true;
		}
		break;
	case 4:
		if (Inventory::instance()->items[ITEMS_CURRENCY] >= 500)
		{
			speedQuestDone = true;
		}
		break;
	default:
		break;
	}

	switch (giantFactionQuest)
	{
	case 2:
		if (Inventory::instance()->items[ITEMS_BLUFRUIT] >= 30)
		{
			giantQuestDone = true;
		}
		break;
	case 3:
		if ((Inventory::instance()->items[ITEMS_MEAT] >= 25) && (Inventory::instance()->items[ITEMS_TRAP] >= 25))
		{
			giantQuestDone = true;
		}
		break;
	case 4:
		if (Inventory::instance()->items[ITEMS_CURRENCY] >= 500)
		{
			giantQuestDone = true;
		}
		break;
	default:
		break;
	}
	////////////////////////////////////////////////////////////////// END OF QUEST CODE //////////////////////////////////////////////////////////////////


	if (shopping == false)
	{
		camera.Update(dt);
	}

	if (camera.position.z <= -195.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_MAIN);
	}
	if (Application::IsKeyPressed('Q')) // Turn on global light
	{
			godlights = false;
	}
	if (Application::IsKeyPressed('E')) // Turn off global light
	{
			godlights = true;
	}

	////////////////////////////////////////////////////////////////// START OF SHOP CODE //////////////////////////////////////////////////////////////////
	if (shopping == true)
	{
		Application::SetCursorVisible(true);
		if (clickedDelay == 11)
		{
			if (Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Application::GetCursorX() >= shop.coord[SHOP_EXIT].minX && Application::GetCursorX() <= shop.coord[SHOP_EXIT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_EXIT].minY && Application::GetCursorY() <= shop.coord[SHOP_EXIT].maxY)
				{
					shopping = false;
					Application::SetCursorVisible(false);
					camera.prevX = Application::GetCursorX();
					camera.prevY = Application::GetCursorY();
					clicked = true;
				}

				// Resolve amount changes
				for (int i = (SHOP_AMOUNT_START + 1); i <= SHOP_AMOUNT_END; i++)
				{
					if (Application::GetCursorX() >= shop.coord[i].minX && Application::GetCursorX() <= shop.coord[i].maxX &&
						Application::GetCursorY() >= shop.coord[i].minY && Application::GetCursorY() <= shop.coord[i].maxY)
					{
						switch (i)
						{
						case SHOP_RESET_AMOUNT:
							itemAmount = 0;
							break;
						case SHOP_INCREASE_AMOUNT_1:
							if (itemAmount <= 998)
							{
								itemAmount += 1;
							}
							else
							{
								itemAmount = 999;
							}
							break;
						case SHOP_DECREASE_AMOUNT_1:
							if (itemAmount >= 1)
							{
								itemAmount -= 1;
							}
							else
							{
								itemAmount = 0;
							}
							break;
						case SHOP_INCREASE_AMOUNT_10:
							if (itemAmount <= 989)
							{
								itemAmount += 10;
							}
							else
							{
								itemAmount = 999;
							}
							break;
						case SHOP_DECREASE_AMOUNT_10:
							if (itemAmount >= 10)
							{
								itemAmount -= 10;
							}
							else
							{
								itemAmount = 0;
							}
							break;
						case SHOP_INCREASE_AMOUNT_100:
							if (itemAmount <= 899)
							{
								itemAmount += 100;
							}
							else
							{
								itemAmount = 999;
							}
							break;
						case SHOP_DECREASE_AMOUNT_100:
							if (itemAmount >= 100)
							{
								itemAmount -= 100;
							}
							else
							{
								itemAmount = 0;
							}
							break;
						default:
							break;
						}
					}
				}

				// Resolve the shopAction
				for (int i = (SHOP_BUY_START + 1); i <= SHOP_BUY_END; i++)
				{
					if (Application::GetCursorX() >= shop.coord[i].minX && Application::GetCursorX() <= shop.coord[i].maxX &&
						Application::GetCursorY() >= shop.coord[i].minY && Application::GetCursorY() <= shop.coord[i].maxY)
					{
						int inventoryItemAffected;
						switch (i)
						{
						case SHOP_BUY_REDFRUIT:
							inventoryItemAffected = ITEMS_REDFRUIT;
							break;
						case SHOP_BUY_BLUFRUIT:
							inventoryItemAffected = ITEMS_BLUFRUIT;
							break;
						case SHOP_BUY_MEAT:
							inventoryItemAffected = ITEMS_MEAT;
							break;
						case SHOP_BUY_TRAP:
							inventoryItemAffected = ITEMS_TRAP;
							break;
						case SHOP_BUY_INCUBATOR:
							inventoryItemAffected = ITEMS_INCUBATOR;
							break;
						default:
							break;
						}
						if ((Inventory::instance()->items[inventoryItemAffected] + itemAmount) >= 999)
						{
							int tempItemAmount = 999 - Inventory::instance()->items[inventoryItemAffected];
							if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[i] * tempItemAmount))
							{
								Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[i] * tempItemAmount);
								Inventory::instance()->items[inventoryItemAffected] += tempItemAmount;
								shop.supply[i] -= tempItemAmount;
							}
						}
						else
						{
							if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[i] * itemAmount))
							{
								Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[i] * itemAmount);
								Inventory::instance()->items[inventoryItemAffected] += itemAmount;
								shop.supply[i] -= itemAmount;
							}
						}
					}
				}
				for (int i = (SHOP_SELL_START + 1); i <= SHOP_SELL_END; i++)
				{
					if (Application::GetCursorX() >= shop.coord[i].minX && Application::GetCursorX() <= shop.coord[i].maxX &&
						Application::GetCursorY() >= shop.coord[i].minY && Application::GetCursorY() <= shop.coord[i].maxY) 
					{
						int inventoryItemAffected;
						switch (i)
						{
						case SHOP_SELL_REDFRUIT:
							inventoryItemAffected = ITEMS_REDFRUIT;
							break;
						case SHOP_SELL_BLUFRUIT:
							inventoryItemAffected = ITEMS_BLUFRUIT;
							break;
						case SHOP_SELL_MEAT:
							inventoryItemAffected = ITEMS_MEAT;
							break;
						case SHOP_SELL_TRAP:
							inventoryItemAffected = ITEMS_TRAP;
							break;
						case SHOP_SELL_INCUBATOR:
							inventoryItemAffected = ITEMS_INCUBATOR;
							break;
						default:
							break;
						}
						if (Inventory::instance()->items[inventoryItemAffected] >= itemAmount)
						{
							shop.supply[i - SHOP_BUY_END] += itemAmount;
							shop.Update();
							Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[i] * itemAmount);
							Inventory::instance()->items[inventoryItemAffected] -= itemAmount;

							if (Inventory::instance()->items[ITEMS_CURRENCY] > 999)
							{
								Inventory::instance()->items[ITEMS_CURRENCY] = 999;
							}
						}
						else
						{
							int tempItemAmount = Inventory::instance()->items[inventoryItemAffected];

							shop.supply[i - SHOP_BUY_END] += itemAmount;
							shop.Update();
							Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[i] * tempItemAmount);
							Inventory::instance()->items[inventoryItemAffected] -= tempItemAmount;

							if (Inventory::instance()->items[ITEMS_CURRENCY] > 999)
							{
								Inventory::instance()->items[ITEMS_CURRENCY] = 999;
							}
						}
					}
				}
				clickedDelay = 0;
			}
		}
		else
		{
			clickedDelay++;
		}
	}
	////////////////////////////////////////////////////////////////// END OF SHOP CODE ////////////////////////////////////////////////////////////////////
	
	// Ptero movement
	int r = rand() % 200 + 1;
	switch ((int)ptero1Direction)
	{
	case 180:	// Front
		switch (r)
		{
		case 1: // Back
			ptero1LocationZ += 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ -= 1.0f;
			}
			ptero1Direction = 0.0f;
			break;
		case 2: // Right
			ptero1LocationX += 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX -= 1.0f;
			}
			ptero1Direction = 90.0f;
			break;
		case 3: // Left
			ptero1LocationX -= 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX += 1.0f;
			}
			ptero1Direction = 270.0f;
			break;
		default: // Front
			ptero1LocationZ -= 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ += 1.0f;
			}
			ptero1Direction = 180.0f;
			break;
		}
		break;
	case 90:	// Right
		switch (r)
		{
		case 1: // Back
			ptero1LocationZ += 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ -= 1.0f;
			}
			ptero1Direction = 0.0f;
			break;
		case 2: // Front
			ptero1LocationZ -= 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ += 1.0f;
			}
			ptero1Direction = 180.0f;
			break;
		case 3: // Left
			ptero1LocationX -= 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX += 1.0f;
			}
			ptero1Direction = 270.0f;
			break;
		default: // Right
			ptero1LocationX += 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX -= 1.0f;
			}
			ptero1Direction = 90.0f;
			break;
		}
		break;
	case 0:		// Back
		switch (r) {
		case 1: // Right
			ptero1LocationX += 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX -= 1.0f;
			}
			ptero1Direction = 90.0f;
			break;
		case 2: // Front
			ptero1LocationZ -= 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ += 1.0f;
			}
			ptero1Direction = 180.0f;
			break;
		case 3: // Left
			ptero1LocationX -= 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX += 1.0f;
			}
			ptero1Direction = 270.0f;
			break;
		default: // Back
			ptero1LocationZ += 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ -= 1.0f;
			}
			ptero1Direction = 0.0f;
			break;
		}
		break;
	case 270:	// Left
		switch (r) {
		case 1: // Right
			ptero1LocationX += 1.0f;
			if (ptero1LocationX <= -200.0f || ptero1LocationX >= 200.0f)
			{
				ptero1LocationX -= 1.0f;
			}
			ptero1Direction = 90.0f;
			break;
		case 2: // Front
			ptero1LocationZ -= 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ += 1.0f;
			}
			ptero1Direction = 180.0f;
			break;
		case 3: // Back
			ptero1LocationZ += 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationZ -= 1.0f;
			}
			ptero1Direction = 0.0f;
			break;
		default: // Left
			ptero1LocationX -= 1.0f;
			if (ptero1LocationZ <= -200.0f || ptero1LocationZ >= 200.0f)
			{
				ptero1LocationX += 1.0f;
			}
			ptero1Direction = 270.0f;
			break;
		}
		break;
	default:
		ptero1Direction = 180;
		break;
	}
	r = rand() % 300 + 1;
	switch ((int)ptero2Direction)
	{
	case 180:	// Front
		switch (r) {
		case 1: // Back
			ptero2LocationZ += 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ -= 1.0f;
			}
			ptero2Direction = 0.0f;
			break;
		case 2: // Right
			ptero2LocationX += 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX -= 1.0f;
			}
			ptero2Direction = 90.0f;
			break;
		case 3: // Left
			ptero2LocationX -= 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX += 1.0f;
			}
			ptero2Direction = 270.0f;
			break;
		default: // Front
			ptero2LocationZ -= 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ += 1.0f;
			}
			ptero2Direction = 180.0f;
			break;
		}
		break;
	case 90:	// Right
		switch (r) {
		case 1: // Back
			ptero2LocationZ += 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ -= 1.0f;
			}
			ptero2Direction = 0.0f;
			break;
		case 2: // Front
			ptero2LocationZ -= 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ += 1.0f;
			}
			ptero2Direction = 180.0f;
			break;
		case 3: // Left
			ptero2LocationX -= 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX += 1.0f;
			}
			ptero2Direction = 270.0f;
			break;
		default: // Right
			ptero2LocationX += 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX -= 1.0f;
			}
			ptero2Direction = 90.0f;
			break;
		}
		break;
	case 0:		// Back
		switch (r) {
		case 1: // Right
			ptero2LocationX += 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX -= 1.0f;
			}
			ptero2Direction = 90.0f;
			break;
		case 2: // front
			ptero2LocationZ -= 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ += 1.0f;
			}
			ptero2Direction = 180.0f;
			break;
		case 3: // Left
			ptero2LocationX -= 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX += 1.0f;
			}
			ptero2Direction = 270.0f;
			break;
		default: // Back
			ptero2LocationZ += 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ -= 1.0f;
			}
			ptero2Direction = 0.0f;
			break;
		}
		break;
	case 270:	// Left
		switch (r)
		{
		case 1: // Right
			ptero2LocationX += 1.0f;
			if (ptero2LocationX <= -200.0f || ptero2LocationX >= 200.0f)
			{
				ptero2LocationX -= 1.0f;
			}
			ptero2Direction = 90.0f;
			break;
		case 2: // Front
			ptero2LocationZ -= 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ += 1.0f;
			}
			ptero2Direction = 180.0f;
			break;
		case 3: // Back
			ptero2LocationZ += 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationZ -= 1.0f;
			}
			ptero2Direction = 0.0f;
			break;
		default: // Left
			ptero2LocationX -= 1.0f;
			if (ptero2LocationZ <= -200.0f || ptero2LocationZ >= 200.0f)
			{
				ptero2LocationX += 1.0f;
			}
			ptero2Direction = 270.0f;
			break;
		}
		break;
	default:
		ptero2Direction = 180;
		break;
	}
	r = rand() % 400 + 1;
	switch ((int)ptero3Direction)
	{
	case 180:	// Front
		switch (r) {
		case 1: // Back
			ptero3LocationZ += 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ -= 1.0f;
			}
			ptero3Direction = 0.0f;
			break;
		case 2: // Right
			ptero3LocationX += 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX -= 1.0f;
			}
			ptero3Direction = 90.0f;
			break;
		case 3: // Left
			ptero3LocationX -= 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX += 1.0f;
			}
			ptero3Direction = 270.0f;
			break;
		default: // Front
			ptero3LocationZ -= 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ += 1.0f;
			}
			ptero3Direction = 180.0f;
			break;
		}
		break;
	case 90:	// Right
		switch (r) {
		case 1: // Back
			ptero3LocationZ += 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ -= 1.0f;
			}
			ptero3Direction = 0.0f;
			break;
		case 2: // Front
			ptero3LocationZ -= 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ += 1.0f;
			}
			ptero3Direction = 180.0f;
			break;
		case 3: // Left
			ptero3LocationX -= 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX += 1.0f;
			}
			ptero3Direction = 270.0f;
			break;
		default: // Right
			ptero3LocationX += 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX -= 1.0f;
			}
			ptero3Direction = 90.0f;
			break;
		}
		break;
	case 0:		// Back
		switch (r)
		{
		case 1: // Right
			ptero3LocationX += 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX -= 1.0f;
			}
			ptero3Direction = 90.0f;
			break;
		case 2: // Front
			ptero3LocationZ -= 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ += 1.0f;
			}
			ptero3Direction = 180.0f;
			break;
		case 3: // Left
			ptero3LocationX -= 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX += 1.0f;
			}
			ptero3Direction = 270.0f;
			break;
		default: // Back
			ptero3LocationZ += 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ -= 1.0f;
			}
			ptero3Direction = 0.0f;
			break;
		}
		break;
	case 270:	// Left
		switch (r) {
		case 1: // Right
			ptero3LocationX += 1.0f;
			if (ptero3LocationX <= -200.0f || ptero3LocationX >= 200.0f)
			{
				ptero3LocationX -= 1.0f;
			}
			ptero3Direction = 90.0f;
			break;
		case 2: // Front
			ptero3LocationZ -= 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ += 1.0f;
			}
			ptero3Direction = 180.0f;
			break;
		case 3: // Back
			ptero3LocationZ += 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationZ -= 1.0f;
			}
			ptero3Direction = 0.0f;
			break;
		default: // Left
			ptero3LocationX -= 1.0f;
			if (ptero3LocationZ <= -200.0f || ptero3LocationZ >= 200.0f)
			{
				ptero3LocationX += 1.0f;
			}
			ptero3Direction = 270.0f;
			break;
		}
		break;
	default:
		ptero3Direction = 180;
		break;
	}
	r = rand() % 500 + 1;
	switch ((int)ptero4Direction)
	{
	case 180:	// Front
		switch (r) {
		case 1: // Back
			ptero4LocationZ += 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ -= 1.0f;
			}
			ptero4Direction = 0.0f;
			break;
		case 2: // Right
			ptero4LocationX += 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX -= 1.0f;
			}
			ptero4Direction = 90.0f;
			break;
		case 3: // Left
			ptero4LocationX -= 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX += 1.0f;
			}
			ptero4Direction = 270.0f;
			break;
		default: // Front
			ptero4LocationZ -= 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ += 1.0f;
			}
			ptero4Direction = 180.0f;
			break;
		}
		break;
	case 90:	// Right
		switch (r) {
		case 1: // Back
			ptero4LocationZ += 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ -= 1.0f;
			}
			ptero4Direction = 0.0f;
			break;
		case 2: // Front
			ptero4LocationZ -= 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ += 1.0f;
			}
			ptero4Direction = 180.0f;
			break;
		case 3: // Left
			ptero4LocationX -= 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX += 1.0f;
			}
			ptero4Direction = 270.0f;
			break;
		default: // Right
			ptero4LocationX += 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX -= 1.0f;
			}
			ptero4Direction = 90.0f;
			break;
		}
		break;
	case 0:		// Back
		switch (r) {
		case 1: // Right
			ptero4LocationX += 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX -= 1.0f;
			}
			ptero4Direction = 90.0f;
			break;
		case 2: // Front
			ptero4LocationZ -= 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ += 1.0f;
			}
			ptero4Direction = 180.0f;
			break;
		case 3: // Left
			ptero4LocationX -= 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX += 1.0f;
			}
			ptero4Direction = 270.0f;
			break;
		default: // Back
			ptero4LocationZ += 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ -= 1.0f;
			}
			ptero4Direction = 0.0f;
			break;
		}
		break;
	case 270:	// Left
		switch (r) {
		case 1: // Right
			ptero4LocationX += 1.0f;
			if (ptero4LocationX <= -200.0f || ptero4LocationX >= 200.0f)
			{
				ptero4LocationX -= 1.0f;
			}
			ptero4Direction = 90.0f;
			break;
		case 2: // Front
			ptero4LocationZ -= 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ += 1.0f;
			}
			ptero4Direction = 180.0f;
			break;
		case 3: // Back
			ptero4LocationZ += 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationZ -= 1.0f;
			}
			ptero4Direction = 0.0f;
			break;
		default: // Left
			ptero4LocationX -= 1.0f;
			if (ptero4LocationZ <= -200.0f || ptero4LocationZ >= 200.0f)
			{
				ptero4LocationX += 1.0f;
			}
			ptero4Direction = 270.0f;
			break;
		}
		break;
	default:
		ptero4Direction = 180;
		break;
	}
	rotateMain++;
}

void Scene4::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[1].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else {
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}

	viewStack.PushMatrix();
		viewStack.PushMatrix();
			viewStack.Translate(camera.position.x, camera.position.y - 30, camera.position.z - 20);
			RenderSkybox(500.0f, false);
		viewStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Rotate(-90, 0, 0, 1);
			modelStack.Translate(0, 0, 0);
			modelStack.Scale(800, 800, 800);
			RenderMesh(meshList[GEO_BOTTOM], light);
		modelStack.PopMatrix();
	viewStack.PopMatrix();

	viewStack.PushMatrix();
		for (int row = 0; row < 30; row++)
		{
			for (int col = 0; col < 30; col++)
			{
				int moveRow = (300 - (row * 20));
				int moveCol = (300 - (col * 20));

				if ((moveRow > 200) || (moveRow < -200) || (moveCol > 200) || (moveCol < -200))
				{
					if (((moveRow > 20) || (moveRow < -20)) || (moveCol > -180))
					{
						viewStack.PushMatrix();
							viewStack.Translate((moveRow), -20, (moveCol));
							viewStack.Scale(4, 4, 4);
							RenderMesh(meshList[GEO_TREE], godlights);
						viewStack.PopMatrix();
					}
				}
			}
		}

		// Fern //
		for (int i = 0; i < 6; i++)
		{
			for (int j = 1; j < 6; j++)
			{
				viewStack.PushMatrix();
					viewStack.Translate(-150 + (62 * i), 0, -180 + (62 * j));
					viewStack.Scale(8, 8, 8);
					viewStack.Rotate(12.5*i, 0, 1, 0);
					RenderMesh(meshList[GEO_FERN], godlights);
				viewStack.PopMatrix();
			}
		}
		// End of environment //

	//BORDER//
	viewStack.PushMatrix();
	viewStack.Translate(0, 0, -10);
	viewStack.Scale(35, 45, 35);
	viewStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_BORDER], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
	viewStack.Translate(0, 0, -10);
	viewStack.Scale(40, 60, 40);
	viewStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_BORDER], godlights);
	viewStack.PopMatrix();

	//End of environment//

	// portal
	viewStack.PushMatrix();
	viewStack.Translate(0, 20, -200);
	viewStack.PushMatrix();
	viewStack.Translate(-10, 30, 0);
	viewStack.Scale(3.75, 3.75, 3.75);
	RenderText(meshList[GEO_TEXT], "BACK TO", (1, 1, 1));
	viewStack.Translate(-0.5, -1.4, 0);
	viewStack.Scale(2, 2, 2);
	RenderText(meshList[GEO_TEXT], "START", (1, 1, 1));
	viewStack.PopMatrix();
	viewStack.Rotate(rotateMain, 0, 0, 1);
	viewStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_PORTAL], false);
	viewStack.PopMatrix();

	// pterodactyls
	viewStack.PushMatrix();
	viewStack.Translate(ptero1LocationX, 100, ptero1LocationZ);
	viewStack.Rotate(ptero1Direction, 0, 1, 0);
	viewStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_PTERO1], godlights);
	viewStack.PopMatrix();
	viewStack.PushMatrix();
	viewStack.Translate(ptero2LocationX, 75, ptero2LocationZ);
	viewStack.Rotate(ptero2Direction, 0, 1, 0);
	viewStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_PTERO2], godlights);
	viewStack.PopMatrix();
	viewStack.PushMatrix();
	viewStack.Translate(ptero3LocationX, 50, ptero3LocationZ);
	viewStack.Rotate(ptero3Direction, 0, 1, 0);
	viewStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_PTERO3], godlights);
	viewStack.PopMatrix();
	viewStack.PushMatrix();
	viewStack.Translate(ptero4LocationX, 50, ptero4LocationZ);
	viewStack.Rotate(ptero4Direction, 0, 1, 0);
	viewStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_PTERO4], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
		RenderNPC();
	viewStack.PopMatrix();

	std::ostringstream ah;
	ah << framerate;
	std::string str = ah.str(); 
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + str, Color(0, 1, 0), 2, 33, 29);

	std::ostringstream shopAMOUNT;
	shopAMOUNT << itemAmount;
	std::string amt = shopAMOUNT.str();

	int totalCostRedF = (shop.cost[SHOP_BUY_REDFRUIT] * itemAmount);
	int totalCostBluF = (shop.cost[SHOP_BUY_BLUFRUIT] * itemAmount);
	int totalCostMeat = (shop.cost[SHOP_BUY_MEAT] * itemAmount);
	int totalCostTrap = (shop.cost[SHOP_BUY_TRAP] * itemAmount);
	int totalCostIncu = (shop.cost[SHOP_BUY_INCUBATOR] * itemAmount);

	std::ostringstream costRed;
	costRed << totalCostRedF;
	std::string c_red = costRed.str();
	std::ostringstream costBlu;
	costBlu << totalCostBluF;
	std::string c_blu = costBlu.str();
	std::ostringstream costMeat;
	costMeat << totalCostMeat;
	std::string c_meat = costMeat.str();
	std::ostringstream costTrap;
	costTrap << totalCostTrap;
	std::string c_trap = costTrap.str();
	std::ostringstream costIncubator;
	costIncubator << totalCostIncu;
	std::string c_incubator = costIncubator.str();

	///////////////////////////////////////////////////////// START OF INVENTORY DISPLAY CODE /////////////////////////////////////////////////////////
	std::ostringstream inv1;
	inv1 << Inventory::instance()->items[ITEMS_REDFRUIT];
	std::ostringstream inv2;
	inv2 << Inventory::instance()->items[ITEMS_BLUFRUIT];
	std::ostringstream inv3;
	inv3 << Inventory::instance()->items[ITEMS_MEAT];
	std::ostringstream inv4;
	inv4 << Inventory::instance()->items[ITEMS_TRAP];
	std::ostringstream inv5;
	inv5 << Inventory::instance()->items[ITEMS_INCUBATOR];
	std::ostringstream inv6;
	inv6 << Inventory::instance()->items[ITEMS_CURRENCY];
	std::string red = inv1.str();
	std::string blu = inv2.str();
	std::string met = inv3.str();
	std::string trp = inv4.str();
	std::string inc = inv5.str();
	std::string cur = inv6.str();

	if (Inventory::instance()->showInventory && shopping != true)
	{
		RenderMeshOnScreen(meshList[GEO_INV_INTERFACE], 40, 30, 20, 20);
		RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], red, Color(1, 0, 0), 3, 10.9, 14.7);
		RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], blu, Color(0, 0, 1), 3, 10.9, 10);
		RenderTextOnScreen(meshList[GEO_INV_MEAT], met, Color(0.7, 0.31, 0), 3, 10.9, 5.9);
		RenderTextOnScreen(meshList[GEO_INV_TRAP], trp, Color(1, 1, 1), 3, 17.6, 14.7);
		RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], inc, Color(0.7, 0.7, 0), 3, 17.6, 10);
		RenderTextOnScreen(meshList[GEO_INV_CURRENCY], cur, Color(0, 0, 0), 3, 17.6, 5.9);
	}
	else if (shopping == true)
	{
		RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], red, Color(1, 0, 0), 3, 4.4, 15.1);
		RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], blu, Color(0, 0, 1), 3, 4.4, 13.3);
		RenderTextOnScreen(meshList[GEO_INV_MEAT], met, Color(0.7, 0.31, 0), 3, 10.2, 15.1);
		RenderTextOnScreen(meshList[GEO_INV_TRAP], trp, Color(1, 1, 1), 3, 10.2, 13.3);
		RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], inc, Color(0.7, 0.7, 0), 3, 15.4, 15.1);
		RenderTextOnScreen(meshList[GEO_INV_CURRENCY], cur, Color(0, 0, 0), 3, 15.4, 13.3);
		///////////////////////////////////////////////////////// END OF INVENTORY DISPLAY CODE /////////////////////////////////////////////////////////

		if (itemAmount <= 9)
		{
			RenderTextOnScreen(meshList[GEO_SHOP_AMOUNT], amt, Color(1, 0, 0), 3, 20.4, 9.5);
		}
		else if (itemAmount <= 99)
		{
			RenderTextOnScreen(meshList[GEO_SHOP_AMOUNT], amt, Color(1, 0, 0), 3, 19.85, 9.5);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_SHOP_AMOUNT], amt, Color(1, 0, 0), 3, 19.3, 9.5);
		}

		if (totalCostRedF <= 9)
		{
			RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], c_red, Color(1, 0, 0), 2, 5.3, 10);
		}
		else if (totalCostRedF <= 99)
		{
			RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], c_red, Color(1, 0, 0), 2, 4.8, 10);
		}
		else if (totalCostRedF <= 999)
		{
			RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], c_red, Color(1, 0, 0), 2, 4.3, 10);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], "SOLD OUT", Color(1, 0, 0), 1, 6.9, 20);
		}

		if (totalCostBluF <= 9)
		{
			RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], c_blu, Color(0, 0, 1), 2, 10.3, 10);
		}
		else if (totalCostBluF <= 99)
		{
			RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], c_blu, Color(0, 0, 1), 2, 9.8, 10);
		}
		else if (totalCostBluF <= 999)
		{
			RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], c_blu, Color(0, 0, 1), 2, 9.3, 10);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], "SOLD OUT", Color(0, 0, 1), 1, 16.9, 20);
		}

		if (totalCostMeat <= 9)
		{
			RenderTextOnScreen(meshList[GEO_INV_MEAT], c_meat, Color(0.7, 0.31, 0), 2, 15.3, 10);
		}
		else if (totalCostMeat <= 99)
		{
			RenderTextOnScreen(meshList[GEO_INV_MEAT], c_meat, Color(0.7, 0.31, 0), 2, 14.8, 10);
		}
		else if (totalCostMeat <= 999)
		{
			RenderTextOnScreen(meshList[GEO_INV_MEAT], c_meat, Color(0.7, 0.31, 0), 2, 14.3, 10);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_INV_MEAT], "SOLD OUT", Color(0.7, 0.31, 0), 1, 26.9, 20);
		}

		if (totalCostTrap <= 9)
		{
			RenderTextOnScreen(meshList[GEO_INV_TRAP], c_trap, Color(1, 1, 1), 2, 20.3, 10);
		}
		else if (totalCostTrap <= 99)
		{
			RenderTextOnScreen(meshList[GEO_INV_TRAP], c_trap, Color(1, 1, 1), 2, 19.8, 10);
		}
		else if (totalCostTrap <= 999)
		{
			RenderTextOnScreen(meshList[GEO_INV_TRAP], c_trap, Color(1, 1, 1), 2, 19.3, 10);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_INV_TRAP], "SOLD OUT", Color(1, 1, 1), 1, 36.9, 20);
		}

		if (totalCostIncu <= 9)
		{
			RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], c_incubator, Color(0.7, 0.7, 0), 2, 25.3, 10);
		}
		else if (totalCostIncu <= 99)
		{
			RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], c_incubator, Color(0.7, 0.7, 0), 2, 24.8, 10);
		}
		else if (totalCostIncu <= 999)
		{
			RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], c_incubator, Color(0.7, 0.7, 0), 2, 24.3, 10);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], "SOLD OUT", Color(0.7, 0.7, 0), 1, 46.9, 20);
		}
	}
}


void Scene4::Exit()
{
	glDeleteProgram(m_programID);
}

void Scene4::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Scene4::RenderSkybox(float d, bool light)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -d);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_FRONT], light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -d);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_BACK], light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0, -d);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_LEFT], light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 0, -d);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_RIGHT], light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Translate(0, 0, -d);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_TOP], light);
	modelStack.PopMatrix();
}

void Scene4::RenderNPC()
{
	textBoxRender = -1;

	for (int i = 0; i < npc.numberOfNPCs; i++)
	{
		viewStack.PushMatrix();
			viewStack.Translate(npc.GetCoord(i).x, npc.GetCoord(i).y, npc.GetCoord(i).z);
			viewStack.PushMatrix();
				if (i == NPC_SHOP)
				{
					viewStack.Scale(8, 8, 8);
					RenderMesh(meshList[GEO_NPC_SHOP], godlights);
				}
				else
				{
					viewStack.Rotate(npc.npcFacingRotaion[i], 0, 1, 0);

					if (i == NPC_FACTION_GIANT)
					{
						viewStack.Scale(14, 14, 14);
						RenderMesh(meshList[GEO_NPC_HUNTER], godlights);
					}
					else if (i == NPC_FACTION_SPEED)
					{
						viewStack.Scale(4, 4, 4);
						RenderMesh(meshList[GEO_NPC_HUNTER], godlights);
					}
					else if (i == NPC_LORE)
					{
						viewStack.Scale(8, 8, 8);
						RenderMesh(meshList[GEO_NPC_LORE], godlights);
					}
					else if (i == NPC_JOKER)
					{
						viewStack.Scale(8, 8, 8);
						RenderMesh(meshList[GEO_NPC_JOKER], godlights);
					}
					else
					{
						viewStack.Scale(8, 8, 8);
						RenderMesh(meshList[GEO_NPC_HUNTER], godlights);
					}
				}
			viewStack.PopMatrix();
		viewStack.PopMatrix();
	}
	textCollision();

	if (Application::IsKeyPressed('X') && textBoxRender == NPC_SHOP)
	{
		shopping = true;
	}

	std::string text[3];

	if (shopping == false && textBoxRender != -1)
	{

		if (continueDelay == 20)
		{
			if (Application::IsKeyPressed('X') && textBoxRender != NPC_SHOP)
			{
				continueDelay = 0;
				conversationStage++;
			}
		}
		else
		{
			continueDelay++;
		}

		viewStack.PushMatrix();
			RenderTextBox();

			loadText(textBoxRender, text);
			RenderTextOnScreen(meshList[GEO_TEXT], text[0], Color(1, 0, 0), 2, 1.8, 3.7);
			RenderTextOnScreen(meshList[GEO_TEXT], text[1], Color(1, 0, 0), 2, 1.8, 2.7);
			RenderTextOnScreen(meshList[GEO_TEXT], text[2], Color(1, 0, 0), 2, 1.8, 1.7);
		viewStack.PopMatrix();
	}
	else if (shopping == true && textBoxRender == NPC_SHOP)
	{
		viewStack.PushMatrix();
			RenderShopTextBox();
		viewStack.PopMatrix();
	}

	if (textBoxRender == -1)
	{
		conversationStage = 1;
		jokeNpcNum = 0;
		racingNpcNum = 0;
		
		if (speedChangedQuest == true)
		{
			speedFactionQuest++;
			speedChangedQuest = false;
		}
		if (giantChangedQuest == true)
		{
			giantFactionQuest++;
			giantChangedQuest = false;
		}
	}
}

void Scene4::loadText(int npc_type, std::string text[3])
{
	std::ifstream reading;
	std::string rawdata;
	switch (npc_type)
	{
	case NPC_RACING:
		switch (conversationStage)
		{
		case 1:
			reading.open("Text/npc_racing/1.txt");
			break;
		case 2:
			if (racingNpcNum == 0)
			{
				racingNpcNum = ((rand() % 2) + 1);
			}
			switch (racingNpcNum)
			{
			case 1:
				reading.open("Text/npc_racing/1.1.txt");
				break;
			case 2:
				reading.open("Text/npc_racing/2.1.txt");
				break;
			}
			break;
		case 3:
			switch (racingNpcNum)
			{
			case 1:
				reading.open("Text/npc_racing/1.2.txt");
				break;
			case 2:
				reading.open("Text/npc_racing/2.2.txt");
				break;
			}
			break;
		default:
			reading.open("Text/npc_racing/end.txt");
			break;
		}
		break;
	case NPC_LORE:
		switch (conversationStage)
		{
		case 1:
			if ((Inventory::instance()->items[ITEMS_TRAP] == 999) &&
				(Inventory::instance()->items[ITEMS_REDFRUIT] == 999) &&
				(Inventory::instance()->items[ITEMS_BLUFRUIT] == 999) &&
				(Inventory::instance()->items[ITEMS_MEAT] == 999) &&
				(Inventory::instance()->items[ITEMS_INCUBATOR] == 999) &&
				(Inventory::instance()->items[ITEMS_CURRENCY] == 999))
			{
				reading.open("Text/npc_lore/3.txt");
			}
			else if (MyPtero::instance()->pteroStage != MyPtero::P_EGG)
			{
				reading.open("Text/npc_lore/2.txt");
			}
			else
			{
				reading.open("Text/npc_lore/1.txt");
			}
			break;
		default:
			if ((Inventory::instance()->items[ITEMS_TRAP] == 999) &&
				(Inventory::instance()->items[ITEMS_REDFRUIT] == 999) &&
				(Inventory::instance()->items[ITEMS_BLUFRUIT] == 999) &&
				(Inventory::instance()->items[ITEMS_MEAT] == 999) &&
				(Inventory::instance()->items[ITEMS_INCUBATOR] == 999) &&
				(Inventory::instance()->items[ITEMS_CURRENCY] == 999))
			{
				reading.open("Text/npc_lore/3.txt");
			}
			else if (MyPtero::instance()->pteroStage != MyPtero::P_EGG)
			{
				reading.open("Text/npc_lore/2.txt");
			}
			else
			{
				reading.open("Text/npc_lore/1.txt");
			}
			break;
		}
		break;
	case NPC_JOKER:
		switch (conversationStage)
		{
		case 1:
			reading.open("Text/npc_joker/1.txt");
			break;
		case 2:
			if (jokeNpcNum == 0)
			{
				jokeNpcNum = ((rand() % 5) + 1);
			}
			switch(jokeNpcNum)
			{
			case 1:
				reading.open("Text/npc_joker/1.1.txt");
				break;
			case 2:
				reading.open("Text/npc_joker/2.1.txt");
				break;
			case 3:
				reading.open("Text/npc_joker/3.1.txt");
				break;
			case 4:
				reading.open("Text/npc_joker/4.1.txt");
				break;
			case 5:
				reading.open("Text/npc_joker/5.1.txt");
				break;
			}
			break;
		case 3:
			switch (jokeNpcNum)
			{
			case 1:
				reading.open("Text/npc_joker/1.2.txt");
				break;
			case 2:
				reading.open("Text/npc_joker/2.2.txt");
				break;
			case 3:
				reading.open("Text/npc_joker/3.2.txt");
				break;
			case 4:
				reading.open("Text/npc_joker/4.2.txt");
				break;
			case 5:
				reading.open("Text/npc_joker/5.2.txt");
				break;
			}
			break;
		default:
			switch (jokeNpcNum)
			{
			case 1:
				reading.open("Text/npc_joker/1.2.txt");
				break;
			case 2:
				reading.open("Text/npc_joker/2.2.txt");
				break;
			case 3:
				reading.open("Text/npc_joker/3.2.txt");
				break;
			case 4:
				reading.open("Text/npc_joker/4.2.txt");
				break;
			case 5:
				reading.open("Text/npc_joker/5.2.txt");
				break;
			}
			break;
		}
		break;
	case NPC_FACTION_SPEED:
		switch (conversationStage)
		{
		case 1:
			switch (speedFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_speed/1.1.txt");
				speedQuestDone = false;
				break;
			case 2:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/2.1.txt");
					speedQuestDone = false;
				}
				else
				{
					reading.open("Text/npc_faction_speed/2.0.txt");
				}
				break;
			case 3:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/3.1.txt");
					speedQuestDone = false;
				}
				else
				{
					reading.open("Text/npc_faction_speed/3.0.txt");
				}
				break;
			case 4:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/end.1.txt");
					speedQuestDone = false;
				}
				else
				{
					reading.open("Text/npc_faction_speed/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_speed/end.txt");
				break;
			}
			break;
		case 2:
			switch (speedFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_speed/1.2.txt");
				break;
			case 2:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/2.2.txt");
				}
				else
				{
					reading.open("Text/npc_faction_speed/2.0.txt");
				}
				break;
			case 3:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/3.2.txt");
				}
				else
				{
					reading.open("Text/npc_faction_speed/3.0.txt");
				}
				break;
			case 4:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/end.2.txt");
				}
				else
				{
					reading.open("Text/npc_faction_speed/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_speed/end.txt");
				break;
			}
			break;
		case 3:
			switch (speedFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_speed/1.3.txt");
				speedChangedQuest = true;
				break;
			case 2:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/2.3.txt");
					speedChangedQuest = true;
				}
				else
				{
					reading.open("Text/npc_faction_speed/2.0.txt");
					speedChangedQuest = true;
				}
				break;
			case 3:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/3.3.txt");
					speedChangedQuest = true;
				}
				else
				{
					reading.open("Text/npc_faction_speed/3.0.txt");
				}
				break;
			case 4:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/end.3.txt");
					speedChangedQuest = true;
				}
				else
				{
					reading.open("Text/npc_faction_speed/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_speed/end.txt");
				break;
			}
			break;
		default:
			switch (speedFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_speed/1.3.txt");
				break;
			case 2:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/2.3.txt");
				}
				else
				{
					reading.open("Text/npc_faction_speed/2.0.txt");
				}
				break;
			case 3:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/3.3.txt");
				}
				else
				{
					reading.open("Text/npc_faction_speed/3.0.txt");
				}
				break;
			case 4:
				if (speedQuestDone)
				{
					reading.open("Text/npc_faction_speed/end.3.txt");
				}
				else
				{
					reading.open("Text/npc_faction_speed/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_speed/end.txt");
				break;
			}
			break;
		}
		break;
	case NPC_FACTION_GIANT:
		switch (conversationStage)
		{
		case 1:
			switch (giantFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_giant/1.1.txt");
				giantQuestDone = false;
				break;
			case 2:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/2.1.txt");
					giantQuestDone = false;
				}
				else
				{
					reading.open("Text/npc_faction_giant/2.0.txt");
				}
				break;
			case 3:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/3.1.txt");
					giantQuestDone = false;
				}
				else
				{
					reading.open("Text/npc_faction_giant/3.0.txt");
				}
				break;
			case 4:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/end.1.txt");
					giantQuestDone = false;
				}
				else
				{
					reading.open("Text/npc_faction_giant/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_giant/end.txt");
				break;
			}
			break;
		case 2:
			switch (giantFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_giant/1.2.txt");
				break;
			case 2:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/2.2.txt");
				}
				else
				{
					reading.open("Text/npc_faction_giant/2.0.txt");
				}
				break;
			case 3:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/3.2.txt");
				}
				else
				{
					reading.open("Text/npc_faction_giant/3.0.txt");
				}
				break;
			case 4:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/end.2.txt");
				}
				else
				{
					reading.open("Text/npc_faction_giant/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_giant/end.txt");
				break;
			}
			break;
		case 3:
			switch (giantFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_giant/1.3.txt");
				giantChangedQuest = true;
				break;
			case 2:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/2.3.txt");
					giantChangedQuest = true;
				}
				else
				{
					reading.open("Text/npc_faction_giant/2.0.txt");
					giantChangedQuest = true;
				}
				break;
			case 3:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/3.3.txt");
					giantChangedQuest = true;
				}
				else
				{
					reading.open("Text/npc_faction_giant/3.0.txt");
				}
				break;
			case 4:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/end.3.txt");
					giantChangedQuest = true;
				}
				else
				{
					reading.open("Text/npc_faction_giant/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_giant/end.txt");
				break;
			}
			break;
		default:
			switch (giantFactionQuest)
			{
			case 1:
				reading.open("Text/npc_faction_giant/1.3.txt");
				break;
			case 2:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/2.3.txt");
				}
				else
				{
					reading.open("Text/npc_faction_giant/2.0.txt");
				}
				break;
			case 3:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/3.3.txt");
				}
				else
				{
					reading.open("Text/npc_faction_giant/3.0.txt");
				}
				break;
			case 4:
				if (giantQuestDone)
				{
					reading.open("Text/npc_faction_giant/end.3.txt");
				}
				else
				{
					reading.open("Text/npc_faction_giant/end.0.txt");
				}
				break;
			default:
				reading.open("Text/npc_faction_giant/end.txt");
				break;
			}
			break;
		}
		break;
	case NPC_SHOP:
		reading.open("Text/npc_shop.txt");
		break;
	default:
		break;
	}
	for (int i = 0; i < 3; i++)
	{
		getline(reading, rawdata);
		text[i] = rawdata;
	}
	reading.close();
}


void Scene4::RenderTextBox()
{
	viewStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX1], 1, 1, 80, 10);	// Middle white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 1, 80, 1);	// Bottom black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 10, 80, 1);	// Top black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 1, 1, 10);	// Left black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 79, 1, 1, 10);	// Right black area
	viewStack.PopMatrix();
}

void Scene4::RenderShopTextBox()
{
	viewStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_SHOP_INTERFACE], 40, 30, 40, 20);
	viewStack.PopMatrix();
}

void Scene4::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) // Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); // 1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Scene4::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) // Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	// Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); // Size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); // No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); // Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); // 1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	// Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Scene4::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); // Size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); // No need camera for ortho mode
	modelStack.PushMatrix();
		modelStack.LoadIdentity();
		modelStack.Translate(x, y, 0);
		modelStack.Scale(sizex, sizey, 1);
		RenderMesh(mesh, false); // UI should not have light
		RenderMesh(mesh, godlights); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

bool Scene4::collision(Vector3 c)
{
	float ActualYpos = c.y - 20;

	for (int i = 0; i < npc.numberOfNPCs; i++)
	{
		if (c.x >= npc.NPCS[i].minX && c.x <= npc.NPCS[i].maxX &&
			c.z >= npc.NPCS[i].minZ && c.z <= npc.NPCS[i].maxZ &&
			ActualYpos >= npc.NPCS[i].minY && ActualYpos <= npc.NPCS[i].maxY)
		{
			return true;
		}
	}

	if (c.x >= 200.0f || c.x <= -200.0f || c.z >= 200.0f || c.z <= -200.0f || c.y >= 200.0f || c.y <= -200.0f) {
		return true;
	}
	else 
	{
		return false;
	}
}

void Scene4::textCollision()
{
	float ActualYpos = camera.position.y - 20;

	for (int i = 0; i < npc.numberOfNPCs; i++)
	{
		if (camera.position.x >= (npc.NPCS[i].minX - npc.sizeOfTextMove) && camera.position.x <= (npc.NPCS[i].maxX + npc.sizeOfTextMove) &&
			camera.position.z >= (npc.NPCS[i].minZ - npc.sizeOfTextMove) && camera.position.z <= (npc.NPCS[i].maxZ + npc.sizeOfTextMove) &&
			ActualYpos >= (npc.NPCS[i].minY - npc.sizeOfTextMove) && ActualYpos <= (npc.NPCS[i].maxY + npc.sizeOfTextMove))
		{
			textBoxRender = i;
			npc.canMove[i] = false;
		}
		else
		{
			npc.canMove[i] = true;
		}
	}
}