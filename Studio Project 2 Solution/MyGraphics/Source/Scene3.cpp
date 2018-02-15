#include "Scene3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <sstream>

//THIS IS THE SP FOLDER VERSION//
//THIS ONE IS TO BE MODIFIED FOR RELEASE//

Scene3::Scene3()
{
	//Keep this here//
	//Should be done everytime scene 3 is loaded up//
	/*bush1.harvestedBush = false; //Sets all bush to be harvestable upon startup
	bush1.harvestCheck = false;  //Check for single-time Harvest

	bush2.harvestedBush = false;
	bush2.harvestCheck = false;

	bush3.harvestedBush = false;
	bush3.harvestCheck = false;

	bush4.harvestedBush = false;
	bush4.harvestCheck = false;

	bush5.harvestedBush = false;
	bush5.harvestCheck = false;

	//Trap State Chart//
	//0 = no trap
	//1 = empty trap
	//2 = trapped animal

	//Checking Trap1 State//
	if (trap1State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap1State = 2;
			trappedBush1 = true;
		}
	}

	//Checking Trap2 State//
	if (trap2State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap2State = 2;
			trappedBush2 = true;
		}
	}

	//Checking Trap3 State//
	if (trap1State == 3)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap3State = 2;
			trappedBush3 = true;
		}
	}

	//Checking Trap4 State//
	if (trap4State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap4State = 2;
			trappedBush4 = true;
		}
	}

	//Checking Trap5 State//
	if (trap5State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap5State = 2;
			trappedBush5 = true;
		}
	}*/
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	framerate = 0.0f;
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);

	camera.Init(Vector3(0, 20, 20), Vector3(0, 0, 1), Vector3(0, 1, 0)); //init camera

	bush1.harvestedBush = false; //Sets all bush to be harvestable upon startup
	bush1.harvestCheck = false;  //Check for single-time Harvest

	bush2.harvestedBush = false;
	bush2.harvestCheck = false;

	bush3.harvestedBush = false;
	bush3.harvestCheck = false;

	bush4.harvestedBush = false;
	bush4.harvestCheck = false;

	bush5.harvestedBush = false;
	bush5.harvestCheck = false;

	//Trap State Chart//
	//0 = no trap
	//1 = empty trap
	//2 = trapped animal

	//Checking Trap1 State//
	if (trap1State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap1State = 2;
			trappedBush1 = true;
		}
	}

	//Checking Trap2 State//
	if (trap2State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap2State = 2;
			trappedBush2 = true;
		}
	}

	//Checking Trap3 State//
	if (trap1State == 3)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap3State = 2;
			trappedBush3 = true;
		}
	}

	//Checking Trap4 State//
	if (trap4State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap4State = 2;
			trappedBush4 = true;
		}
	}

	//Checking Trap5 State//
	if (trap5State == 1)
	{
		int TRAPCARD;
		srand(time(NULL));
		TRAPCARD = rand() % 70 + 1;

		if (TRAPCARD <= 70)
		{
			trap5State = 2;
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

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(0, 199, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 10;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(90));
	light[0].cosInner = cos(Math::DegreeToRadian(90));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

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
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::Generate2DQuad("back", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_LEFT] = MeshBuilder::Generate2DQuad("left", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::Generate2DQuad("right", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::Generate2DQuad("top", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::Generate2DQuad("bottom", 1.0f, 1.0f, 1.f, 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_EXPLAINTEXT] = MeshBuilder::GenerateText("foragingInstruction", 16, 16);
	meshList[GEO_EXPLAINTEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_INVINTERFACE] = MeshBuilder::Generate2DQuad("InvInterface", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	meshList[GEO_INVINTERFACE]->textureID = LoadTGA("Image//invInterface.tga");

	meshList[GEO_REDINV] = MeshBuilder::GenerateText("redInv", 16, 16);
	meshList[GEO_REDINV]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_BLUINV] = MeshBuilder::GenerateText("bluInv", 16, 16);
	meshList[GEO_BLUINV]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TRAPINV] = MeshBuilder::GenerateText("trpInv", 16, 16);
	meshList[GEO_TRAPINV]->textureID = LoadTGA("Image//calibri.tga");
	
	meshList[GEO_TRAPDEFAULT] = MeshBuilder::GenerateOBJ("defaultTrap", "OBJ//scene3Trap.obj");
	meshList[GEO_TRAPCAUGHT] = MeshBuilder::GenerateOBJ("caughtTrap", "OBJ//scene3Trapped.obj");

	meshList[GEO_BUSH] = MeshBuilder::GenerateOBJ("Bush", "OBJ//tempBush.obj");

	meshList[GEO_FRUITRED] = MeshBuilder::GenerateOBJ("Bush", "OBJ//tempFruit.obj");
	meshList[GEO_FRUITRED]->textureID = LoadTGA("Image/fruitRed.tga");
}

void Scene3::Update(double dt)
{
	framerate = 1.0 / dt;
	camera.Update(dt);

	if (Application::IsKeyPressed('6') || Application::IsKeyPressed('\b'))
	{
		SceneManager::instance()->SetNextScene(SceneManager::SCENEID_MAIN);
	}

	//Checking Bush 1//
	if (Application::IsKeyPressed('E') && (camera.position.x <= 125.0f && camera.position.x >= 95.0f && camera.position.z <= 85.0f && camera.position.z >= 55.0f)) //Harvest Bush Function
	{
		bush1.harvestedBush = true;

		if (bush1.harvestCheck == false)
		{
			getFruuts();
			bush1.harvestCheck = true;
		}
	}

	if (Application::IsKeyPressed('V') && (camera.position.x <= 125.0f && camera.position.x >= 95.0f && camera.position.z <= 85.0f && camera.position.z >= 55.0f)) //Trap Interactions
	{
		if ((trappedBush1 == false) && (invTraps != 0)) //Setting a trap
		{
			trap1State = 1;
			invTraps -= 1;
			trappedBush1 = true;
		}

		else if (trap1State == 2) //Collecting trapped animal
		{
			trappedBush1 = false;
			trap1State = 0;
			meat += 2;
		}
	}

	//Checking Bush 2//
	if (Application::IsKeyPressed('E') && (camera.position.x <= -15.0f && camera.position.x >= -45.0f && camera.position.z <= 65.0f && camera.position.z >= 35.0f)) //Harvest Bush Function
	{
		bush2.harvestedBush = true;

		if (bush2.harvestCheck == false)
		{
			getFruuts();
			bush2.harvestCheck = true;
		}
	}

	if (Application::IsKeyPressed('V') && (camera.position.x <= -15.0f && camera.position.x >= -45.0f && camera.position.z <= 65.0f && camera.position.z >= 35.0f)) //Trap Interactions
		{
			if ((trappedBush2 == false) && (invTraps != 0)) //Setting a trap
			{
				trappedBush2 = true;
				trap2State = 1;
				invTraps -= 1;
			}

			else if (trap2State == 2) //Collecting trapped animal
			{
				trappedBush2 = false;
				trap2State = 0;
				meat += 2;
			}
		}

	//Checking Bush 3//
	if (Application::IsKeyPressed('E') && (camera.position.x <= 165.0f && camera.position.x >= 135.0f && camera.position.z <= -75.0f && camera.position.z >= -105.0f)) //Harvest Bush Function
	{
		bush3.harvestedBush = true;

		if (bush3.harvestCheck == false)
		{
			getFruuts();
			bush3.harvestCheck = true;
		}
	}

	if (Application::IsKeyPressed('V') && (camera.position.x <= 165.0f && camera.position.x >= 135.0f && camera.position.z <= -75.0f && camera.position.z >= -105.0f)) //Trap Interactions
		{
			if (trappedBush3 == false) //Setting a trap
			{
				if (invTraps > 0) //Checks for traps in inv
				{
					trappedBush3 = true;
					trap3State = 1;
					invTraps -= 1;
				}
			}

			else if ((trappedBush3 == true) && (trap3State == 2)) //Collecting trapped animal
			{
				trappedBush3 = false;
				trap3State = 0;
				meat += 2;
			}
		}

	//Checking Bush 4//
	if (Application::IsKeyPressed('E') && (camera.position.x <= 95.0f && camera.position.x >= 65.0f && camera.position.z <= -135.0f && camera.position.z >= -165.0f)) //Harvest Bush Function
	{
		bush4.harvestedBush = true;

		if (bush4.harvestCheck == false)
		{
			getFruuts();
			bush4.harvestCheck = true;
		}
	}

	if (Application::IsKeyPressed('V') && (camera.position.x <= 95.0f && camera.position.x >= 65.0f && camera.position.z <= -135.0f && camera.position.z >= -165.0f)) //Trap Interactions
		{
			if (trappedBush4 == false) //Setting a trap
			{
				if (invTraps > 0) //Checks for traps in inv
				{
					trappedBush4 = true;
					trap4State = 1;
					invTraps -= 1;
				}
			}

			else if ((trappedBush4 == true) && (trap4State == 2)) //Collecting trapped animal
			{
				trappedBush4 = false;
				trap4State = 0;
				meat += 2;
			}
		}

	//Checking Bush 5//
	if (Application::IsKeyPressed('E') && (camera.position.x <= -55.0f && camera.position.x >= -85.0f && camera.position.z <= -85.0f && camera.position.z >= -115.0f)) //Harvest Bush Function
	{
		bush5.harvestedBush = true;

		if (bush5.harvestCheck == false)
		{
			getFruuts();
			bush5.harvestCheck = true;
		}
	}

	if (Application::IsKeyPressed('V') && (camera.position.x <= -55.0f && camera.position.x >= -85.0f && camera.position.z <= -85.0f && camera.position.z >= -115.0f)) //Trap Interactions
	{
		if (trappedBush5 == false) //Setting a trap
		{
			if (invTraps > 0) //Checks for traps in inv
			{
				trappedBush5 = true;
				trap5State = 1;
				invTraps -= 1;
			}
		}

		else if ((trappedBush5 == true) && (trap5State == 2)) //Collecting trapped animal
		{
			trappedBush5 = false;
			trap5State = 0;
			meat += 2;
		}
	}
}

void Scene3::getFruuts()
{
	int gain = 0;
	srand(time(NULL));
	gain = rand() % 5 + 1;
	redFruits += gain;
	bluFruits += (5 - gain);
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

	/*
	viewStack.PushMatrix();
	viewStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TRAPDEFAULT], godlights);
	viewStack.PopMatrix();
	*/

	//BUSH 1//
	viewStack.PushMatrix();
	viewStack.Translate(110, 0, 70);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(70, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], light);
	viewStack.PopMatrix();

	if (bush1.harvestedBush == false) //Bush 1 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(110, 30, 70);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_FRUITRED], light);
		viewStack.PopMatrix();
	}

	if (trap1State == 1) //Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(90, 0, 70);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(70, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], light);
		viewStack.PopMatrix();
	}

	 else if (trap1State == 2) //Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(90, 0, 70);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(70, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], light);
		viewStack.PopMatrix();
	}

	//BUSH 2//
	viewStack.PushMatrix();
	viewStack.Translate(-30, 0, 50);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(120, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], light);
	viewStack.PopMatrix();

	if (bush2.harvestedBush == false) //Bush 2 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(-30, 30, 50);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_FRUITRED], light);
		viewStack.PopMatrix();
	}

	if (trap2State == 1) //Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-18, 0, 36);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-50, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], light);
		viewStack.PopMatrix();
	}

	else if (trap2State == 2) //Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-18, 0, 36);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-50, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], light);
		viewStack.PopMatrix();
	}

	//BUSH 3//
	viewStack.PushMatrix();
	viewStack.Translate(150, 0, -90);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(10, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], light);
	viewStack.PopMatrix();

	if (bush3.harvestedBush == false) //Bush 3 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(150, 30, -90);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_FRUITRED], light);
		viewStack.PopMatrix();
	}

	if (trap3State == 1) //Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(130, 0, -77);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], light);
		viewStack.PopMatrix();
	}

	else if (trap3State == 2) //Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(130, 0, -77);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], light);
		viewStack.PopMatrix();
	}

	//BUSH 4//

	viewStack.PushMatrix();
	viewStack.Translate(80, 0, -150);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], light);
	viewStack.PopMatrix();
	if (bush4.harvestedBush == false) //Bush 4 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(80, 30, -150);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_FRUITRED], light);
		viewStack.PopMatrix();
	}

	if (trap4State == 1) //Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(66, 0, -137);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], light);
		viewStack.PopMatrix();
	}

	else if (trap4State == 2) //Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(66, 0, -137);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-230, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], light);
		viewStack.PopMatrix();
	}

	//BUSH 5//
	viewStack.PushMatrix();
	viewStack.Translate(-70, 0, -100);
	viewStack.Scale(15, 15, 15);
	viewStack.Rotate(50, 0, 1, 0);
	RenderMesh(meshList[GEO_BUSH], light);
	viewStack.PopMatrix();

	if (bush5.harvestedBush == false) //Bush 5 With fruits
	{
		viewStack.PushMatrix();
		viewStack.Translate(-70, 30, -100);
		viewStack.Scale(15, 15, 15);
		RenderMesh(meshList[GEO_FRUITRED], light);
		viewStack.PopMatrix();
	}

	if (trap5State == 1) //Trap w/o Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-91, 0, -95);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-100, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPDEFAULT], light);
		viewStack.PopMatrix();
	}

	else if (trap5State == 2) //Trap w/ Animal
	{
		viewStack.PushMatrix();
		viewStack.Translate(-91, 0, -95);
		viewStack.Scale(15, 15, 15);
		viewStack.Rotate(-100, 0, 1, 0);
		RenderMesh(meshList[GEO_TRAPCAUGHT], light);
		viewStack.PopMatrix();
	}

	//GENERATE TEXT ON SCREEN//
	std::ostringstream ah;
	ah << framerate;
	std::string str = ah.str();
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + str, Color(0, 1, 0), 2, 33, 29);
	RenderTextOnScreen(meshList[GEO_EXPLAINTEXT], "<E> to pick fruits", Color(0, 1, 0), 1.8, 27.5, 31);
	RenderTextOnScreen(meshList[GEO_EXPLAINTEXT], "<V> to set a trap", Color(0, 1, 0), 1.8, 28, 30);

	std::ostringstream inv1;
	inv1 << redFruits;
	std::ostringstream inv2;
	inv2 << bluFruits;
	std::ostringstream inv3;
	inv3 << meat;
	std::ostringstream inv4;
	inv4 << invTraps;
	std::string red = inv1.str();
	std::string blu = inv2.str();
	std::string met = inv3.str();
	std::string trp = inv4.str();

	RenderMeshOnScreen(meshList[GEO_INVINTERFACE], 10, 50, 10, 10);
	RenderTextOnScreen(meshList[GEO_REDINV], ":" + red, Color(1, 0, 0), 4, 2.7, 14.3);
	RenderTextOnScreen(meshList[GEO_BLUINV], ":" + blu, Color(0, 0, 1), 4, 2.7, 13);
	RenderTextOnScreen(meshList[GEO_BLUINV], ":" + met, Color(0.7, 0.31, 0), 4, 2.7, 11.9);
	RenderTextOnScreen(meshList[GEO_TRAPINV], ":" + trp, Color(1, 1, 1), 4, 2.7, 10.7);
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

void Scene3::RenderSkybox(float d, bool light)
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

void Scene3::RenderText(Mesh* mesh, std::string text, Color color)
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

void Scene3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void Scene3::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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
