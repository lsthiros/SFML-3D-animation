#pragma once
#include <assimp\vector3.h>
#include <assimp\matrix4x4.h>
#include <assimp\quaternion.h>
#include <assimp\scene.h>

#include <vector>

class Bone
{
private:
	aiNode* m_correspondingNode;
	Bone* m_parent, *m_children;
	int m_numChildren;
public:
	Bone(void);
	~Bone(void);
	bool hasChildren();
	bool isRoot();
	int getNumChildren() {return m_numChildren;};
	Bone* getChildren() {return m_children;};
};

//anything that uses bones will probably need a list of them
typedef std::vector<Bone*>;