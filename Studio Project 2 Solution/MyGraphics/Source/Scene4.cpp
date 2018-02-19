#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <sstream>

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

	// TODO remove the below testing code
	////////start of testing code////////
	std::cout << "Total : " << npc.numberOfNPCs << std::endl;
	std::cout << "Weather : " << npc.getCoord(NPC_WEATHER) << std::endl;
	std::cout << "Lore : " << npc.getCoord(NPC_LORE) << std::endl;
	std::cout << "Hunting : " << npc.getCoord(NPC_HUNTING) << std::endl;
	std::cout << "Raising : " << npc.getCoord(NPC_RAISING) << std::endl;
	std::cout << "Racing : " << npc.getCoord(NPC_RACING) << std::endl;
	////////end of testing code////////
	// TODO remove the above testing code


	camera.Init(Vector3(0, 20, 20), Vector3(0, 0, 1), Vector3(0, 1, 0)); //init camera

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
	light[0].position.Set(0, 10, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 10;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(0, 10, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 10;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

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

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_FRONT] = MeshBuilder::Generate2DQuad("front", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//4front.tga");
	meshList[GEO_BACK] = MeshBuilder::Generate2DQuad("back", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//4back.tga");
	meshList[GEO_LEFT] = MeshBuilder::Generate2DQuad("left", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//4left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::Generate2DQuad("right", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//4right.tga");
	meshList[GEO_TOP] = MeshBuilder::Generate2DQuad("top", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//4top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::Generate2DQuad("bottom", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//4bottom.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	///////////////////////////////////////////////////////// START OF INVENTORY MESH CODE /////////////////////////////////////////////////////////
	meshList[GEO_INV_REDFRUIT] = MeshBuilder::GenerateText("invRedFruit", 16, 16);
	meshList[GEO_INV_REDFRUIT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_BLUFRUIT] = MeshBuilder::GenerateText("invBluFruit", 16, 16);
	meshList[GEO_INV_BLUFRUIT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_MEAT] = MeshBuilder::GenerateText("invMeat", 16, 16);
	meshList[GEO_INV_MEAT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_TRAP] = MeshBuilder::GenerateText("invTrap", 16, 16);
	meshList[GEO_INV_TRAP]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INV_INTERFACE] = MeshBuilder::Generate2DQuad("InvInterface", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	meshList[GEO_INV_INTERFACE]->textureID = LoadTGA("Image//invInterface.tga");
	///////////////////////////////////////////////////////// END OF INVENTORY MESH CODE /////////////////////////////////////////////////////////

	meshList[GEO_PLACEHOLDER_NPC] = MeshBuilder::GenerateCube("placeholderNPC", Color(1, 1, 1), 1, 5, 1);
	meshList[GEO_PLACEHOLDER_TEXT_BOX1] = MeshBuilder::Generate2DQuad("placeholderTextBox", 1.0f, 1.0f, 0.f, 0.f, 0.f);
	meshList[GEO_PLACEHOLDER_TEXT_BOX2] = MeshBuilder::Generate2DQuad("placeholderTextBox", 1.0f, 1.0f, 1.f, 1.f, 1.f);
}

void Scene4::Update(double dt)
{	
	// TODO remove the below testing code
	////////start of testing code////////
	/*
	std::cout << "Position : " << camera.position << std::endl;
	std::cout << "Target : " << camera.target << std::endl;
	*/
	////////end of testing code////////
	// TODO remove the above testing code

	framerate = 1.0 / dt;
	Inventory::instance()->Update(dt);

	if (shopping == false)
	{
		camera.Update(dt);
	}

	if (camera.position.z <= -185.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_MAIN);
	}
	if (Application::IsKeyPressed('Q')) // turn on global light
	{
			godlights = false;
	}
	if (Application::IsKeyPressed('E')) // turn off global light
	{
			godlights = true;
	}

	////////////////////////////////////////////////////////////////// START OF SHOP CODE //////////////////////////////////////////////////////////////////
	if (shopping == true)
	{
		Application::SetCursorVisible(true);

		// TODO remove the below testing code
		////////start of testing code////////
		//std::cout << " x " << Application::GetCursorX() << std::endl;
		//std::cout << " y " << Application::GetCursorY() << std::endl;
		////////end of testing code////////
		// TODO remove the above testing code

		// Check what the player clicked on
		if (clickedDelay == 20)
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

				// Assign the shopAction
				if (Application::GetCursorX() >= shop.coord[SHOP_BUY_REDFRUIT].minX && Application::GetCursorX() <= shop.coord[SHOP_BUY_REDFRUIT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_BUY_REDFRUIT].minY && Application::GetCursorY() <= shop.coord[SHOP_BUY_REDFRUIT].maxY)
				{
					shopAction = SHOP_BUY_REDFRUIT;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_BUY_BLUFRUIT].minX && Application::GetCursorX() <= shop.coord[SHOP_BUY_BLUFRUIT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_BUY_BLUFRUIT].minY && Application::GetCursorY() <= shop.coord[SHOP_BUY_BLUFRUIT].maxY)
				{
					shopAction = SHOP_BUY_BLUFRUIT;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_BUY_MEAT].minX && Application::GetCursorX() <= shop.coord[SHOP_BUY_MEAT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_BUY_MEAT].minY && Application::GetCursorY() <= shop.coord[SHOP_BUY_MEAT].maxY)
				{
					shopAction = SHOP_BUY_MEAT;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_BUY_TRAP].minX && Application::GetCursorX() <= shop.coord[SHOP_BUY_TRAP].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_BUY_TRAP].minY && Application::GetCursorY() <= shop.coord[SHOP_BUY_TRAP].maxY)
				{
					shopAction = SHOP_BUY_TRAP;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_BUY_INCUBATOR].minX && Application::GetCursorX() <= shop.coord[SHOP_BUY_INCUBATOR].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_BUY_INCUBATOR].minY && Application::GetCursorY() <= shop.coord[SHOP_BUY_INCUBATOR].maxY)
				{
					shopAction = SHOP_BUY_INCUBATOR;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_SELL_REDFRUIT].minX && Application::GetCursorX() <= shop.coord[SHOP_SELL_REDFRUIT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_SELL_REDFRUIT].minY && Application::GetCursorY() <= shop.coord[SHOP_SELL_REDFRUIT].maxY)
				{
					shopAction = SHOP_SELL_REDFRUIT;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_SELL_BLUFRUIT].minX && Application::GetCursorX() <= shop.coord[SHOP_SELL_BLUFRUIT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_SELL_BLUFRUIT].minY && Application::GetCursorY() <= shop.coord[SHOP_SELL_BLUFRUIT].maxY)
				{
					shopAction = SHOP_SELL_BLUFRUIT;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_SELL_MEAT].minX && Application::GetCursorX() <= shop.coord[SHOP_SELL_MEAT].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_SELL_MEAT].minY && Application::GetCursorY() <= shop.coord[SHOP_SELL_MEAT].maxY)
				{
					shopAction = SHOP_SELL_MEAT;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_SELL_TRAP].minX && Application::GetCursorX() <= shop.coord[SHOP_SELL_TRAP].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_SELL_TRAP].minY && Application::GetCursorY() <= shop.coord[SHOP_SELL_TRAP].maxY)
				{
					shopAction = SHOP_SELL_TRAP;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_SELL_INCUBATOR].minX && Application::GetCursorX() <= shop.coord[SHOP_SELL_INCUBATOR].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_SELL_INCUBATOR].minY && Application::GetCursorY() <= shop.coord[SHOP_SELL_INCUBATOR].maxY)
				{
					shopAction = SHOP_SELL_INCUBATOR;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_RESET_QUANTITY].minX && Application::GetCursorX() <= shop.coord[SHOP_RESET_QUANTITY].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_RESET_QUANTITY].minY && Application::GetCursorY() <= shop.coord[SHOP_RESET_QUANTITY].maxY)
				{
					itemQuantity = 0;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_INCREASE_QUANTITY_1].minX && Application::GetCursorX() <= shop.coord[SHOP_INCREASE_QUANTITY_1].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_INCREASE_QUANTITY_1].minY && Application::GetCursorY() <= shop.coord[SHOP_INCREASE_QUANTITY_1].maxY)
				{
					itemQuantity += 1;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_DECREASE_QUANTITY_1].minX && Application::GetCursorX() <= shop.coord[SHOP_DECREASE_QUANTITY_1].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_DECREASE_QUANTITY_1].minY && Application::GetCursorY() <= shop.coord[SHOP_DECREASE_QUANTITY_1].maxY)
				{
					if (itemQuantity >= 1)
					{
						itemQuantity -= 1;
					}
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_INCREASE_QUANTITY_10].minX && Application::GetCursorX() <= shop.coord[SHOP_INCREASE_QUANTITY_10].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_INCREASE_QUANTITY_10].minY && Application::GetCursorY() <= shop.coord[SHOP_INCREASE_QUANTITY_10].maxY)
				{
					itemQuantity += 10;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_DECREASE_QUANTITY_10].minX && Application::GetCursorX() <= shop.coord[SHOP_DECREASE_QUANTITY_10].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_DECREASE_QUANTITY_10].minY && Application::GetCursorY() <= shop.coord[SHOP_DECREASE_QUANTITY_10].maxY)
				{
					if (itemQuantity >= 10)
					{
						itemQuantity -= 10;
					}
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_INCREASE_QUANTITY_100].minX && Application::GetCursorX() <= shop.coord[SHOP_INCREASE_QUANTITY_100].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_INCREASE_QUANTITY_100].minY && Application::GetCursorY() <= shop.coord[SHOP_INCREASE_QUANTITY_100].maxY)
				{
					itemQuantity += 100;
				}
				if (Application::GetCursorX() >= shop.coord[SHOP_DECREASE_QUANTITY_100].minX && Application::GetCursorX() <= shop.coord[SHOP_DECREASE_QUANTITY_100].maxX &&
					Application::GetCursorY() >= shop.coord[SHOP_DECREASE_QUANTITY_100].minY && Application::GetCursorY() <= shop.coord[SHOP_DECREASE_QUANTITY_100].maxY)
				{
					if (itemQuantity >= 100)
					{
						itemQuantity -= 100;
					}
				}
			}

			// Resolve the shopAction
			if (shopAction == SHOP_BUY_REDFRUIT)
			{
				if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[SHOP_BUY_REDFRUIT] * itemQuantity))
				{
					Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[SHOP_BUY_REDFRUIT] * itemQuantity);
					Inventory::instance()->items[ITEMS_REDFRUIT] += itemQuantity;
				}
			}
			if (shopAction == SHOP_BUY_BLUFRUIT)
			{
				if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[SHOP_BUY_BLUFRUIT] * itemQuantity))
				{
					Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[SHOP_BUY_BLUFRUIT] * itemQuantity);
					Inventory::instance()->items[ITEMS_BLUFRUIT] += itemQuantity;
				}
			}
			if (shopAction == SHOP_BUY_MEAT)
			{
				if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[SHOP_BUY_MEAT] * itemQuantity))
				{
					Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[SHOP_BUY_MEAT] * itemQuantity);
					Inventory::instance()->items[ITEMS_MEAT] += itemQuantity;
				}
			}
			if (shopAction == SHOP_BUY_TRAP)
			{
				if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[SHOP_BUY_TRAP] * itemQuantity))
				{
					Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[SHOP_BUY_TRAP] * itemQuantity);
					Inventory::instance()->items[ITEMS_TRAP] += itemQuantity;
				}
			}
			if (shopAction == SHOP_BUY_INCUBATOR)
			{
				if (Inventory::instance()->items[ITEMS_CURRENCY] >= (shop.cost[SHOP_BUY_INCUBATOR] * itemQuantity))
				{
					Inventory::instance()->items[ITEMS_CURRENCY] -= (shop.cost[SHOP_BUY_INCUBATOR] * itemQuantity);
					Inventory::instance()->items[ITEMS_INCUBATOR] += itemQuantity;
				}
			}
			if (shopAction == SHOP_SELL_REDFRUIT)
			{
				if (Inventory::instance()->items[ITEMS_REDFRUIT] >= itemQuantity)
					{
						Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[SHOP_SELL_REDFRUIT] * itemQuantity);
						Inventory::instance()->items[ITEMS_REDFRUIT] -= itemQuantity;
					}
				}
			if (shopAction == SHOP_SELL_BLUFRUIT)
			{
				if (Inventory::instance()->items[ITEMS_BLUFRUIT] >= itemQuantity)
				{
					Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[SHOP_SELL_BLUFRUIT] * itemQuantity);
					Inventory::instance()->items[ITEMS_BLUFRUIT] -= itemQuantity;
				}
			}
			if (shopAction == SHOP_SELL_MEAT)
			{
				if (Inventory::instance()->items[ITEMS_MEAT] >= itemQuantity)
				{
					Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[SHOP_SELL_MEAT] * itemQuantity);
					Inventory::instance()->items[ITEMS_MEAT] -= itemQuantity;
				}
			}
			if (shopAction == SHOP_SELL_TRAP)
			{
				if (Inventory::instance()->items[ITEMS_TRAP] >= itemQuantity)
				{
					Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[SHOP_SELL_TRAP] * itemQuantity);
					Inventory::instance()->items[ITEMS_TRAP] -= itemQuantity;
				}
			}
			if (shopAction == SHOP_SELL_INCUBATOR)
			{
				if (Inventory::instance()->items[SHOP_SELL_INCUBATOR] >= itemQuantity)
				{
					Inventory::instance()->items[ITEMS_CURRENCY] += (shop.cost[SHOP_SELL_INCUBATOR] * itemQuantity);
					Inventory::instance()->items[ITEMS_INCUBATOR] -= itemQuantity;
				}
			}
			shopAction = SHOP_EXIT;

			// TODO remove the below testing code
			////////start of testing code////////
			std::cout << "Money    : " << Inventory::instance()->items[ITEMS_CURRENCY] << std::endl;
			std::cout << "BluFruit : " << Inventory::instance()->items[ITEMS_BLUFRUIT] << std::endl;
			std::cout << "RedFruit : " << Inventory::instance()->items[ITEMS_REDFRUIT] << std::endl;
			std::cout << "Meat     : " << Inventory::instance()->items[ITEMS_MEAT] << std::endl;
			std::cout << "Trap	   : " << Inventory::instance()->items[ITEMS_TRAP] << std::endl;
			std::cout << "Incubator: " << Inventory::instance()->items[ITEMS_INCUBATOR] << std::endl;
			std::cout << "Quantity : " << itemQuantity << std::endl;
			////////end of testing code////////
			// TODO remove the above testing code

			clickedDelay = 0;
		}
		else
		{
			clickedDelay++;
		}
	}
	////////////////////////////////////////////////////////////////// END OF SHOP CODE ////////////////////////////////////////////////////////////////////
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

	RenderSkybox(200.0f, godlights);
	RenderMesh(meshList[GEO_AXES], false);

	/* sampel
	viewStack.PushMatrix();
		viewStack.Scale(1, 1, 1);
		viewStack.Translate(0, 0, 0);
		viewStack.Rotate(0, 0, 1, 0);
		RenderMesh(meshList[], godlights);
		RenderText(meshList[GEO_TEXT], "test", Color(1, 0, 0));
	viewStack.PopMatrix();
	*/

	viewStack.PushMatrix();
		RenderNPC();
	viewStack.PopMatrix();

	std::ostringstream ah;
	ah << framerate;
	std::string str = ah.str(); 
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + str, Color(0, 1, 0), 2, 33, 29);

	///////////////////////////////////////////////////////// START OF INVENTORY DISPLAY CODE /////////////////////////////////////////////////////////
	std::ostringstream inv1;
	inv1 << Inventory::instance()->items[ITEMS_REDFRUIT];
	std::ostringstream inv2;
	inv2 << Inventory::instance()->items[ITEMS_BLUFRUIT];
	std::ostringstream inv3;
	inv3 << Inventory::instance()->items[ITEMS_MEAT];
	std::ostringstream inv4;
	inv4 << Inventory::instance()->items[ITEMS_TRAP];
	std::string red = inv1.str();
	std::string blu = inv2.str();
	std::string met = inv3.str();
	std::string trp = inv4.str();

	if (Inventory::instance()->showInventory)
	{
		RenderMeshOnScreen(meshList[GEO_INV_INTERFACE], 10, 50, 10, 10);
		RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], ":" + red, Color(1, 0, 0), 4, 2.7, 14.3);
		RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], ":" + blu, Color(0, 0, 1), 4, 2.7, 13);
		RenderTextOnScreen(meshList[GEO_INV_MEAT], ":" + met, Color(0.7, 0.31, 0), 4, 2.7, 11.9);
		RenderTextOnScreen(meshList[GEO_INV_TRAP], ":" + trp, Color(1, 1, 1), 4, 2.7, 10.7);
		RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], ":" + trp, Color(1, 1, 1), 4, 2.7, 10.7);
	}
	///////////////////////////////////////////////////////// END OF INVENTORY DISPLAY CODE /////////////////////////////////////////////////////////
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
	//modelStack.Rotate(0, 0, 0, 0);
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

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Translate(0, 0, -d); // change -d to 0 to bring floor up to foot level
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_BOTTOM], light);
	modelStack.PopMatrix();
}

void Scene4::RenderNPC()
{
	textBoxRender = -1;

	for (int i = 0; i < npc.numberOfNPCs; i++)
	{
		viewStack.PushMatrix();
			viewStack.Translate(npc.getCoord(i).x, npc.getCoord(i).y, npc.getCoord(i).z);
			viewStack.PushMatrix();
				viewStack.Scale(10, 40, 10);
				RenderMesh(meshList[GEO_PLACEHOLDER_NPC], godlights);
			viewStack.PopMatrix();
		viewStack.PopMatrix();
	}
	textCollision();


	if (Application::IsKeyPressed('X') && textBoxRender == NPC_SHOP)
	{
		shopping = true;
	}
	if (textBoxRender == NPC_WEATHER)
	{
		viewStack.PushMatrix();
		RenderTextBox();
		viewStack.PopMatrix();
	}
	if (textBoxRender == NPC_LORE)
	{
		viewStack.PushMatrix();
		RenderTextBox();
		viewStack.PopMatrix();
	}
	if (textBoxRender == NPC_HUNTING)
	{
		viewStack.PushMatrix();
		RenderTextBox();
		viewStack.PopMatrix();
	}
	if (textBoxRender == NPC_RAISING)
	{
		viewStack.PushMatrix();
		RenderTextBox();
		viewStack.PopMatrix();
	}
	if (textBoxRender == NPC_RACING)
	{
		viewStack.PushMatrix();
		RenderTextBox();
		viewStack.PopMatrix();
	}
	if (shopping == false && textBoxRender == NPC_SHOP)
	{
		viewStack.PushMatrix();
		RenderTextBox();
		viewStack.PopMatrix();
	}
	else if (shopping == true && textBoxRender == NPC_SHOP)
	{
		viewStack.PushMatrix();
		RenderShopTextBox();
		viewStack.PopMatrix();
	}
}

void Scene4::RenderTextBox()
{
	viewStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX1], 1, 1, 80, 10); // Middle black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 1, 80, 1);	// Bottom white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 10, 80, 1);	// Top white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 1, 1, 10);	// Left white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 79, 1, 1, 10);	// Right white area
	viewStack.PopMatrix();
}

void Scene4::RenderShopTextBox()
{
	viewStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX1], 1, 30, 80, 20); // Middle black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 11, 80, 1);	// Bottom white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 50, 80, 1);	// Top white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 1, 30, 1, 20);	// Left white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 79, 30, 1, 20);	// Right white area

		viewStack.PushMatrix();

		// The design of the boxes
		int shopUI[7][7] =
		{
			0,0,0,0,0,1,0,
			0,0,0,0,0,1,0,
			1,1,1,1,1,1,0,
			1,1,1,1,1,1,1,
			1,1,1,1,1,1,0,
			0,0,0,0,0,1,0,
			1,0,0,0,0,1,0,
		};

		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 7; col++)
			{
				if (shopUI[row][col] == 1)
				{
					RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_TEXT_BOX2], 10 + (col * 10), 45 - (row * 5), 4, 2);
				}
			}
		}
		viewStack.PopMatrix();
	viewStack.PopMatrix();
}

void Scene4::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
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
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
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
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
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
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void Scene4::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
		modelStack.LoadIdentity();
		modelStack.Translate(x, y, 0);
		modelStack.Scale(sizex, sizey, 1);
		RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

bool Scene4::collision(Vector3 c)
{
	float ActualYpos = c.y - 20;

	for (int i = 0; i < NPC_TOTAL; i++)
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
	else {
		return false;
	}
}

void Scene4::textCollision()
{
	float ActualYpos = camera.position.y - 20;

	for (int i = 0; i < NPC_TOTAL; i++)
	{
		if (camera.position.x >= (npc.NPCS[i].minX - npc.sizeOfTextMove) && camera.position.x <= (npc.NPCS[i].maxX + npc.sizeOfTextMove) &&
			camera.position.z >= (npc.NPCS[i].minZ - npc.sizeOfTextMove) && camera.position.z <= (npc.NPCS[i].maxZ + npc.sizeOfTextMove) &&
			ActualYpos >= (npc.NPCS[i].minY - npc.sizeOfTextMove) && ActualYpos <= (npc.NPCS[i].maxY + npc.sizeOfTextMove))
		{
		textBoxRender = i;
		}
	}
}