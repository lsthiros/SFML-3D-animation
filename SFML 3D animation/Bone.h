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
	Bone* m_parent;
	std::vector<Bone*> m_children;
	int m_numChildren;
	aiMatrix4x4 m_transform, m_global, m_offset;
	//TODO cleanup unused crap, like m_root, hasChildren, etc.
	bool m_root;
public:
	Bone(aiMatrix4x4 transform, aiMatrix4x4 global, Bone* parent);
	~Bone(void);
	bool hasChildren();
	bool isRoot(){return m_root;};
	//getters and setters
	int getNumChildren() {return m_numChildren;};
	aiMatrix4x4 getGlobalMatrix() {return m_global;};
	void setOffset(const aiMatrix4x4& offset) {m_offset = offset;};
	void updateChildTransforms(aiMatrix4x4& parentMatrix);
	void addChild(Bone* child);
};

//anything that uses bones will probably need a list of them
typedef std::vector<Bone*>;