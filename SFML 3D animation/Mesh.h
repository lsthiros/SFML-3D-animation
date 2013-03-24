#pragma once

#include <assimp\vector3.h>
#include <assimp\scene.h>

#include <vector>
#include <map>

#include "Bone.h"

//this vertex struct made to shove straight into a VBO
typedef struct Vertex {
	float modelSpace[3];
	float normal[3];
	unsigned int boneId[4];
	float boneWeighs[4];
} Vertex;

class Mesh
{
private:
	unsigned int m_numVertices;
	Vertex* m_vertices;
	aiNode* m_node, *m_root;
	aiMesh* m_mesh;
	aiMatrix4x4 m_transform;
	std::string name;
	Bone* m_skeleton;
	//used for constructing skeleton. HOPEFULLY
	Bone* constructSkeleton();
	void findNecessaryBones(std::map<std::string, bool>& map);
	void recursivelyZeroNecessityMap(std::map<std::string, bool>& map, aiNode* currentNode);
public:
	Mesh(aiMesh *mesh, aiNode* node, aiNode* rootNode, const aiMatrix4x4& transform);
	~Mesh(void);
};