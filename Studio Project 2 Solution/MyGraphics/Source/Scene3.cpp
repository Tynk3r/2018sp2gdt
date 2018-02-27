#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <sstream>

// THIS IS THE SP FOLDER VERSION // 
// THIS ONE IS TO BE MODIFIED FOR RELEASE // 

Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{	
	framerate = 0.0f;
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
	godlights = true;

	camera.Init(Vector3(0, 20, 20), Vector3(0, 0, 1), Vector3(0, 1, 0)); // init camera

	for (int i = 0; i < 5; i++)
	{
		bushesHarvested[i] = false;
	}

	// Trap State Chart // 
	// 0 = no trap
	// 1 = empty trap
	// 2 = trapped animal

	// Checking Trap1 State // 
	if (trap1State == TRAP_PLACED)
	{
		int TRAPCARD;
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap1State = TRAP_TRAPPED;
			trappedBush1 = true;
		}
	}

	// Checking Trap2 State // 
	if (trap2State == TRAP_PLACED)
	{
		int TRAPCARD;
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap2State = TRAP_TRAPPED;
			trappedBush2 = true;
		}
	}

	// Checking Trap3 State // 
	if (trap3State == TRAP_PLACED)
	{
		int TRAPCARD;
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap3State = TRAP_TRAPPED;
			trappedBush3 = true;
		}
	}

	// Checking Trap4 State // 
	if (trap4State == TRAP_PLACED)
	{
		int TRAPCARD;
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap4State = TRAP_TRAPPED;
			trappedBush4 = true;
		}
	}

	// Checking Trap5 State // 
	if (trap5State == TRAP_PLACED)
	{
		int TRAPCARD;
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap5State = TRAP_TRAPPED;
			trappedBush5 = true;
		}
	}

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

	glUniform1i(m_parameters[U_NUMLIGHTS], 3);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init VBO here
	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//remove all glGenBuffers, glBindBuffer, glBufferData code
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
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_EXPLAINTEXT] = MeshBuilder::GenerateText("foragingInstruction", 16, 16);
	meshList[GEO_EXPLAINTEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_INSTRUCTIONS] = MeshBuilder::Generate2DQuad("InstructionInterface", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	meshList[GEO_INSTRUCTIONS]->textureID = LoadTGA("Image//instructionInterface.tga");

	//Environment Mesh Codes
	meshList[GEO_TRAPDEFAULT] = MeshBuilder::GenerateOBJ("defaultTrap", "OBJ//scene3Trap.obj");
	meshList[GEO_TRAPDEFAULT]->textureID = LoadTGA("Image//scene3Trap.tga");
	meshList[GEO_TRAPCAUGHT] = MeshBuilder::GenerateOBJ("caughtTrap", "OBJ//scene3Trapped.obj");
	meshList[GEO_TRAPCAUGHT]->textureID = LoadTGA("Image//scene3Trapped.tga");

	meshList[GEO_BUSH] = MeshBuilder::GenerateOBJ("Bush", "OBJ//tempBush.obj");
	meshList[GEO_BUSH]->textureID = LoadTGA("Image//bush.tga");

	meshList[GEO_REDFRUIT] = MeshBuilder::GenerateOBJ("Bush", "OBJ//tempFruit.obj");
	meshList[GEO_REDFRUIT]->textureID = LoadTGA("Image//fruitRed.tga");

	meshList[GEO_WHEELBARROW] = MeshBuilder::GenerateOBJ("wheelbarrow", "OBJ//wheelBarrow.obj");
	meshList[GEO_WHEELBARROW]->textureID = LoadTGA("Image//wheelBarrow.tga");

	meshList[GEO_FERN] = MeshBuilder::GenerateOBJ("fern", "OBJ//fern.obj");
	meshList[GEO_FERN]->textureID = LoadTGA("Image//fern.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("tree", "OBJ//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//tree.tga");

	meshList[GEO_BORDER] = MeshBuilder::GenerateOBJ("border", "OBJ//border.obj");
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//rock1.tga");

	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJ("rock", "OBJ//rock.obj");
	meshList[GEO_ROCK]->textureID = LoadTGA("Image//rock1.tga");


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

	meshList[GEO_PLACEHOLDER_UI_WHITE] = MeshBuilder::Generate2DQuad("placeholderTextBoxWhite", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_PLACEHOLDER_UI_BLACK] = MeshBuilder::Generate2DQuad("placeholderTextBoxBlack", 1.0f, 1.0f, 0.f, 0.f, 0.f);
	meshList[GEO_PLACEHOLDER_GETTING_FRUITS_GAME_OBJECT] = MeshBuilder::Generate2DQuad("placeholderGameObject", 1.0f, 1.0f, 1.f, 0.f, 0.f);

	//Set Object Positions//
	objs[OBJ_TREE1].setBox(Vector3(-50, -16, -30), 8, 40, 8);
	objs[OBJ_TREE2].setBox(Vector3(-80, -16, -100), 8, 40, 8);
	objs[OBJ_TREE3].setBox(Vector3(50, -16, -10), 8, 40, 8);
	objs[OBJ_ROCK1].setBox(Vector3(100, 0, -80), 50);
	objs[OBJ_ROCK2].setBox(Vector3(-140, 0, 80), 50);
	objs[OBJ_ROCK3].setBox(Vector3(-80, 0, -30), 50);
	objs[OBJ_WHEELBARROW].setBox(Vector3(95, 0, 0), 40, 10, 20);
}

void Scene3::Update(double dt)
{
	framerate = 1.0 / dt;
	Inventory::instance()->Update();

	if (Application::IsKeyPressed('P'))
	{
		Inventory::instance()->items[ITEMS_TRAP] += 1;
	}

	if (camera.position.z <= -185.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_MAIN);
	}

	if ((Application::IsKeyPressed('E')) && (camera.position.x <= 125.0f && camera.position.x >= 95.0f && camera.position.z <= 85.0f && camera.position.z >= 55.0f))
	{
		if (bushesHarvested[0] == false)
		{
			bushesHarvested[0] = true;
			inGettingFruitsGame = true;
		}
	}
	else if ((Application::IsKeyPressed('E')) && (camera.position.x <= -15.0f && camera.position.x >= -45.0f && camera.position.z <= 65.0f && camera.position.z >= 35.0f))
	{
		if (bushesHarvested[1] == false)
		{
			bushesHarvested[1] = true;
			inGettingFruitsGame = true;
		}
	}
	else if ((Application::IsKeyPressed('E')) && (camera.position.x <= 165.0f && camera.position.x >= 135.0f && camera.position.z <= -75.0f && camera.position.z >= -105.0f))
	{
		if (bushesHarvested[2] == false)
		{
			bushesHarvested[2] = true;
			inGettingFruitsGame = true;
		}
	}
	else if ((Application::IsKeyPressed('E')) && (camera.position.x <= 95.0f && camera.position.x >= 65.0f && camera.position.z <= -135.0f && camera.position.z >= -165.0f))
	{
		if (bushesHarvested[3] == false)
		{
			bushesHarvested[3] = true;
			inGettingFruitsGame = true;
		}
	}
	else if ((Application::IsKeyPressed('E')) && (camera.position.x <= -55.0f && camera.position.x >= -85.0f && camera.position.z <= -85.0f && camera.position.z >= -115.0f))
	{
		if (bushesHarvested[4] == false)
		{
			bushesHarvested[4] = true;
			inGettingFruitsGame = true;
		}
	}

	if (Application::IsKeyPressed('V') && (camera.position.x <= 125.0f && camera.position.x >= 95.0f && camera.position.z <= 85.0f && camera.position.z >= 55.0f)) // Trap Interactions
	{
		if ((trappedBush1 == false) && (Inventory::instance()->items[ITEMS_TRAP] > 0)) // Setting a trap
		{
			trap1State = TRAP_PLACED;
			Inventory::instance()->items[ITEMS_TRAP] -= 1;
			trappedBush1 = true;
		}
		else if (trap1State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) < 998)) // Collecting trapped animal
		{
			trappedBush1 = false;
			trap1State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 2;
		}
		else if (trap1State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) == 998)) // Collecting trapped animal but capped at 999
		{
			trappedBush1 = false;
			trap1State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 1;
		}
	}

	if (Application::IsKeyPressed('X') && (camera.position.x <= -15.0f && camera.position.x >= -45.0f && camera.position.z <= 65.0f && camera.position.z >= 35.0f)) // Trap Interactions
	{
		if ((trappedBush2 == false) && (Inventory::instance()->items[ITEMS_TRAP] > 0)) // Setting a trap
		{
			trappedBush2 = true;
			trap2State = TRAP_PLACED;
			Inventory::instance()->items[ITEMS_TRAP] -= 1;
		}
		else if (trap2State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) < 998)) // Collecting trapped animal
		{
			trappedBush2 = false;
			trap2State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 2;
		}
		else if (trap2State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) == 998)) // Collecting trapped animal but capped at 999
		{
			trappedBush2 = false;
			trap2State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 1;
		}
	}

	if (Application::IsKeyPressed('X') && (camera.position.x <= 165.0f && camera.position.x >= 135.0f && camera.position.z <= -75.0f && camera.position.z >= -105.0f)) // Trap Interactions
	{
		if ((trappedBush3 == false) && (Inventory::instance()->items[ITEMS_TRAP] > 0)) // Setting a trap
		{
			trappedBush3 = true;
			trap3State = TRAP_PLACED;
			Inventory::instance()->items[ITEMS_TRAP] -= 1;
		}
		else if (trap3State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) < 998)) // Collecting trapped animal
		{
			trappedBush3 = false;
			trap3State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 2;
		}
		else if (trap3State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) == 998)) // Collecting trapped animal but capped at 999
		{
			trappedBush3 = false;
			trap3State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 1;
		}
	}

	if (Application::IsKeyPressed('X') && (camera.position.x <= 95.0f && camera.position.x >= 65.0f && camera.position.z <= -135.0f && camera.position.z >= -165.0f)) // Trap Interactions
	{
		if ((trappedBush4 == false) && (Inventory::instance()->items[ITEMS_TRAP] > 0)) // Setting a trap
		{
			trappedBush4 = true;
			trap4State = TRAP_PLACED;
			Inventory::instance()->items[ITEMS_TRAP] -= 1;
		}
		else if (trap4State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) < 998)) // Collecting trapped animal
		{
			trappedBush4 = false;
			trap4State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 2;
		}
		else if (trap4State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) == 998)) // Collecting trapped animal but capped at 999
		{
			trappedBush4 = false;
			trap4State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 1;
		}
	}

	if (Application::IsKeyPressed('X') && (camera.position.x <= -55.0f && camera.position.x >= -85.0f && camera.position.z <= -85.0f && camera.position.z >= -115.0f)) // Trap Interactions
	{
		if ((trappedBush5 == false) && (Inventory::instance()->items[ITEMS_TRAP] > 0)) // Setting a trap
		{
			trappedBush5 = true;
			trap5State = TRAP_PLACED;
			Inventory::instance()->items[ITEMS_TRAP] -= 1;
		}
		else if (trap5State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) < 998)) // Collecting trapped animal
		{
			trappedBush5 = false;
			trap5State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 2;
		}
		else if (trap5State == TRAP_TRAPPED && ((Inventory::instance()->items[ITEMS_MEAT] + 2) == 998)) // Collecting trapped animal but capped at 999
		{
			trappedBush5 = false;
			trap5State = TRAP_NONE;
			Inventory::instance()->items[ITEMS_MEAT] += 1;
		}
	}

	////////////////////////////////////////////////////////////////// START OF GETTING FRUITS GAME CODE //////////////////////////////////////////////////////////////////
	if (inGettingFruitsGame == true)
	{
		if (gameStartDelay == 20)
		{
			if (Application::IsKeyPressed('E'))
			{
				if ((fruitMovingPosition >= 30) && (fruitMovingPosition <= 50))
				{
					fruitsWon++;
					fruitsGameDifficulty++;
					gameStartDelay = 0;
				}
				else
				{
					getFruuts(fruitsWon);
					inGettingFruitsGame = false;
					fruitsGameDifficulty = 1;
					gameStartDelay = 0;
					fruitsWon = 0;
				}
			}
		}
		else
		{
			gameStartDelay++;
		}

		if (fruitMovingPosition <= 3)
		{
			fruitMoveTowardsLeft = false;
		}
		if (fruitMovingPosition >= 78)
		{
			fruitMoveTowardsLeft = true;
		}

		if (fruitMoveTowardsLeft)
		{
			fruitMovingPosition -= fruitsGameDifficulty;
		}
		else
		{
			fruitMovingPosition += fruitsGameDifficulty;
		}

		// Max difficulty
		if (fruitsGameDifficulty == 10)
		{
			getFruuts(fruitsWon * 2);
			inGettingFruitsGame = false;
			fruitsGameDifficulty = 1;
			gameStartDelay = 0;
			fruitsWon = 0;
		}
	}
	////////////////////////////////////////////////////////////////// END OF GETTING FRUITS GAME CODE ////////////////////////////////////////////////////////////////////
	else
	{
		camera.Update(dt);
	}
}

bool Scene3::getFruuts(int fruitsWon)
{
	bool gotFruits = false;
	int gain = rand() % 3 + 1;
	gain += fruitsWon;

	if ((Inventory::instance()->items[ITEMS_REDFRUIT] + gain) >= 999 && (Inventory::instance()->items[ITEMS_REDFRUIT] != 999)) // Capped at 999
	{
		Inventory::instance()->items[ITEMS_REDFRUIT] = 999;
		gotFruits = true;
	}
	else if ((Inventory::instance()->items[ITEMS_REDFRUIT] + gain) < 999)
	{
		Inventory::instance()->items[ITEMS_REDFRUIT] += gain;
		gotFruits = true;
	}

	gain -= 5;

	if (gain < 0)
	{
		gain = 0;
	}

	if ((Inventory::instance()->items[ITEMS_BLUFRUIT] + gain) >= 999 && (Inventory::instance()->items[ITEMS_BLUFRUIT] != 999)) // Capped at 999
	{
		Inventory::instance()->items[ITEMS_BLUFRUIT] = 999;
		gotFruits = true;
	}
	else if ((Inventory::instance()->items[ITEMS_BLUFRUIT] + gain) < 999)
	{
		Inventory::instance()->items[ITEMS_BLUFRUIT] += gain;
		gotFruits = true;
	}

	if (gotFruits)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Scene3::Render()
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

	viewStack.PushMatrix();
	viewStack.PushMatrix();
	viewStack.Translate(camera.position.x, camera.position.y - 20, camera.position.z - 20);
	RenderSkybox(700.0f, false);
	viewStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(400, 400, 400);
	RenderMesh(meshList[GEO_BOTTOM], godlights);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	
	//Environment//
	//Trees//
	viewStack.PushMatrix();
	viewStack.Translate(objs[1].getPos().x, objs[1].getPos().y, objs[1].getPos().z);
	viewStack.Scale(4, 4, 4);
	viewStack.Rotate(270, 0, 1, 0);
	RenderMesh(meshList[GEO_TREE], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
	viewStack.Translate(objs[2].getPos().x, objs[2].getPos().y, objs[2].getPos().z);
	viewStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_TREE], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
	viewStack.Translate(objs[3].getPos().x, objs[3].getPos().y, objs[3].getPos().z);
	viewStack.Scale(4, 4, 4);
	viewStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_TREE], godlights);
	viewStack.PopMatrix();

	//Rocks//
	viewStack.PushMatrix();
	viewStack.Translate(objs[4].getPos().x, objs[4].getPos().y, objs[4].getPos().z);
	viewStack.Scale(4, 4, 4);
	viewStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_ROCK], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
	viewStack.Translate(objs[5].getPos().x, objs[5].getPos().y, objs[5].getPos().z);
	viewStack.Scale(4, 4, 4);
	viewStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_ROCK], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
	viewStack.Translate(objs[6].getPos().x, objs[6].getPos().y, objs[6].getPos().z);
	viewStack.Scale(4, 4, 4);
	viewStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_ROCK], godlights);
	viewStack.PopMatrix();

	//BORDER//
	viewStack.PushMatrix();
	viewStack.Translate(0, 0, -10);
	viewStack.Scale(30, 40, 30);
	viewStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_BORDER], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
	viewStack.Translate(0, 0, -10);
	viewStack.Scale(35, 50, 35);
	viewStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_BORDER], godlights);
	viewStack.PopMatrix();

	//Fern//
	for (int i = 0; i < 6; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			viewStack.PushMatrix();
			//viewStack.Rotate(12.5*i, 0, 1, 0);
			viewStack.Translate(-150 + (62 * i), 0, -180 + (62 * j));
			viewStack.Scale(8, 8, 8);
			viewStack.Rotate(12.5*i, 0, 1, 0);
			RenderMesh(meshList[GEO_FERN], godlights);
			viewStack.PopMatrix();
		}
	}
	//End of environment//
	
	// BUSH 1 // 
	viewStack.PushMatrix();
	viewStack.Translate(110, 0, 70);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(70, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], godlights);
	viewStack.PopMatrix();

	if (bushesHarvested[0] == false) // Bush 1 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(110, 30, 70);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_REDFRUIT], godlights);
		viewStack.PopMatrix();
	}

	if (trap1State == TRAP_PLACED) // Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(90, 0, 70);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(70, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], godlights);
		viewStack.PopMatrix();
	}

	else if (trap1State == TRAP_TRAPPED) // Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(90, 0, 70);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(70, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], godlights);
		viewStack.PopMatrix();
	}

	// BUSH 2 // 
	viewStack.PushMatrix();
	viewStack.Translate(-30, 0, 50);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(120, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], godlights);
	viewStack.PopMatrix();

	if (bushesHarvested[1] == false) // Bush 2 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(-30, 30, 50);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_REDFRUIT], godlights);
		viewStack.PopMatrix();
	}

	if (trap2State == TRAP_PLACED) // Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-18, 0, 36);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-50, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], godlights);
		viewStack.PopMatrix();
	}

	else if (trap2State == TRAP_TRAPPED) // Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-18, 0, 36);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-50, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], godlights);
		viewStack.PopMatrix();
	}

	// BUSH 3 // 
	viewStack.PushMatrix();
	viewStack.Translate(150, 0, -90);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(10, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], godlights);
	viewStack.PopMatrix();

	if (bushesHarvested[2] == false) // Bush 3 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(150, 30, -90);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_REDFRUIT], godlights);
		viewStack.PopMatrix();
	}

	if (trap3State == TRAP_PLACED) // Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(130, 0, -77);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], godlights);
		viewStack.PopMatrix();
	}

	else if (trap3State == TRAP_TRAPPED) // Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(130, 0, -77);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], godlights);
		viewStack.PopMatrix();
	}

	// BUSH 4 // 

	viewStack.PushMatrix();
	viewStack.Translate(80, 0, -150);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], godlights);
	viewStack.PopMatrix();
	if (bushesHarvested[3] == false) // Bush 4 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(80, 30, -150);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_REDFRUIT], godlights);
		viewStack.PopMatrix();
	}

	if (trap4State == TRAP_PLACED) // Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(66, 0, -137);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], godlights);
		viewStack.PopMatrix();
	}

	else if (trap4State == TRAP_TRAPPED) // Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(66, 0, -137);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], godlights);
		viewStack.PopMatrix();
	}

	// BUSH 5 // 
	viewStack.PushMatrix();
	viewStack.Translate(-70, 0, -100);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(50, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], godlights);
	viewStack.PopMatrix();

	if (bushesHarvested[4] == false) // Bush 5 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(-70, 30, -100);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_REDFRUIT], godlights);
		viewStack.PopMatrix();
	}

	if (trap5State == TRAP_PLACED) // Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-91, 0, -95);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-100, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], godlights);
		viewStack.PopMatrix();
	}

	else if (trap5State == TRAP_TRAPPED) // Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-91, 0, -95);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-100, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], godlights);
		viewStack.PopMatrix();
	}

	viewStack.PushMatrix();
	viewStack.Translate(100, 8, 0);
	viewStack.Scale(15, 15, 15);
	//viewStack.Rotate(72, 0, 1, 0);
	RenderMesh(meshList[GEO_WHEELBARROW], godlights);
	viewStack.PopMatrix();

	RenderMeshOnScreen(meshList[GEO_INSTRUCTIONS], 64, 57, 16, 3);
	RenderTextOnScreen(meshList[GEO_EXPLAINTEXT], "<E> to pick fruits", Color(1, 1, 1), 1.5, 33, 38);
	RenderTextOnScreen(meshList[GEO_EXPLAINTEXT], "<X> to set/pick trap", Color(1, 1, 1), 1.5, 33, 37);
	RenderTextOnScreen(meshList[GEO_EXPLAINTEXT], "<I> to show inventory", Color(1, 1, 1), 1.5, 33, 39);

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

	if ((Inventory::instance()->showInventory) && (!inGettingFruitsGame))
	{
		RenderMeshOnScreen(meshList[GEO_INV_INTERFACE], 40, 30, 20, 20);
		RenderTextOnScreen(meshList[GEO_INV_REDFRUIT], red, Color(1, 0, 0), 3, 10.9, 14.7);
		RenderTextOnScreen(meshList[GEO_INV_BLUFRUIT], blu, Color(0, 0, 1), 3, 10.9, 10);
		RenderTextOnScreen(meshList[GEO_INV_MEAT], met, Color(0.7, 0.31, 0), 3, 10.9, 5.9);
		RenderTextOnScreen(meshList[GEO_INV_TRAP], trp, Color(1, 1, 1), 3, 17.6, 14.7);
		RenderTextOnScreen(meshList[GEO_INV_INCUBATOR], inc, Color(0.7, 0.7, 0), 3, 17.6, 10);
		RenderTextOnScreen(meshList[GEO_INV_CURRENCY], cur, Color(0, 0, 0), 3, 17.6, 5.9);
	}
	///////////////////////////////////////////////////////// END OF INVENTORY DISPLAY CODE /////////////////////////////////////////////////////////

	if (inGettingFruitsGame)
	{
		viewStack.PushMatrix();
			RenderGettingFruitsGameUI();
		viewStack.PopMatrix();
	}
}

void Scene3::RenderGettingFruitsGameUI()
{
	viewStack.PushMatrix();
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_WHITE], 40, 30, 40, 1); // Middle white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 1, 32, 80, 1);	// Top black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 1, 28, 80, 1);	// Bottom black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_GETTING_FRUITS_GAME_OBJECT], fruitMovingPosition, 30, 1, 1); // Middle red object
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 1, 30, 1, 3);	// Left black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 79, 30, 1, 3);	// Right black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 30, 30, 1, 1);	// Middle left black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 50, 30, 1, 1);	// Middle right black area

		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_WHITE], 1, 1, 80, 10);	 // Middle black area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 1, 1, 80, 1);	// Bottom white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 1, 10, 80, 1);	// Top white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 1, 1, 1, 10);	// Left white area
		RenderMeshOnScreen(meshList[GEO_PLACEHOLDER_UI_BLACK], 79, 1, 1, 10);	// Right white area

		if (fruitsGameDifficulty == 1)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "  Press 'E' when it's in the middle   ", Color(1, 0, 0), 2, 1.8, 3.7);
			RenderTextOnScreen(meshList[GEO_TEXT], " to advance. The higher the level the ", Color(1, 0, 0), 2, 1.8, 2.7);
			RenderTextOnScreen(meshList[GEO_TEXT], "  higher the chances of more fruits.  ", Color(1, 0, 0), 2, 1.8, 1.7);
		}
		else
		{
			std::ostringstream levelStream;
			levelStream << fruitsGameDifficulty;
			std::string getFruitLevel = levelStream.str();

			RenderTextOnScreen(meshList[GEO_TEXT], "              Level : " + getFruitLevel, Color(1, 0, 0), 2, 1.8, 2.7);
		}
	viewStack.PopMatrix();
}


void Scene3::Exit()
{
	glDeleteProgram(m_programID);
}

void Scene3::RenderMesh(Mesh *mesh, bool enableLight)
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

		// load material
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

void Scene3::RenderSkybox(float d, bool light)
{
	modelStack.PushMatrix();
	// modelStack.Rotate(0, 0, 0, 0);
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

	/*modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_BOTTOM], light);
	modelStack.PopMatrix();*/
}

void Scene3::RenderText(Mesh* mesh, std::string text, Color color)
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

void Scene3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) // Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	// Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); // size of screen UI
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

void Scene3::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); // size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); // No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, godlights); // UI should not have light, but i added for fun
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

bool Scene3::collision(Vector3 c)
{
	float ActualYpos = c.y - 20;

	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		if (c.x >= objs[i].minX && c.x <= objs[i].maxX &&
			c.z >= objs[i].minZ && c.z <= objs[i].maxZ &&
			ActualYpos >= objs[i].minY && ActualYpos <= objs[i].maxY)
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
