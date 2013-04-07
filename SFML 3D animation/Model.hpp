#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

#include "Mesh.h"

typedef std::vector<Mesh*> MeshList;

class Model{
public:
	Model(const std::string filename);
	~Model();
private:
	std::string m_filename;
	Assimp::Importer m_importer;
	const aiScene* m_scene;
	MeshList m_meshes;
	void recursivelyFindMeshes(aiNode* currentNode);
	void inline addMesh(aiNode* meshContainingNode, aiNode* rootNode, unsigned int meshIndex);
};