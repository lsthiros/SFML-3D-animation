#include "Model.hpp"

Model::Model(const std::string filename) : m_filename(filename) {
	scene = importer.ReadFile(m_filename,
		aiProcess_Triangulate |
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices);
	std::cerr<<"File read"<<std::endl;
};

Model::~Model() {
};