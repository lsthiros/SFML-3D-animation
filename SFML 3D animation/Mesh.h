#pragma once

#include <assimp\vector3.h>
#include <assimp\scene.h>

//this vertex struct made to shove straight into a VBO
typedef struct Vertex {
	float modelSpace[3];
	float normal[3];
	unsigned int boneId[4];
	float boneWeighs[4];
} Vertex;

//doubt that this will be usefull
typedef int face[3];

class Mesh
{
private:
	//nothing here yet
	//TODO figure out what is private
public:
	//TODO do bones belong in here?
	unsigned int m_numVertices;
	Vertex* m_vertices;
	aiNode* m_node;
	aiMesh* m_mesh;
	aiMatrix4x4* m_transform;

	Mesh(aiMesh *mesh, aiNode* node, aiMatrix4x4* transform);
	~Mesh(void);
};