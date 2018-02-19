#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <string>
#include <sstream>


Scene2::Scene2()
{
	pteroStage = P_BABY;
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	framerate = 0.0f;
	glClearColor(0.05f, 0.05f, 0.05f, 0.0f);

	camera.Init(Vector3(0, 10, 0), Vector3(0, 10, 62.5), Vector3(0, 1, 0)); //init camera

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

	meshList[GEO_DINOEGG] = MeshBuilder::GenerateOBJ("objs1", "OBJ//dinoegg.obj");
	meshList[GEO_DINOEGG]->textureID = LoadTGA("Image//dinoegg.tga");
	meshList[GEO_PTERO] = MeshBuilder::GenerateOBJ("objs2", "OBJ//pterodactyl.obj");
	meshList[GEO_PTERO]->textureID = LoadTGA("Image//pterodactyl.tga");
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("objs3", "OBJ//fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//fence.tga");

	objs[OBJ_DINOEGG].setBox(Vector3(0, 0, 62.5), 10); 
	objs[OBJ_PTERO_BABY].setBox(Vector3(0, 5, 62.5), 10); 
	objs[OBJ_PTERO_ADOLESCENT].setBox(Vector3(0, 10, 62.5), 25);
	objs[OBJ_PTERO_ADULT].setBox(Vector3(0, 15, 62.5), 40);
	objs[OBJ_FENCE].setBox(Vector3(100.0, 0, 25), 400, 10, 10); // left most fence and sizeX spans whole level

	camera.SkyboxSize = 100.0f;

	switch (pteroStage)	{
	case P_EGG:
		if (incubating) {
			pteroStage++;
		}
		incubating = false;
		break;
	case P_BABY:
		if (!hungry) {
			pteroStage++;
		}
		hungry = true;
		break;
	case P_ADOLESCENT:
		if (!hungry) {
			pteroStage++;
		}
		hungry = true;
		break;
	case P_ADULT:
		hungry = true;
		break;
	default:
		break;
	}

}

void Scene2::Update(double dt)
{
	framerate = 1.0 / dt;
	camera.Update(dt);

	//std::cout << camera.position.x << ", " << camera.position.z << std::endl;

	if (camera.position.z <= -85.0f && camera.position.x >= -15.0f && camera.position.x <= 15.0f)
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
	if (Application::IsKeyPressed('X') && camera.position.z >= 19.0f)
	{
		if (hungry && pteroStage != P_EGG) {
			hungry = false;
		}
		if (pteroStage == P_EGG && !incubating) {
			std::cout << "Incubating egg" << std::endl;
		}
	}
	
	rotateMain++;
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

	RenderSkybox(camera.SkyboxSize, godlights);
	RenderMesh(meshList[GEO_AXES], false);

	switch (pteroStage) {
	case P_EGG:
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_DINOEGG].getPos().x, objs[OBJ_DINOEGG].getPos().y, objs[OBJ_DINOEGG].getPos().z);
		viewStack.Scale(objs[OBJ_DINOEGG].getSize(), objs[OBJ_DINOEGG].getSize(), objs[OBJ_DINOEGG].getSize());
		RenderMesh(meshList[GEO_DINOEGG], godlights);
		viewStack.PopMatrix();
		break;
	case P_BABY:
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_PTERO_BABY].getPos().x, objs[OBJ_PTERO_BABY].getPos().y, objs[OBJ_PTERO_BABY].getPos().z);
		viewStack.Rotate(180, 0, 1, 0);
		viewStack.Scale(objs[OBJ_PTERO_BABY].getSize(), objs[OBJ_PTERO_BABY].getSize(), objs[OBJ_PTERO_BABY].getSize());
		RenderMesh(meshList[GEO_PTERO], godlights);
		viewStack.PopMatrix();
		break;
	case P_ADOLESCENT:
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_PTERO_ADOLESCENT].getPos().x, objs[OBJ_PTERO_ADOLESCENT].getPos().y, objs[OBJ_PTERO_ADOLESCENT].getPos().z);
		viewStack.Rotate(180, 0, 1, 0);
		viewStack.Scale(objs[OBJ_PTERO_ADOLESCENT].getSize(), objs[OBJ_PTERO_ADOLESCENT].getSize(), objs[OBJ_PTERO_ADOLESCENT].getSize());
		RenderMesh(meshList[GEO_PTERO], godlights);
		viewStack.PopMatrix();
		break;
	case P_ADULT:
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_PTERO_ADULT].getPos().x, objs[OBJ_PTERO_ADULT].getPos().y, objs[OBJ_PTERO_ADULT].getPos().z);
		viewStack.Rotate(180, 0, 1, 0);
		viewStack.Scale(objs[OBJ_PTERO_ADULT].getSize(), objs[OBJ_PTERO_ADULT].getSize(), objs[OBJ_PTERO_ADULT].getSize());
		RenderMesh(meshList[GEO_PTERO], godlights);
		viewStack.PopMatrix();
		break;
	default:
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_PTERO_BABY].getPos().x, objs[OBJ_PTERO_BABY].getPos().y, objs[OBJ_PTERO_BABY].getPos().z);
		RenderText(meshList[GEO_TEXT], "dis nigga DEAD bruh", Color(1, 0, 0));
		viewStack.PopMatrix();
		break;
	}

	for (int i = 0; i <= 200; i += 10) { // fence
		viewStack.PushMatrix();
		viewStack.Translate(objs[OBJ_FENCE].getPos().x - i, objs[OBJ_FENCE].getPos().y, objs[OBJ_FENCE].getPos().z);
		viewStack.Scale(objs[OBJ_FENCE].getSizeY(), objs[OBJ_FENCE].getSizeY(), objs[OBJ_FENCE].getSizeY());
		RenderMesh(meshList[GEO_FENCE], godlights);
		viewStack.PopMatrix();
	}

	/* sampel
	viewStack.PushMatrix();
		viewStack.Scale(1, 1, 1);
		viewStack.Translate(0, 0, 0);
		viewStack.Rotate(0, 0, 1, 0);
		RenderMesh(meshList[], godlights);
		RenderText(meshList[GEO_TEXT], "test", Color(1, 0, 0));
	viewStack.PopMatrix();
	*/

	switch (pteroStage) {
	case P_EGG:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: EGG", Color(1, 1, 1), 3, 1, 1);
		if (incubating) {
			RenderTextOnScreen(meshList[GEO_TEXT], "EGG INCUBATED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z >= 19.0f) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO INCUBATE EGG", Color(1, 0, 0), 2, 1, 29);
		}
		break;
	case P_BABY:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: BABY", Color(0, 1, 0), 3, 1, 1);
		if (!hungry) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PTERODACTYL FED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z >= 19.0f) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO FEED PTERODACTYL", Color(1, 0, 0), 2, 1, 29);
		}
		break;
	case P_ADOLESCENT:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: ADOLESCENT", Color(0, 1, 0), 3, 1, 1);
		if (!hungry) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PTERODACTYL FED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z >= 19.0f) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO FEED PTERODACTYL", Color(1, 0, 0), 2, 1, 29);
		}
		break;
	case P_ADULT:
		RenderTextOnScreen(meshList[GEO_TEXT], "Stage: ADULT", Color(0, 1, 0), 3, 1, 1);
		if (!hungry) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PTERODACTYL FED", Color(1, 0, 0), 2, 1, 29);
			RenderTextOnScreen(meshList[GEO_TEXT], "(COME BACK IN A WHILE)", Color(1, 0, 0), 1.5, 1, 37);
		}
		else if (camera.position.z >= 19.0f) {
			RenderTextOnScreen(meshList[GEO_TEXT], "PRESS X TO FEED PTERODACTYL", Color(1, 0, 0), 2, 1, 29);
		}
		break;
	default:
		
		break;
	}

	std::ostringstream ah;
	ah << framerate;
	std::string str = ah.str();
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + str, Color(0, 1, 0), 2, 33, 29);
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