#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <ctime>
#include <sstream>
#include "Inventory.h"


Scene2::Scene2()
{
	MyPtero::instance()->pteroStage = MyPtero::P_BABY;
	MyPtero::instance()->pteroType = MyPtero::T_GREEN;
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	srand(time(NULL));
	framerate = 0.0f;
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);

	camera.Init(Vector3(0, 10, 0), Vector3(0, 10, 1), Vector3(0, 1, 0)); //init camera

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

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(2, 2, 2);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(-1, -1, -1);
	light[1].color.Set(1, 1, 1);
	light[1].power = 2;
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

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

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
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//2front.tga");
	meshList[GEO_BACK] = MeshBuilder::Generate2DQuad("back", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//2back.tga");
	meshList[GEO_LEFT] = MeshBuilder::Generate2DQuad("left", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//2left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::Generate2DQuad("right", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//2right.tga");
	meshList[GEO_TOP] = MeshBuilder::Generate2DQuad("top", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//2top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::Generate2DQuad("bottom", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//2bottom.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_QUAD] = MeshBuilder::Generate2DQuad("genericquad", 1.0f, 1.0f, 1.f, 1.f, 1.f);

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

	meshList[GEO_DINOEGG] = MeshBuilder::GenerateOBJ("objs1", "OBJ//dinoegg.obj");
	meshList[GEO_PTERO] = MeshBuilder::GenerateOBJ("objs2", "OBJ//pterodactyl.obj");
	switch (MyPtero::instance()->pteroType) {
	case MyPtero::T_GREEN:
		meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//greendino.tga");
		meshList[GEO_PTERO]->textureID = LoadTGA("Image//greendino.tga");
		break;
	case MyPtero::T_RED:
		meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//REDdino.tga");
		meshList[GEO_PTERO]->textureID = LoadTGA("Image//REDdino.tga");
		break;
	case MyPtero::T_PURPLE:
		meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//PURPLEdino.tga");
		meshList[GEO_PTERO]->textureID = LoadTGA("Image//PURPLEdino.tga");
		break;
	}
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("objs3", "OBJ//fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//fence.tga");
	meshList[GEO_CAMPFIRE_BASE] = MeshBuilder::GenerateOBJ("objs4", "OBJ//campfireBase.obj");
	meshList[GEO_CAMPFIRE_BASE]->textureID = LoadTGA("Image//campfireBase.tga");
	meshList[GEO_CAMPFIRE_WOOD] = MeshBuilder::GenerateOBJ("objs5", "OBJ//campfireWood.obj");
	meshList[GEO_CAMPFIRE_WOOD]->textureID = LoadTGA("Image//campfireWood.tga");
	meshList[GEO_SKELETON] = MeshBuilder::GenerateOBJ("objs6", "OBJ//skeleton.obj");
	meshList[GEO_SKELETON]->textureID = LoadTGA("Image//skeleton.tga");
	meshList[GEO_INCUBATOR] = MeshBuilder::GenerateOBJ("objs7", "OBJ//incubator.obj");
	meshList[GEO_INCUBATOR]->textureID = LoadTGA("Image//incubator.tga");

	objs[OBJ_FENCE].setBox(Vector3(100.0, 0, 25), 400, 10, 10); // left most fence and sizeX spans whole level
	objs[OBJ_CAMPFIRE].setBox(Vector3(50, 0, 0), 0.1);
	objs[OBJ_SKELETON].setBox(Vector3(-70, 0, 70), 2);
	objs[OBJ_INCUBATOR].setBox(Vector3(70, -1, 85), 7);

	camera.SkyboxSize = 100.0f;

	//updating stage
	switch (MyPtero::instance()->pteroStage)	{
	case MyPtero::P_EGG:
		if (MyPtero::instance()->incubating) {
			MyPtero::instance()->pteroStage++;
		}
		MyPtero::instance()->incubating = false;
		break;
	case MyPtero::P_BABY:
		if (!MyPtero::instance()->hungry) {
			MyPtero::instance()->pteroStage++;
		}
		MyPtero::instance()->hungry = true;
		break;
	case MyPtero::P_ADOLESCENT:
		if (!MyPtero::instance()->hungry) {
			MyPtero::instance()->pteroStage++;
		}
		MyPtero::instance()->hungry = true;
		break;
	case MyPtero::P_ADULT:
		MyPtero::instance()->hungry = true;
		break;
	default:
		break;
	}
	// movement speed
	switch (MyPtero::instance()->pteroStage) {
	case MyPtero::P_EGG:
		MyPtero::instance()->pteroMovementSpeed = 0.0f;
		break;
	case MyPtero::P_BABY:
		MyPtero::instance()->pteroMovementSpeed = 0.5f;
		break;
	case MyPtero::P_ADOLESCENT:
		MyPtero::instance()->pteroMovementSpeed = 0.5f;
		break;
	case MyPtero::P_ADULT:
		MyPtero::instance()->pteroMovementSpeed = 0.5f;
		break;
	default:
		break;
	}
}

void Scene2::Update(double dt)
{
	framerate = 1.0 / dt;
	camera.Update(dt);
	Inventory::instance()->Update(dt);

	if (camera.position.z <= -85.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_MAIN);
	}
	// feed/incubate
	if (Application::IsKeyPressed('X') && camera.position.z > 0.0f)
	{
		// hungry + Meat
		if (MyPtero::instance()->hungry && MyPtero::instance()->pteroStage != MyPtero::P_EGG && Inventory::instance()->items[ITEMS_MEAT] > 0) {
			MyPtero::instance()->hungry = false;
			Inventory::instance()->items[ITEMS_MEAT]--;
		}
		// egg + incubator
		if (MyPtero::instance()->pteroStage == MyPtero::P_EGG && !MyPtero::instance()->incubating && Inventory::instance()->items[ITEMS_INCUBATOR] > 0) {
			MyPtero::instance()->incubating = true;
			Inventory::instance()->items[ITEMS_INCUBATOR]--;
		}
	}
	// reset ptero
	if (Application::IsKeyPressed('X') && camera.position.x > 25.0f && camera.position.z < -25.0 && Inventory::instance()->items[ITEMS_CURRENCY] >= 25) {
		Inventory::instance()->items[ITEMS_CURRENCY] -= 25;
		MyPtero::instance()->newPtero();
		switch (MyPtero::instance()->pteroType) {
		case MyPtero::T_GREEN:
			meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//greendino.tga");
			meshList[GEO_PTERO]->textureID = LoadTGA("Image//greendino.tga");
			break;
		case MyPtero::T_RED:
			meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//REDdino.tga");
			meshList[GEO_PTERO]->textureID = LoadTGA("Image//REDdino.tga");
			break;
		case MyPtero::T_PURPLE:
			meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//PURPLEdino.tga");
			meshList[GEO_PTERO]->textureID = LoadTGA("Image//PURPLEdino.tga");
			break;
		}
	}

	// ptero movement
	int r = rand() % 200 + 1;
	switch ((int)MyPtero::instance()->pteroDirection) {
	case 180:	// front
		switch (r) {
		case 1: // back
			MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 0.0f;
			break;
		case 2: // right
			MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 90.0f;
			break;
		case 3: // left
			MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 270.0f;
			break;
		default: // front
			MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 180.0f;
			break;
		}
		break;
	case 90:		// right
		switch (r) {
		case 1: // back
			MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 0.0f;
			break;
		case 2: // front
			MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 180.0f;
			break;
		case 3: // left
			MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 270.0f;
			break;
		default: // right
			MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 90.0f;
			break;
		}
		break;
	case 0:		// back
		switch (r) {
		case 1: // right
			MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 90.0f;
			break;
		case 2: // front
			MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 180.0f;
			break;
		case 3: // left
			MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 270.0f;
			break;
		default: // back
			MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 0.0f;
			break;
		}
		break;
	case 270:	// left
		switch (r) {
		case 1: // right
			MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 90.0f;
			break;
		case 2: // front
			MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 180.0f;
			break;
		case 3: // back
			MyPtero::instance()->pteroLocationZ += MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationZ >= 90.0f || MyPtero::instance()->pteroLocationZ <= 25.0f) {
				MyPtero::instance()->pteroLocationZ -= MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 0.0f;
			break;
		default: // left
			MyPtero::instance()->pteroLocationX -= MyPtero::instance()->pteroMovementSpeed;
			if (MyPtero::instance()->pteroLocationX >= 90.0f || MyPtero::instance()->pteroLocationX <= -90.0f) {
				MyPtero::instance()->pteroLocationX += MyPtero::instance()->pteroMovementSpeed;
			}
			MyPtero::instance()->pteroDirection = 270.0f;
			break;
		}
		break;
	default:
		MyPtero::instance()->pteroDirection = 180;
		break;
	}
}

void Scene2::Render()
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

	RenderSkybox(camera.SkyboxSize, godlights);

	// pterodactyl
	switch (MyPtero::instance()->pteroStage) {
	case MyPtero::P_EGG:
		viewStack.PushMatrix();
		viewStack.Translate(MyPtero::instance()->pteroLocationX, 0, MyPtero::instance()->pteroLocationZ);
		viewStack.Scale(10 * MyPtero::instance()->pteroSize, 10 * MyPtero::instance()->pteroSize, 10 * MyPtero::instance()->pteroSize);
		RenderMesh(meshList[GEO_DINOEGG], godlights);
		viewStack.PopMatrix();
		break;
	case MyPtero::P_BABY:
		viewStack.PushMatrix();
		viewStack.Translate(MyPtero::instance()->pteroLocationX, 10, MyPtero::instance()->pteroLocationZ);
		viewStack.Rotate(MyPtero::instance()->pteroDirection, 0, 1, 0);
		viewStack.Scale(10 * MyPtero::instance()->pteroSize, 10 * MyPtero::instance()->pteroSize, 10 * MyPtero::instance()->pteroSize);
		RenderMesh(meshList[GEO_PTERO], godlights);
		viewStack.PopMatrix();
		break;
	case MyPtero::P_ADOLESCENT:
		viewStack.PushMatrix();
		viewStack.Translate(MyPtero::instance()->pteroLocationX, 15, MyPtero::instance()->pteroLocationZ);
		viewStack.Rotate(MyPtero::instance()->pteroDirection, 0, 1, 0);
		viewStack.Scale(25 * MyPtero::instance()->pteroSize, 25 * MyPtero::instance()->pteroSize, 25 * MyPtero::instance()->pteroSize);
		RenderMesh(meshList[GEO_PTERO], godlights);
		viewStack.PopMatrix();
		break;
	case MyPtero::P_ADULT:
		viewStack.PushMatrix();
		viewStack.Translate(MyPtero::instance()->pteroLocationX, 25, MyPtero::instance()->pteroLocationZ);
		viewStack.Rotate(MyPtero::instance()->pteroDirection, 0, 1, 0);
		viewStack.Scale(40 * MyPtero::instance()->pteroSize, 40 * MyPtero::instance()->pteroSize, 40 * MyPtero::instance()->pteroSize);
		RenderMesh(meshList[GEO_PTERO], godlights);
		viewStack.PopMatrix();
		break;
	default:
		break;
	}
	// fences
	for (int i = 0; i <= 200; i += 10) {
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_FENCE].getPos().x - i, objs[OBJ_FENCE].getPos().y, objs[OBJ_FENCE].getPos().z);
		viewStack.Scale(objs[OBJ_FENCE].getSizeY(), objs[OBJ_FENCE].getSizeY(), objs[OBJ_FENCE].getSizeY());
		RenderMesh(meshList[GEO_FENCE], godlights);
		viewStack.PopMatrix();
	}
	//campfire
	viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_CAMPFIRE].getPos().x, objs[OBJ_CAMPFIRE].getPos().y, objs[OBJ_CAMPFIRE].getPos().z);
		viewStack.Rotate(0, 0, 1, 0);
		viewStack.Scale(objs[OBJ_CAMPFIRE].getSizeX(), objs[OBJ_CAMPFIRE].getSizeY(), objs[OBJ_CAMPFIRE].getSizeZ());
		RenderMesh(meshList[GEO_CAMPFIRE_BASE], godlights);
		RenderMesh(meshList[GEO_CAMPFIRE_WOOD], godlights);
	viewStack.PopMatrix();
	//skeleton
	viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_SKELETON].getPos().x, objs[OBJ_SKELETON].getPos().y, objs[OBJ_SKELETON].getPos().z);
		viewStack.Rotate(32, 0, 1, 0);
		viewStack.Scale(objs[OBJ_SKELETON].getSizeX(), objs[OBJ_SKELETON].getSizeY(), objs[OBJ_SKELETON].getSizeZ());
		RenderMesh(meshList[GEO_SKELETON], godlights);
	viewStack.PopMatrix();
	// incubator
	viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_INCUBATOR].getPos().x, objs[OBJ_INCUBATOR].getPos().y, objs[OBJ_INCUBATOR].getPos().z);
		viewStack.Rotate(180, 0, 1, 0);
		viewStack.Scale(objs[OBJ_INCUBATOR].getSizeX(), objs[OBJ_INCUBATOR].getSizeY(), objs[OBJ_INCUBATOR].getSizeZ());
		RenderMesh(meshList[GEO_INCUBATOR], godlights);
	viewStack.PopMatrix();
	// screen
	std::ostringstream sh;
	sh << MyPtero::instance()->pteroSize;
	std::ostringstream sp;
	sp << MyPtero::instance()->pteroSpeedModifier;
	std::string sg;
	switch (MyPtero::instance()->pteroStage) {
	case MyPtero::P_EGG:
		sg = "INCUBATOR";
		break;
	case MyPtero::P_BABY:
		sg = "  1MEAT";
		break;
	case MyPtero::P_ADOLESCENT:
		sg = "  1MEAT";
		break;
	case MyPtero::P_ADULT:
		sg = "  1MEAT";
		break;
	default:
		break;
	}
	viewStack.PushMatrix();
		viewStack.Translate(40, 25, -99.9);
		viewStack.Rotate(0, 0, 1, 0);
		viewStack.Scale(2, 2, 2);
		viewStack.PushMatrix();
			viewStack.Translate(8, -4.5, 0);
			viewStack.Scale(16, 7, 1);
			RenderMesh(meshList[GEO_QUAD], godlights);
		viewStack.PopMatrix();
		viewStack.Translate(-5, 0, 0);
		viewStack.Scale(3, 3, 3);
		RenderText(meshList[GEO_TEXT], "Speed:" + sp.str(), Color(1, 0, 0));
		viewStack.Translate(0, -1, 0);
		RenderText(meshList[GEO_TEXT], "Size: " + sh.str(), Color(1, 0, 0));
		viewStack.Translate(0, -1, 0);
		viewStack.PushMatrix();
			viewStack.Translate(0, 0, 0);
			viewStack.Scale(0.5, 0.5, 0.5);
			RenderText(meshList[GEO_TEXT], "Needed to Progress: ", Color(1, 0, 0));
		viewStack.PopMatrix();
		viewStack.Translate(0.5, -1, 0);
		RenderText(meshList[GEO_TEXT], sg, Color(1, 0, 0));
	viewStack.PopMatrix();
	// reset button
	if (camera.position.x > 25.0f && camera.position.z < -25.0f && Inventory::instance()->items[ITEMS_CURRENCY] >= 25) {
		viewStack.PushMatrix();
			viewStack.Translate(99.9, 15, -70);
			viewStack.Rotate(-90, 0, 1, 0);
			viewStack.Scale(2, 2, 2);
			viewStack.PushMatrix();
				viewStack.Translate(0, -0.5, 0);
				viewStack.Scale(11, 2, 1);
				RenderMesh(meshList[GEO_QUAD], godlights);
			viewStack.PopMatrix();
			viewStack.Translate(-9.25, 0, 0);
			viewStack.Scale(0.9, 1, 1);
			RenderText(meshList[GEO_TEXT], "       PRESS X", Color(1, 0, 0));
			viewStack.Translate(1, -1, 0);
			RenderText(meshList[GEO_TEXT], "TO RESET PTERODACTYL", Color(1, 0, 0));
		viewStack.PopMatrix();
	}

	switch (MyPtero::instance()->pteroStage) {
	case MyPtero::P_EGG:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: EGG", Color(1, 1, 1), 3, 1, 1);
		if (MyPtero::instance()->incubating) {
			RenderTextOnScreen(meshList[GEO_TEXT], "EGG INCUBATED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z > 0.0f) {
			if (Inventory::instance()->items[ITEMS_INCUBATOR] > 0) {
				RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO INCUBATE EGG", Color(1, 0, 0), 2, 1, 29);
			}
			else {
				RenderTextOnScreen(meshList[GEO_TEXT], "OBTAIN INCUBATOR", Color(1, 0, 0), 2, 1, 29);
			}
		}
		break;
	case MyPtero::P_BABY:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: BABY", Color(0, 1, 0), 3, 1, 1);
		if (!MyPtero::instance()->hungry) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PTERODACTYL FED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z > 0.0f) {
			if (Inventory::instance()->items[ITEMS_MEAT] > 0) {
				RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO FEED PTERODACTYL", Color(1, 0, 0), 2, 1, 29);
			}
			else {
				RenderTextOnScreen(meshList[GEO_TEXT], "GATHER MEAT TO FEED", Color(1, 0, 0), 2, 1, 29);
			}
		}
		break;
	case MyPtero::P_ADOLESCENT:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: ADOLESCENT", Color(0, 1, 0), 3, 1, 1);
		if (!MyPtero::instance()->hungry) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PTERODACTYL FED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z > 0.0f) {
			if (Inventory::instance()->items[ITEMS_MEAT] > 0) {
				RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO FEED PTERODACTYL", Color(1, 0, 0), 2, 1, 29);
			}
			else {
				RenderTextOnScreen(meshList[GEO_TEXT], "GATHER MEAT TO FEED", Color(1, 0, 0), 2, 1, 29);
			}
		}
		break;
	case MyPtero::P_ADULT:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: ADULT", Color(0, 1, 0), 3, 1, 1);
		if (!MyPtero::instance()->hungry) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PTERODACTYL FED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z > 0.0f) {
			if (Inventory::instance()->items[ITEMS_MEAT] > 0) {
				RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO FEED PTERODACTYL", Color(1, 0, 0), 2, 1, 29);
			}
			else {
				RenderTextOnScreen(meshList[GEO_TEXT], "GATHER MEAT TO FEED", Color(1, 0, 0), 2, 1, 29);
			}
		}
		break;
	default:
		break;
	}

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

	if (Inventory::instance()->showInventory)
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
}

void Scene2::Exit()
{
	glDeleteProgram(m_programID);
}

void Scene2::RenderMesh(Mesh *mesh, bool enableLight)
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

void Scene2::RenderSkybox(float d, bool light)
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
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(d, d, d);
	RenderMesh(meshList[GEO_BOTTOM], light);
	modelStack.PopMatrix();
}

void Scene2::RenderText(Mesh* mesh, std::string text, Color color)
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

void Scene2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

bool Scene2::collision(Vector3 c)
{
	float ActualYpos = c.y - 10;

	for (int i = 0; i < NUM_OBJECTS; i++)
	{
		if (c.x >= objs[i].minX && c.x <= objs[i].maxX &&
			c.z >= objs[i].minZ && c.z <= objs[i].maxZ &&
			ActualYpos >= objs[i].minY && ActualYpos <= objs[i].maxY)
		{
			return true;
		}
	}

	if (c.x >= camera.SkyboxSize || c.x <= -camera.SkyboxSize || c.z >= camera.SkyboxSize || c.z <= -camera.SkyboxSize || c.y >= camera.SkyboxSize || c.y <= -camera.SkyboxSize) {
		return true;
	}
	else {
		return false;
	}
}

void Scene2::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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