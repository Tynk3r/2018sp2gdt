#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"


/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* Generate2DQuad(const std::string &meshName, float lengthX, float lengthY, float Red, float Green, float Blue);
	static Mesh* GenerateCube(const std::string &meshName, Color colz, float lengthX, float lengthY, float lengthZ);

	static Mesh* GenerateRing(const std::string &meshName, Color colz, float innerRadius, float outerRadius);
	static Mesh* GenerateSphere(const std::string &meshName, Color colz, unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif