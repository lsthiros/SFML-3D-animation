#include "Bone.h"


Bone::Bone(aiMatrix4x4 transform, aiMatrix4x4 global) :
	m_transform(transform),
	m_global(global)
{
}


Bone::~Bone(void)
{
}
