#include "Mesh.h"


Mesh::Mesh(aiMesh *mesh, aiNode* node, aiNode* rootNode, const aiMatrix4x4& transform) : m_node(node), m_mesh(mesh), m_transform(transform), m_root(rootNode)
{
	//find out how many vertices there are in this mesh
	//this is probably going to come in handy later
	m_numVertices=m_mesh->mNumVertices;
	m_vertices=new Vertex[m_numVertices];
	for(unsigned int i=0;i<m_numVertices;i++) {
		//deal with the model space coordinates first
		m_vertices[i].modelSpace[0]=m_mesh->mVertices[i][0];
		m_vertices[i].modelSpace[1]=m_mesh->mVertices[i][1];
		m_vertices[i].modelSpace[2]=m_mesh->mVertices[i][2];

		//then put the normals in there as well
		m_vertices[i].normal[0]=m_mesh->mNormals[i][0];
		m_vertices[i].normal[1]=m_mesh->mNormals[i][1];
		m_vertices[i].normal[2]=m_mesh->mNormals[i][2];
		//initialize the weights as 0 and the ID's as -1, that should prevent any mishaps
		//have to remember that for the shaders though...
		for(int weightIndex=0;weightIndex<4;weightIndex++) {
			m_vertices[i].boneId[weightIndex]=-1;
			m_vertices[i].boneWeighs[weightIndex]=0.0f;
		};
	};

	//==========================================================
	//==========================DONE============================
	//==========================================================
	//find a list of all ai nodes that are effectively part of the skeleton
	//do this by looking at the list of aimesh's aibones, marking each one and its ancestors
	//as a part of the skeleton, up to the parent ainode that the aimesh shares (eg, check
	//each ainode's parent against the mesh's parent) like this:
	//
	//Common Root---Mesh
	//			 \
	//			  Skeleton root
	//
	//After you have a list of necessary aiNodes, start at the one that shares its root with the mesh
	//make it known that its the root bone
	m_skeleton=constructSkeleton();
	//assign weights
	//an array to keep track of how many weights have been added to each vertex
	std::vector<unsigned int> weightList(m_numVertices, 0);
	for(size_t boneIndex=0;boneIndex<m_mesh->mNumBones;boneIndex++) {
		for(size_t weightIndex=0;weightIndex<m_mesh->mBones[boneIndex]->mNumWeights;weightIndex++) {
			unsigned int& currentId=weightList[m_mesh->mBones[boneIndex]->mWeights[weightIndex].mVertexId];
			if(currentId<4) {
				m_vertices[m_mesh->mBones[boneIndex]->mWeights[weightIndex].mVertexId].boneId[currentId]=m_boneNameToOffset[m_mesh->mBones[boneIndex]->mName.data];
				m_vertices[m_mesh->mBones[boneIndex]->mWeights[weightIndex].mVertexId].boneWeighs[currentId]=m_mesh->mBones[boneIndex]->mWeights[weightIndex].mWeight;
				currentId++;
			};
		};
	};
}

//recursively creates a group of Bones resembling the tree given at the parent node.
Bone* Mesh::recursivelyCreateSkeleton(aiNode* node, Bone* parent, std::map<std::string, bool>& map,const aiMatrix4x4& parentOffset) {
	//gross hacky way of getting this to work.
	Bone* newBone =new Bone(node->mTransformation,(parent==NULL) ? node->mTransformation : node->mTransformation*parentOffset, parent);
	m_boneNameToOffset[node->mName.data]=m_boneList.size();
	m_boneList.push_back(newBone);
	//for every child node that is marked as necessary, add a corresponding Bone as a child to the
	//current bone.
	for(size_t childIndex=0;childIndex<node->mNumChildren;childIndex++) {
		if(map[node->mChildren[childIndex]->mName.data]) newBone->addChild(recursivelyCreateSkeleton(node->mChildren[childIndex], newBone, map, newBone->getGlobalMatrix()));
	};
	return newBone;
};

Bone* Mesh::constructSkeleton() {
	std::map<std::string, bool> boneNecessityMap;
	//find out what bones are needed
	aiNode* skeletonRoot=findNecessaryBones(boneNecessityMap);
	//this is also weird...
	aiMatrix4x4* identity = new aiMatrix4x4();
	Bone* rootBone = recursivelyCreateSkeleton(skeletonRoot, NULL, boneNecessityMap, *identity);
	//The bones do not have their offset matrices created yet, they need to be set.
	for(size_t boneIndex=0; boneIndex<m_mesh->mNumBones;boneIndex++) {
		m_boneList[m_boneNameToOffset[m_mesh->mBones[boneIndex]->mName.data]]->setOffset(m_mesh->mBones[boneIndex]->mOffsetMatrix);
	};
	return rootBone;
};


/*this function takes a starting node, puts its name in the necessity register as false, and then
||goes through each of its children recursively and marks then as false (not necessary). This is
||necessary because otherwise, parts that aren't needed won't be put in the map at all*/
void Mesh::recursivelyZeroNecessityMap(std::map<std::string, bool>& map, aiNode* currentNode) {
	map[currentNode->mName.data]=false;

	//very important to exit if there are no children. That is, BEFORE we go around and
	//play with memory.
	if(currentNode->mNumChildren == NULL) return;

	for(size_t childIndex=0; childIndex < currentNode->mNumChildren; childIndex++) {
		recursivelyZeroNecessityMap(map, currentNode->mChildren[childIndex]);
	};
};

//this function first marks all nodes as not-needed, then figures out
//which ones will actually affect the mesh object. NOTE: I do not know if
//I should mark the parents of the mesh as necessary. It would be needed for
//more complicated models, but not this.
aiNode* Mesh::findNecessaryBones(std::map<std::string, bool>& map) {
	//mark everything as not needed.
	recursivelyZeroNecessityMap(map, m_root);
	//then go and mark the needed ones as such
	aiNode* skeletonRoot;
	for(size_t boneIndex=0; boneIndex<m_mesh->mNumBones; boneIndex++) {
		aiNode* currentNode = m_root->FindNode(m_mesh->mBones[boneIndex]->mName.data);
		skeletonRoot=recursivelyFindNecessaryBones(map, currentNode);
	};
	return skeletonRoot;
};

aiNode* Mesh::recursivelyFindNecessaryBones(std::map<std::string, bool>& map, aiNode* currentNode) {
	map[currentNode->mName.data]=true;

	if(currentNode->mParent->mName.data == m_node->mParent->mName.data || currentNode->mParent==NULL || currentNode->mParent->mName.data == m_node->mName.data) return currentNode;

	return recursivelyFindNecessaryBones(map, currentNode->mParent);
}

//TODO make sure all memory is unallocated
Mesh::~Mesh(void)
{
}
