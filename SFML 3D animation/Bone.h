#pragma once
#include <assimp\vector3.h>
#include <assimp\matrix4x4.h>
#include <assimp\quaternion.h>
#include <assimp\scene.h>

#include <vector>
#include <string>

class Bone
{
private:
	aiNode* m_correspondingNode;
	Bone* m_parent, *m_children;
	int m_numChildren;
	aiMatrix4x4 m_transform, m_global, m_offset;
	bool m_root;
public:
	Bone(aiMatrix4x4 transform, aiMatrix4x4 global);
	~Bone(void);
	bool hasChildren();
	bool isRoot(){return m_root;};
	int getNumChildren() {return m_numChildren;};
	Bone* getChildren() {return m_children;};
	aiMatrix4x4 getGlobalMatrix() {return m_global;};
	void updateChildTransforms(aiMatrix4x4& parentMatrix);
};

//anything that uses bones will probably need a list of them
typedef std::vector<Bone*>;