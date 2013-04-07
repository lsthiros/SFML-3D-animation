#pragma once

#include "Bone.h"

class Skeleton
{
private:
	Bone** m_boneList;
	int m_numBones;
public:
	Skeleton(int numBones);
	~Skeleton(void);
	Bone* getBone(int index) {return m_boneList[index];};
	int getNumBones() {return m_numBones;};
};

