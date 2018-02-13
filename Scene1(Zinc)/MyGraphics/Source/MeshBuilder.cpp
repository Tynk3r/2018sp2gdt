#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertexBuffer;
	std::vector<GLuint> indexBuffer;
	Vertex vee;
	vee.pos.Set(-1000, 0, 0);
	vee.color.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(1000, 0, 0);
	vee.color.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0, -1000, 0);
	vee.color.Set(0, 1, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0, 1000, 0);
	vee.color.Set(0, 1, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0, 0, -1000);
	vee.color.Set(0, 0, 1);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0, 0, 1000);
	vee.color.Set(0, 0, 1);
	vertexBuffer.push_back(vee);

	indexBuffer = { 0,1,2,3,4,5 };
	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), &vertexBuffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLuint), &indexBuffer[0], GL_STATIC_DRAW);


	
	mesh->indexSize = indexBuffer.size();
	mesh->mode = Mesh::DRAW_LINES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::Generate2DQuad(const std::string &meshName, float lengthX, float lengthY, float Red, float Green, float Blue)
{
	std::vector<Vertex> vertexBuffer;
	std::vector<GLuint> indexBuffer;
	Vertex vee;
	vee.pos.Set(-1.0f*lengthX, -1.0f*lengthY, 0.0f);
	vee.color.Set(Red, Green, Blue);
	vee.normal.Set(1, 0, 0);
	vee.texCoord.Set(0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(1.0f*lengthX, -1.0f*lengthY, 0.0f);
	vee.color.Set(Red, Green, Blue);
	vee.normal.Set(1, 0, 0);
	vee.texCoord.Set(1, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(1.0f*lengthX, 1.0f*lengthY, 0.0f);
	vee.color.Set(Red, Green, Blue);
	vee.normal.Set(1, 0, 0);
	vee.texCoord.Set(1, 1);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-1.0f*lengthX, 1.0f*lengthY, 0.0f);
	vee.color.Set(Red, Green, Blue);
	vee.normal.Set(1, 0, 0);
	vee.texCoord.Set(0, 1);
	vertexBuffer.push_back(vee);

	indexBuffer = { 
		0,1,2,
		0,2,3
	};

	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), &vertexBuffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLuint), &indexBuffer[0], GL_STATIC_DRAW);
	mesh->indexSize = indexBuffer.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName,Color colz, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertexBuffer;
	std::vector<GLuint> indexBuffer;
	Vertex vee;
	vee.pos.Set(-0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);
	
	vee.pos.Set(-0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee); //front

	vee.pos.Set(0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee); //right

	vee.pos.Set(0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee); //top

	vee.pos.Set(-0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, 0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee); //left

	vee.pos.Set(-0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, 0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee); //bottm

	vee.pos.Set(-0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(-0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, 0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee);

	vee.pos.Set(0.5f, -0.5f, -0.5f);
	vee.color = colz;
	vee.normal.Set(1, 0, 0);
	vertexBuffer.push_back(vee); //bak

	indexBuffer = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35 };

	
	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), &vertexBuffer[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLuint), &indexBuffer[0], GL_STATIC_DRAW);
	mesh->indexSize = indexBuffer.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}

float DegtoRad(float th)
{
	return (th*(3.1415926535897932f / 180.0f));
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color colz, float innerRadius, float outerRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;


	for (int theta = 0; theta <= 360; theta += 10)
	{
		float x = outerRadius * cosf(DegtoRad(theta));
		float y = outerRadius * sinf(DegtoRad(theta));

		v.pos.Set(x, 0, y);
		v.color = colz;
		vertex_buffer_data.push_back(v);

		float x1 = innerRadius * cosf(DegtoRad(theta));
		float y1 = innerRadius * sinf(DegtoRad(theta));

		v.pos.Set(x1, 0, y1);
		v.color = colz;
		vertex_buffer_data.push_back(v);

	}

	std::vector<GLuint> index_buffer_data;

	for (int i = 0; i < vertex_buffer_data.size(); ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float sphereX(float phi, float theta)
{
	return cos(DegtoRad(phi)) * cos(DegtoRad(theta));
}
float sphereY(float phi, float theta)
{
	return sin(DegtoRad(phi));
}
float sphereZ(float phi, float theta)
{
	return cos(DegtoRad(phi)) * sin(DegtoRad(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color colz, unsigned numStack, unsigned numSlice, float radius)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;


	for (unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = -90.0f + stack * degreePerStack;

		for (unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			float theta = slice *degreePerSlice;
			Vertex v;

			v.pos.Set(radius* sphereX(phi, theta), radius*sphereY(phi, theta), radius*sphereZ(phi, theta));
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			v.color = colz;
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice; ++slice)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned j = 0; j < numRow; ++j)
	{
		for (unsigned i = 0; i < numCol; ++i)
		{
			float u1 = i*width;
			float v1 = 1.0f - height - j*height;
			Vertex vee;
			vee.pos.Set(-0.5f, -0.5f, 0.0f);
			vee.texCoord.Set(u1, v1);
			vee.normal.Set(1, 0, 0);
			vertex_buffer_data.push_back(vee);

			vee.pos.Set(0.5f, -0.5f, 0.0f);
			vee.texCoord.Set(u1+width, v1);
			vee.normal.Set(1, 0, 0);
			vertex_buffer_data.push_back(vee);

			vee.pos.Set(0.5f, 0.5f, 0.0f);
			vee.texCoord.Set(width + u1, height + v1);
			vee.normal.Set(1, 0, 0);
			vertex_buffer_data.push_back(vee);

			vee.pos.Set(-0.5f, 0.5f, 0.0f);
			vee.texCoord.Set(0 + u1, height + v1);
			vee.normal.Set(1, 0, 0);
			vertex_buffer_data.push_back(vee);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
