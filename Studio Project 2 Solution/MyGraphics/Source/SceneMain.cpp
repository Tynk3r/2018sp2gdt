#include "SceneMain.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <sstream>


SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	framerate = 0.0f;
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);

	developerMode = false;
	Race1 = true;

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

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Lightings
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(80, 2, 80);
	light[0].color.Set(0.9, 0.6, 0.125);
	light[0].power = 6;
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
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_FRONT] = MeshBuilder::Generate2DQuad("front", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	if (MyPtero::instance()->pteroStage == MyPtero::P_EGG) {
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//mainfront2.tga");
	}
	else {
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//mainfront.tga");
	}
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

	meshList[GEO_QUAD] = MeshBuilder::Generate2DQuad("genericquad", 1.0f, 1.0f, 1.f, 1.f, 1.f);

	meshList[GEO_PORTAL] = MeshBuilder::Generate2DQuad("portal", 1.0f, 1.0f, 0.f, 0.f, 0.f);
	meshList[GEO_PORTAL]->textureID = LoadTGA("Image//portal1.tga");

	meshList[GEO_DINOEGG] = MeshBuilder::GenerateOBJ("objs1", "OBJ//dinoegg.obj");
	meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//dinoegg.tga");
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//tree.tga");
	meshList[GEO_FIREBASE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//campfireBase.obj");
	meshList[GEO_FIREBASE]->textureID = LoadTGA("Image//campfireBase.tga");
	meshList[GEO_FIREWOOD] = MeshBuilder::GenerateOBJ("Tree", "OBJ//campfireWood.obj");
	meshList[GEO_FIREWOOD]->textureID = LoadTGA("Image//campfireWood.tga");
	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJ("Tree", "OBJ//rock.obj");
	meshList[GEO_ROCK]->textureID = LoadTGA("Image//rock1.tga");
	meshList[GEO_BORDER] = MeshBuilder::GenerateOBJ("Tree", "OBJ//border.obj");
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//rock1.tga");
	meshList[GEO_FERN] = MeshBuilder::GenerateOBJ("Tree", "OBJ//fern.obj");
	meshList[GEO_FERN]->textureID = LoadTGA("Image//fern.tga");

	//Set Object Positions//
	objs[OBJ_DINOEGG].setBox(Vector3(0, 0, 0), 20);
	objs[OBJ_TREE1].setBox(Vector3(-50, -16, -30), 8, 40, 8);
	objs[OBJ_TREE2].setBox(Vector3(-80, -16, -100), 8, 40, 8);
	objs[OBJ_TREE3].setBox(Vector3(50, -16, -10), 8, 40, 8);
	objs[OBJ_ROCK1].setBox(Vector3(100, 0, -80), 50);
	objs[OBJ_ROCK2].setBox(Vector3(-140, 0, 80), 50);
	objs[OBJ_ROCK3].setBox(Vector3(-80, 0, -30), 50);
	objs[OBJ_CAMPFIRE].setBox(Vector3(80, 0, 80), 0.1);

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
}

void SceneMain::Update(double dt)
{
	framerate = 1.0 / dt;
	camera.Update(dt);
	Inventory::instance()->Update();

	// portals
	if (camera.position.z <= -185.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f && MyPtero::instance()->pteroStage != MyPtero::instance()->P_EGG)
	{
		if (!developerMode)
		{
			//1/2 chance for either race track
			int track = rand() % 3 + 1;
			if (track == 1)
			{
				SceneManager::instance()->SetNextScene(SceneManager::SCENEID_1);
			}
			else
			{
				SceneManager::instance()->SetNextScene(SceneManager::SCENEID_1_5);
			}
		}
		else
		{
			if (Race1)
			{
				SceneManager::instance()->SetNextScene(SceneManager::SCENEID_1);
			}
			else
			{
				SceneManager::instance()->SetNextScene(SceneManager::SCENEID_1_5);
			}
		}
	}
	else if (camera.position.x <= -195.0f && camera.position.z >= -15.0f && camera.position.z <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_2);
	}
	else if (camera.position.z >= 195.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_3);
	}
	else if (camera.position.x >= 195.0f && camera.position.z >= -15.0f && camera.position.z <= 15.0f)
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_4);
	}

	if (Application::IsKeyPressed(VK_NUMPAD1))
	{
		developerMode = true;
	}
	if (Application::IsKeyPressed(VK_NUMPAD2))
	{
		developerMode = false;
	}
	if (Application::IsKeyPressed(VK_NUMPAD3))
	{
		if (developerMode)
		{
			Race1 = true;
		}
	}
	if (Application::IsKeyPressed(VK_NUMPAD4))
	{
		if (developerMode)
		{
			Race1 = false;
		}
	}
	rotateMain++;
}

void SceneMain::Render()
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
			RenderSkybox(500.0f, false);
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

	//Campfire//
	viewStack.PushMatrix();
		viewStack.Translate(objs[7].getPos().x, objs[7].getPos().y, objs[7].getPos().z);
		viewStack.Scale(objs[OBJ_CAMPFIRE].getSizeX(), objs[OBJ_CAMPFIRE].getSizeY(), objs[OBJ_CAMPFIRE].getSizeZ());
		viewStack.Rotate(0, 0, 1, 0);
		RenderMesh(meshList[GEO_FIREBASE], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
		viewStack.Translate(objs[7].getPos().x, objs[7].getPos().y, objs[7].getPos().z);
		viewStack.Scale(objs[OBJ_CAMPFIRE].getSizeX(), objs[OBJ_CAMPFIRE].getSizeY(), objs[OBJ_CAMPFIRE].getSizeZ());
		viewStack.Rotate(0, 0, 1, 0);
		RenderMesh(meshList[GEO_FIREWOOD], godlights);
	viewStack.PopMatrix();

	//BORDER//
	viewStack.PushMatrix();
		viewStack.Translate(0,0,-10);
		viewStack.Scale(20,30,20);
		viewStack.Rotate(45, 0, 1, 0);
		RenderMesh(meshList[GEO_BORDER], godlights);
	viewStack.PopMatrix();

	viewStack.PushMatrix();
		viewStack.Translate(0, 0, -10);
		viewStack.Scale(23, 60, 23);
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

	//Portals//
	viewStack.PushMatrix(); // scene 1
		viewStack.Translate(0, 20, -200);
		viewStack.PushMatrix();
			viewStack.Translate(-17.25, 30, 0);
			viewStack.Scale(3.75, 3.75, 3.75);
			RenderText(meshList[GEO_TEXT], "PTERODACTYL", (1, 1, 1));
			viewStack.Translate(0.15, -1.4, 0);
			viewStack.Scale(2, 2, 2);
			RenderText(meshList[GEO_TEXT], "RACING", (1, 1, 1));
		viewStack.PopMatrix();
		viewStack.Rotate(rotateMain, 0, 0, 1);
		viewStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_PORTAL], false);
	viewStack.PopMatrix();
	viewStack.PushMatrix(); // scene 2
		viewStack.Translate(-200, 20, 0);
		viewStack.Rotate(90, 0, 1, 0);
		viewStack.PushMatrix();
			viewStack.Translate(-17.25, 30, 0);
			viewStack.Scale(3.75, 3.75, 3.75);
			RenderText(meshList[GEO_TEXT], "PTERODACTYL", (1, 1, 1));
			viewStack.Translate(-0.5, -1.4, 0);
			viewStack.Scale(2, 2, 2);
			RenderText(meshList[GEO_TEXT], "NURSERY", (1, 1, 1));
		viewStack.PopMatrix();
		viewStack.Rotate(rotateMain, 0, 0, 1);
		viewStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_PORTAL], false);
	viewStack.PopMatrix();
	viewStack.PushMatrix(); // scene 3
		viewStack.Translate(0, 20, 200);
		viewStack.Rotate(180, 0, 1, 0);
		viewStack.PushMatrix();
			viewStack.Translate(-17.25, 30, 0);
			viewStack.Scale(3.75, 3.75, 3.75);
			RenderText(meshList[GEO_TEXT], "HUNTING AND", (1, 1, 1));
			viewStack.Translate(-2, -1.4, 0);
			viewStack.Scale(2, 2, 2);
			RenderText(meshList[GEO_TEXT], "FORAGING", (1, 1, 1));
		viewStack.PopMatrix();
		viewStack.Rotate(rotateMain, 0, 0, 1);
		viewStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_PORTAL], false);
	viewStack.PopMatrix();
	viewStack.PushMatrix(); // scene 4
		viewStack.Translate(200, 20, 0);
		viewStack.Rotate(-90, 0, 1, 0);
		viewStack.PushMatrix();
			viewStack.Translate(-17.25, 30, 0);
			viewStack.Scale(3.75, 3.75, 3.75);
			RenderText(meshList[GEO_TEXT], "PTERODACTYL", (1, 1, 1));
			viewStack.Translate(-0.5, -1.4, 0);
			viewStack.Scale(2, 2, 2);
			RenderText(meshList[GEO_TEXT], "VILLAGE", (1, 1, 1));
		viewStack.PopMatrix();
		viewStack.Rotate(rotateMain, 0, 0, 1);
		viewStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_PORTAL], false);
	viewStack.PopMatrix();

	//End of Environment//

	viewStack.PushMatrix();
		viewStack.Translate(objs[0].getPos().x, objs[0].getPos().y, objs[0].getPos().z);

		viewStack.PushMatrix();
			viewStack.Scale(objs[0].getSize(), objs[0].getSize(), objs[0].getSize());
			viewStack.Rotate(rotateMain, 0, 1, 0);
			RenderMesh(meshList[GEO_DINOEGG], godlights);
		viewStack.PopMatrix();

		viewStack.PushMatrix();
			viewStack.Translate(-18, 35, 0);
			viewStack.Scale(4, 4, 4);
			viewStack.PushMatrix();
				viewStack.PushMatrix();
					viewStack.Translate(4.5, -1, 0);
					viewStack.Scale(8.5, 2, 2);
					RenderMesh(meshList[GEO_QUAD], godlights);
				viewStack.PopMatrix();
				RenderText(meshList[GEO_TEXT], "WELCOME TO", Color(0, 1, 0));
				viewStack.Translate(-3, -2, 0);
				viewStack.Scale(2, 2, 2);
				RenderText(meshList[GEO_TEXT], "PTEROPETS", Color(1, 0, 0));
			viewStack.PopMatrix();
		viewStack.PopMatrix();
	viewStack.PopMatrix();

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

	std::ostringstream ah;
	ah << framerate;
	std::string str = ah.str();
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + str, Color(0, 1, 0), 2, 33, 29);

	if (camera.position.z <= -185.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f && MyPtero::instance()->pteroStage == MyPtero::instance()->P_EGG)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Your Pterodactyl can't fly yet!", Color(1, 0.1, 0.1), 2.3, 4, 11);
	}

	if (developerMode)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Developer Mode", Color(0, 1, 0), 2, 1, 1);
		std::ostringstream oh;
		oh << Race1;
		std::string str2 = oh.str();
		RenderTextOnScreen(meshList[GEO_TEXT], "Is Race Track 1:" + str2, Color(1, 1, 0), 2, 1, 2);
	}
}

void SceneMain::Exit()
{
	glDeleteProgram(m_programID);
}

void SceneMain::RenderMesh(Mesh *mesh, bool enableLight)
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

void SceneMain::RenderSkybox(float d, bool light)
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
}

void SceneMain::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneMain::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneMain::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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

bool SceneMain::collision(Vector3 c)
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