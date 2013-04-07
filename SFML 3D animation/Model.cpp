#include "Model.hpp"

void inline Model::addMesh(aiNode* meshContainingNode, aiNode* rootNode, unsigned int meshIndex) {
	Mesh* currentMesh = new Mesh(m_scene->mMeshes[meshContainingNode->mMeshes[meshIndex]],meshContainingNode,m_scene->mRootNode,meshContainingNode->mTransformation);
	m_meshes.push_back((Mesh*)NULL);
}

void Model::recursivelyFindMeshes(aiNode* currentNode) {
	if(currentNode->mNumMeshes > 0) {
		for(size_t meshIndex=0; meshIndex < currentNode->mNumMeshes; meshIndex++) {
			addMesh(currentNode, m_scene->mRootNode,meshIndex);
		};
	};

	if(currentNode->mChildren > 0) {
		for(size_t childIndex=0; childIndex<currentNode->mNumChildren; childIndex++) {
			recursivelyFindMeshes(currentNode->mChildren[childIndex]);
		};
	};
}

Model::Model(const std::string filename) : m_filename(filename) {
	//the scene shoudl generally be disposable, but I don't think that matters for this really.
	m_scene = m_importer.ReadFile(m_filename,
		aiProcess_Triangulate |
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices);
	std::cerr<<"File read"<<std::endl;

	//for this test code, find all the meshes and their nodes
	//NO ERROR CHECKING The following is not checked right now:
	//if there are meshes
	//if the model even loaded
	//if there is anything in the file
	//if there are bones
	//if the mesh-bone relationship is anything different than what is illustrated in "Mesh.cpp"

	recursivelyFindMeshes(m_scene->mRootNode);
};

Model::~Model() {
};