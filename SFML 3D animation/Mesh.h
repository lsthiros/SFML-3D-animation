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
	//ainode containing the this mesh
	aiMesh* m_mesh;
	//transformation of this mesh relative to parent
	aiMatrix4x4 m_transform;
	//name of the node containing this mesh
	std::string name;
	//root bone of the skeleton associated with this model
	Bone* m_skeleton;
	//and then a vector of bones
	std::vector<Bone*> m_boneList;
	//and map to translate bone names to list index
	std::map<std::string, unsigned int> m_boneNameToOffset;
	//private functions
	Bone* constructSkeleton();
	aiNode* findNecessaryBones(std::map<std::string, bool>& map);
	void recursivelyZeroNecessityMap(std::map<std::string, bool>& map, aiNode* currentNode);
	aiNode* recursivelyFindNecessaryBones(std::map<std::string, bool>& map, aiNode* currentNode);
	Bone* recursivelyCreateSkeleton(aiNode* node, Bone* parent, std::map<std::string, bool>& map,const aiMatrix4x4& parentOffset);
public:
	Mesh(aiMesh *mesh, aiNode* node, aiNode* rootNode, const aiMatrix4x4& transform);
	~Mesh(void);
};