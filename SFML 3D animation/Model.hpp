#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <cstdlib>
#include <string>
#include <iostream>

class Model{
public:
	Model(const std::string filename);
	~Model();
private:
	std::string m_filename;
	Assimp::Importer importer;
	const aiScene* scene;
};