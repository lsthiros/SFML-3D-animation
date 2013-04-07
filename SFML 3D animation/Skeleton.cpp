#include "Skeleton.h"
#include "Bone.h"

Skeleton::Skeleton(int numbones) : m_numBones(numbones)
{
	m_boneList=new Bone*[m_numBones];
}


Skeleton::~Skeleton(void)
{
	delete[] m_boneList;
}